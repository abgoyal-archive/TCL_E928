

#include <common.h>
#include <asm/io.h>
#ifdef CONFIG_OMAP_SX1
#include <i2c.h>
#endif
#include <usbdevice.h>
#include <usb/omap1510_udc.h>

#include "ep0.h"


#define UDC_INIT_MDELAY		     80 /* Device settle delay */
#define UDC_MAX_ENDPOINTS	     31 /* Number of endpoints on this UDC */

/* Some kind of debugging output... */
#if 1
#define UDCDBG(str)
#define UDCDBGA(fmt,args...)
#else  /* The bugs still exists... */
#define UDCDBG(str) serial_printf("[%s] %s:%d: " str "\n", __FILE__,__FUNCTION__,__LINE__)
#define UDCDBGA(fmt,args...) serial_printf("[%s] %s:%d: " fmt "\n", __FILE__,__FUNCTION__,__LINE__, ##args)
#endif

#if 1
#define UDCREG(name)
#define UDCREGL(name)
#else  /* The bugs still exists... */
#define UDCREG(name)	 serial_printf("%s():%d: %s[%08x]=%.4x\n",__FUNCTION__,__LINE__, (#name), name, inw(name))	/* For 16-bit regs */
#define UDCREGL(name)	 serial_printf("%s():%d: %s[%08x]=%.8x\n",__FUNCTION__,__LINE__, (#name), name, inl(name))	/* For 32-bit regs */
#endif


static struct urb *ep0_urb = NULL;

static struct usb_device_instance *udc_device;	/* Used in interrupt handler */
static u16 udc_devstat = 0;	/* UDC status (DEVSTAT) */
static u32 udc_interrupts = 0;

static void udc_stall_ep (unsigned int ep_addr);


static struct usb_endpoint_instance *omap1510_find_ep (int ep)
{
	int i;

	for (i = 0; i < udc_device->bus->max_endpoints; i++) {
		if (udc_device->bus->endpoint_array[i].endpoint_address == ep)
			return &udc_device->bus->endpoint_array[i];
	}
	return NULL;
}

/* ************************************************************************** */

static void omap1510_prepare_endpoint_for_rx (int ep_addr)
{
	int ep_num = ep_addr & USB_ENDPOINT_NUMBER_MASK;

	UDCDBGA ("omap1510_prepare_endpoint %x", ep_addr);
	if (((ep_addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT)) {
		if ((inw (UDC_EP_RX (ep_num)) &
		     (UDC_EPn_RX_Valid | UDC_EPn_RX_Iso)) ==
		    UDC_EPn_RX_Valid) {
			/* rx endpoint is valid, non-ISO, so enable its FIFO */
			outw (UDC_EP_Sel | ep_num, UDC_EP_NUM);
			outw (UDC_Set_FIFO_En, UDC_CTRL);
			outw (0, UDC_EP_NUM);
		}
	}
}

static void omap1510_configure_endpoints (struct usb_device_instance *device)
{
	int ep;
	struct usb_bus_instance *bus;
	struct usb_endpoint_instance *endpoint;
	unsigned short ep_ptr;
	unsigned short ep_size;
	unsigned short ep_isoc;
	unsigned short ep_doublebuffer;
	int ep_addr;
	int packet_size;
	int buffer_size;
	int attributes;

	bus = device->bus;

	/* There is a dedicated 2048 byte buffer for USB packets that may be
	 * arbitrarily partitioned among the endpoints on 8-byte boundaries.
	 * The first 8 bytes are reserved for receiving setup packets on
	 * endpoint 0.
	 */
	ep_ptr = 8;		/* reserve the first 8 bytes for the setup fifo */

	for (ep = 0; ep < bus->max_endpoints; ep++) {
		endpoint = bus->endpoint_array + ep;
		ep_addr = endpoint->endpoint_address;
		if ((ep_addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN) {
			/* IN endpoint */
			packet_size = endpoint->tx_packetSize;
			attributes = endpoint->tx_attributes;
		} else {
			/* OUT endpoint */
			packet_size = endpoint->rcv_packetSize;
			attributes = endpoint->rcv_attributes;
		}

		switch (packet_size) {
		case 0:
			ep_size = 0;
			break;
		case 8:
			ep_size = 0;
			break;
		case 16:
			ep_size = 1;
			break;
		case 32:
			ep_size = 2;
			break;
		case 64:
			ep_size = 3;
			break;
		case 128:
			ep_size = 4;
			break;
		case 256:
			ep_size = 5;
			break;
		case 512:
			ep_size = 6;
			break;
		default:
			UDCDBGA ("ep 0x%02x has bad packet size %d",
				 ep_addr, packet_size);
			packet_size = 0;
			ep_size = 0;
			break;
		}

		switch (attributes & USB_ENDPOINT_XFERTYPE_MASK) {
		case USB_ENDPOINT_XFER_CONTROL:
		case USB_ENDPOINT_XFER_BULK:
		case USB_ENDPOINT_XFER_INT:
		default:
			/* A non-isochronous endpoint may optionally be
			 * double-buffered. For now we disable
			 * double-buffering.
			 */
			ep_doublebuffer = 0;
			ep_isoc = 0;
			if (packet_size > 64)
				packet_size = 0;
			if (!ep || !ep_doublebuffer)
				buffer_size = packet_size;
			else
				buffer_size = packet_size * 2;
			break;
		case USB_ENDPOINT_XFER_ISOC:
			/* Isochronous endpoints are always double-
			 * buffered, but the double-buffering bit
			 * in the endpoint configuration register
			 * becomes the msb of the endpoint size so we
			 * set the double-buffering flag to zero.
			 */
			ep_doublebuffer = 0;
			ep_isoc = 1;
			buffer_size = packet_size * 2;
			break;
		}

		/* check to see if our packet buffer RAM is exhausted */
		if ((ep_ptr + buffer_size) > 2048) {
			UDCDBGA ("out of packet RAM for ep 0x%02x buf size %d", ep_addr, buffer_size);
			buffer_size = packet_size = 0;
		}

		/* force a default configuration for endpoint 0 since it is
		 * always enabled
		 */
		if (!ep && ((packet_size < 8) || (packet_size > 64))) {
			buffer_size = packet_size = 64;
			ep_size = 3;
		}

		if (!ep) {
			/* configure endpoint 0 */
			outw ((ep_size << 12) | (ep_ptr >> 3), UDC_EP0);
			/*UDCDBGA("ep 0 buffer offset 0x%03x packet size 0x%03x", */
			/*	ep_ptr, packet_size); */
		} else if ((ep_addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN) {
			/* IN endpoint */
			if (packet_size) {
				outw ((1 << 15) | (ep_doublebuffer << 14) |
				      (ep_size << 12) | (ep_isoc << 11) |
				      (ep_ptr >> 3),
				      UDC_EP_TX (ep_addr &
						 USB_ENDPOINT_NUMBER_MASK));
				UDCDBGA ("IN ep %d buffer offset 0x%03x"
					 " packet size 0x%03x",
					 ep_addr & USB_ENDPOINT_NUMBER_MASK,
					 ep_ptr, packet_size);
			} else {
				outw (0,
				      UDC_EP_TX (ep_addr &
						 USB_ENDPOINT_NUMBER_MASK));
			}
		} else {
			/* OUT endpoint */
			if (packet_size) {
				outw ((1 << 15) | (ep_doublebuffer << 14) |
				      (ep_size << 12) | (ep_isoc << 11) |
				      (ep_ptr >> 3),
				      UDC_EP_RX (ep_addr &
						 USB_ENDPOINT_NUMBER_MASK));
				UDCDBGA ("OUT ep %d buffer offset 0x%03x"
					 " packet size 0x%03x",
					 ep_addr & USB_ENDPOINT_NUMBER_MASK,
					 ep_ptr, packet_size);
			} else {
				outw (0,
				      UDC_EP_RX (ep_addr &
						 USB_ENDPOINT_NUMBER_MASK));
			}
		}
		ep_ptr += buffer_size;
	}
}

static void omap1510_deconfigure_device (void)
{
	int epnum;

	UDCDBG ("clear Cfg_Lock");
	outw (inw (UDC_SYSCON1) & ~UDC_Cfg_Lock, UDC_SYSCON1);
	UDCREG (UDC_SYSCON1);

	/* deconfigure all endpoints */
	for (epnum = 1; epnum <= 15; epnum++) {
		outw (0, UDC_EP_RX (epnum));
		outw (0, UDC_EP_TX (epnum));
	}
}

static void omap1510_configure_device (struct usb_device_instance *device)
{
	omap1510_configure_endpoints (device);


	/* Figure 14-9 indicates we should enable interrupts here, but we have
	 * other routines (udc_all_interrupts, udc_suspended_interrupts) to
	 * do that.
	 */

	UDCDBG ("set Cfg_Lock");
	outw (inw (UDC_SYSCON1) | UDC_Cfg_Lock, UDC_SYSCON1);
	UDCREG (UDC_SYSCON1);
}

static void omap1510_write_noniso_tx_fifo (struct usb_endpoint_instance
					   *endpoint)
{
	struct urb *urb = endpoint->tx_urb;

	if (urb) {
		unsigned int last, i;

		UDCDBGA ("urb->buffer %p, buffer_length %d, actual_length %d",
			 urb->buffer, urb->buffer_length, urb->actual_length);
		if ((last =
		     MIN (urb->actual_length - endpoint->sent,
			  endpoint->tx_packetSize))) {
			u8 *cp = urb->buffer + endpoint->sent;

			UDCDBGA ("endpoint->sent %d, tx_packetSize %d, last %d", endpoint->sent, endpoint->tx_packetSize, last);

			if (((u32) cp & 1) == 0) {	/* word aligned? */
				outsw (UDC_DATA, cp, last >> 1);
			} else {	/* byte aligned. */
				for (i = 0; i < (last >> 1); i++) {
					u16 w = ((u16) cp[2 * i + 1] << 8) |
						(u16) cp[2 * i];
					outw (w, UDC_DATA);
				}
			}
			if (last & 1) {
				outb (*(cp + last - 1), UDC_DATA);
			}
		}
		endpoint->last = last;
	}
}

static int omap1510_read_noniso_rx_fifo (struct usb_endpoint_instance
					 *endpoint)
{
	struct urb *urb = endpoint->rcv_urb;
	int len = 0;

	if (urb) {
		len = inw (UDC_RXFSTAT);

		if (len) {
			unsigned char *cp = urb->buffer + urb->actual_length;

			insw (UDC_DATA, cp, len >> 1);
			if (len & 1)
				*(cp + len - 1) = inb (UDC_DATA);
		}
	}
	return len;
}

static void omap1510_prepare_for_control_write_status (struct urb *urb)
{
	struct usb_device_request *request = &urb->device_request;;

	/* check for a SET_CONFIGURATION request */
	if (request->bRequest == USB_REQ_SET_CONFIGURATION) {
		int configuration = le16_to_cpu (request->wValue) & 0xff;
		unsigned short devstat = inw (UDC_DEVSTAT);

		if ((devstat & (UDC_ADD | UDC_CFG)) == UDC_ADD) {
			/* device is currently in ADDRESSED state */
			if (configuration) {
				/* Assume the specified non-zero configuration
				 * value is valid and switch to the CONFIGURED
				 * state.
				 */
				outw (UDC_Dev_Cfg, UDC_SYSCON2);
			}
		} else if ((devstat & UDC_CFG) == UDC_CFG) {
			/* device is currently in CONFIGURED state */
			if (!configuration) {
				/* Switch to ADDRESSED state. */
				outw (UDC_Clr_Cfg, UDC_SYSCON2);
			}
		}
	}

	/* select EP0 tx FIFO */
	outw (UDC_EP_Dir | UDC_EP_Sel, UDC_EP_NUM);
	/* clear endpoint (no data bytes in status stage) */
	outw (UDC_Clr_EP, UDC_CTRL);
	/* enable the EP0 tx FIFO */
	outw (UDC_Set_FIFO_En, UDC_CTRL);
	/* deselect the endpoint */
	outw (UDC_EP_Dir, UDC_EP_NUM);
}

static void udc_state_transition_up (usb_device_state_t initial,
				     usb_device_state_t final)
{
	if (initial < final) {
		switch (initial) {
		case STATE_ATTACHED:
			usbd_device_event_irq (udc_device,
					       DEVICE_HUB_CONFIGURED, 0);
			if (final == STATE_POWERED)
				break;
		case STATE_POWERED:
			usbd_device_event_irq (udc_device, DEVICE_RESET, 0);
			if (final == STATE_DEFAULT)
				break;
		case STATE_DEFAULT:
			usbd_device_event_irq (udc_device,
					       DEVICE_ADDRESS_ASSIGNED, 0);
			if (final == STATE_ADDRESSED)
				break;
		case STATE_ADDRESSED:
			usbd_device_event_irq (udc_device, DEVICE_CONFIGURED,
					       0);
		case STATE_CONFIGURED:
			break;
		default:
			break;
		}
	}
}

static void udc_state_transition_down (usb_device_state_t initial,
				       usb_device_state_t final)
{
	if (initial > final) {
		switch (initial) {
		case STATE_CONFIGURED:
			usbd_device_event_irq (udc_device, DEVICE_DE_CONFIGURED, 0);
			if (final == STATE_ADDRESSED)
				break;
		case STATE_ADDRESSED:
			usbd_device_event_irq (udc_device, DEVICE_RESET, 0);
			if (final == STATE_DEFAULT)
				break;
		case STATE_DEFAULT:
			usbd_device_event_irq (udc_device, DEVICE_POWER_INTERRUPTION, 0);
			if (final == STATE_POWERED)
				break;
		case STATE_POWERED:
			usbd_device_event_irq (udc_device, DEVICE_HUB_RESET, 0);
		case STATE_ATTACHED:
			break;
		default:
			break;
		}
	}
}

static void omap1510_udc_state_changed (void)
{
	u16 bits;
	u16 devstat = inw (UDC_DEVSTAT);

	UDCDBGA ("state changed, devstat %x, old %x", devstat, udc_devstat);

	bits = devstat ^ udc_devstat;
	if (bits) {
		if (bits & UDC_ATT) {
			if (devstat & UDC_ATT) {
				UDCDBG ("device attached and powered");
				udc_state_transition_up (udc_device->device_state, STATE_POWERED);
			} else {
				UDCDBG ("device detached or unpowered");
				udc_state_transition_down (udc_device->device_state, STATE_ATTACHED);
			}
		}
		if (bits & UDC_USB_Reset) {
			if (devstat & UDC_USB_Reset) {
				UDCDBG ("device reset in progess");
				udc_state_transition_down (udc_device->device_state, STATE_POWERED);
			} else {
				UDCDBG ("device reset completed");
			}
		}
		if (bits & UDC_DEF) {
			if (devstat & UDC_DEF) {
				UDCDBG ("device entering default state");
				udc_state_transition_up (udc_device->device_state, STATE_DEFAULT);
			} else {
				UDCDBG ("device leaving default state");
				udc_state_transition_down (udc_device->device_state, STATE_POWERED);
			}
		}
		if (bits & UDC_SUS) {
			if (devstat & UDC_SUS) {
				UDCDBG ("entering suspended state");
				usbd_device_event_irq (udc_device, DEVICE_BUS_INACTIVE, 0);
			} else {
				UDCDBG ("leaving suspended state");
				usbd_device_event_irq (udc_device, DEVICE_BUS_ACTIVITY, 0);
			}
		}
		if (bits & UDC_R_WK_OK) {
			UDCDBGA ("remote wakeup %s", (devstat & UDC_R_WK_OK)
				 ? "enabled" : "disabled");
		}
		if (bits & UDC_ADD) {
			if (devstat & UDC_ADD) {
				UDCDBG ("default -> addressed");
				udc_state_transition_up (udc_device->device_state, STATE_ADDRESSED);
			} else {
				UDCDBG ("addressed -> default");
				udc_state_transition_down (udc_device->device_state, STATE_DEFAULT);
			}
		}
		if (bits & UDC_CFG) {
			if (devstat & UDC_CFG) {
				UDCDBG ("device configured");
				/* The ep0_recv_setup function generates the
				 * DEVICE_CONFIGURED event when a
				 * USB_REQ_SET_CONFIGURATION setup packet is
				 * received, so we should already be in the
				 * state STATE_CONFIGURED.
				 */
				udc_state_transition_up (udc_device->device_state, STATE_CONFIGURED);
			} else {
				UDCDBG ("device deconfigured");
				udc_state_transition_down (udc_device->device_state, STATE_ADDRESSED);
			}
		}
	}

	/* Clear interrupt source */
	outw (UDC_DS_Chg, UDC_IRQ_SRC);

	/* Save current DEVSTAT */
	udc_devstat = devstat;
}

static void omap1510_udc_setup (struct usb_endpoint_instance *endpoint)
{
	UDCDBG ("-> Entering device setup");

	do {
		const int setup_pktsize = 8;
		unsigned char *datap =
			(unsigned char *) &ep0_urb->device_request;

		/* Gain access to EP 0 setup FIFO */
		outw (UDC_Setup_Sel, UDC_EP_NUM);

		/* Read control request data */
		insb (UDC_DATA, datap, setup_pktsize);

		UDCDBGA ("EP0 setup read [%x %x %x %x %x %x %x %x]",
			 *(datap + 0), *(datap + 1), *(datap + 2),
			 *(datap + 3), *(datap + 4), *(datap + 5),
			 *(datap + 6), *(datap + 7));

		/* Reset EP0 setup FIFO */
		outw (0, UDC_EP_NUM);
	} while (inw (UDC_IRQ_SRC) & UDC_Setup);

	/* Try to process setup packet */
	if (ep0_recv_setup (ep0_urb)) {
		/* Not a setup packet, stall next EP0 transaction */
		udc_stall_ep (0);
		UDCDBG ("can't parse setup packet, still waiting for setup");
		return;
	}

	/* Check direction */
	if ((ep0_urb->device_request.bmRequestType & USB_REQ_DIRECTION_MASK)
	    == USB_REQ_HOST2DEVICE) {
		UDCDBG ("control write on EP0");
		if (le16_to_cpu (ep0_urb->device_request.wLength)) {
			/* We don't support control write data stages.
			 * The only standard control write request with a data
			 * stage is SET_DESCRIPTOR, and ep0_recv_setup doesn't
			 * support that so we just stall those requests.  A
			 * function driver might support a non-standard
			 * write request with a data stage, but it isn't
			 * obvious what we would do with the data if we read it
			 * so we'll just stall it.  It seems like the API isn't
			 * quite right here.
			 */
#if 0
			/* Here is what we would do if we did support control
			 * write data stages.
			 */
			ep0_urb->actual_length = 0;
			outw (0, UDC_EP_NUM);
			/* enable the EP0 rx FIFO */
			outw (UDC_Set_FIFO_En, UDC_CTRL);
#else
			/* Stall this request */
			UDCDBG ("Stalling unsupported EP0 control write data "
				"stage.");
			udc_stall_ep (0);
#endif
		} else {
			omap1510_prepare_for_control_write_status (ep0_urb);
		}
	} else {
		UDCDBG ("control read on EP0");
		/* The ep0_recv_setup function has already placed our response
		 * packet data in ep0_urb->buffer and the packet length in
		 * ep0_urb->actual_length.
		 */
		endpoint->tx_urb = ep0_urb;
		endpoint->sent = 0;
		/* select the EP0 tx FIFO */
		outw (UDC_EP_Dir | UDC_EP_Sel, UDC_EP_NUM);
		/* Write packet data to the FIFO.  omap1510_write_noniso_tx_fifo
		 * will update endpoint->last with the number of bytes written
		 * to the FIFO.
		 */
		omap1510_write_noniso_tx_fifo (endpoint);
		/* enable the FIFO to start the packet transmission */
		outw (UDC_Set_FIFO_En, UDC_CTRL);
		/* deselect the EP0 tx FIFO */
		outw (UDC_EP_Dir, UDC_EP_NUM);
	}

	UDCDBG ("<- Leaving device setup");
}

static void omap1510_udc_ep0_rx (struct usb_endpoint_instance *endpoint)
{
	unsigned short status;

	UDCDBG ("RX on EP0");
	/* select EP0 rx FIFO */
	outw (UDC_EP_Sel, UDC_EP_NUM);

	status = inw (UDC_STAT_FLG);

	if (status & UDC_ACK) {
		/* Check direction */
		if ((ep0_urb->device_request.bmRequestType
		     & USB_REQ_DIRECTION_MASK) == USB_REQ_HOST2DEVICE) {
			/* This rx interrupt must be for a control write data
			 * stage packet.
			 *
			 * We don't support control write data stages.
			 * We should never end up here.
			 */

			/* clear the EP0 rx FIFO */
			outw (UDC_Clr_EP, UDC_CTRL);

			/* deselect the EP0 rx FIFO */
			outw (0, UDC_EP_NUM);

			UDCDBG ("Stalling unexpected EP0 control write "
				"data stage packet");
			udc_stall_ep (0);
		} else {
			/* This rx interrupt must be for a control read status
			 * stage packet.
			 */
			UDCDBG ("ACK on EP0 control read status stage packet");
			/* deselect EP0 rx FIFO */
			outw (0, UDC_EP_NUM);
		}
	} else if (status & UDC_STALL) {
		UDCDBG ("EP0 stall during RX");
		/* deselect EP0 rx FIFO */
		outw (0, UDC_EP_NUM);
	} else {
		/* deselect EP0 rx FIFO */
		outw (0, UDC_EP_NUM);
	}
}

static void omap1510_udc_ep0_tx (struct usb_endpoint_instance *endpoint)
{
	unsigned short status;
	struct usb_device_request *request = &ep0_urb->device_request;

	UDCDBG ("TX on EP0");
	/* select EP0 TX FIFO */
	outw (UDC_EP_Dir | UDC_EP_Sel, UDC_EP_NUM);

	status = inw (UDC_STAT_FLG);
	if (status & UDC_ACK) {
		/* Check direction */
		if ((request->bmRequestType & USB_REQ_DIRECTION_MASK) ==
		    USB_REQ_HOST2DEVICE) {
			/* This tx interrupt must be for a control write status
			 * stage packet.
			 */
			UDCDBG ("ACK on EP0 control write status stage packet");
			/* deselect EP0 TX FIFO */
			outw (UDC_EP_Dir, UDC_EP_NUM);
		} else {
			/* This tx interrupt must be for a control read data
			 * stage packet.
			 */
			int wLength = le16_to_cpu (request->wLength);

			/* Update our count of bytes sent so far in this
			 * transfer.
			 */
			endpoint->sent += endpoint->last;

			/* We are finished with this transfer if we have sent
			 * all of the bytes in our tx urb (urb->actual_length)
			 * unless we need a zero-length terminating packet.  We
			 * need a zero-length terminating packet if we returned
			 * fewer bytes than were requested (wLength) by the host,
			 * and the number of bytes we returned is an exact
			 * multiple of the packet size endpoint->tx_packetSize.
			 */
			if ((endpoint->sent == ep0_urb->actual_length)
			    && ((ep0_urb->actual_length == wLength)
				|| (endpoint->last !=
				    endpoint->tx_packetSize))) {
				/* Done with control read data stage. */
				UDCDBG ("control read data stage complete");
				/* deselect EP0 TX FIFO */
				outw (UDC_EP_Dir, UDC_EP_NUM);
				/* select EP0 RX FIFO to prepare for control
				 * read status stage.
				 */
				outw (UDC_EP_Sel, UDC_EP_NUM);
				/* clear the EP0 RX FIFO */
				outw (UDC_Clr_EP, UDC_CTRL);
				/* enable the EP0 RX FIFO */
				outw (UDC_Set_FIFO_En, UDC_CTRL);
				/* deselect the EP0 RX FIFO */
				outw (0, UDC_EP_NUM);
			} else {
				/* We still have another packet of data to send
				 * in this control read data stage or else we
				 * need a zero-length terminating packet.
				 */
				UDCDBG ("ACK control read data stage packet");
				omap1510_write_noniso_tx_fifo (endpoint);
				/* enable the EP0 tx FIFO to start transmission */
				outw (UDC_Set_FIFO_En, UDC_CTRL);
				/* deselect EP0 TX FIFO */
				outw (UDC_EP_Dir, UDC_EP_NUM);
			}
		}
	} else if (status & UDC_STALL) {
		UDCDBG ("EP0 stall during TX");
		/* deselect EP0 TX FIFO */
		outw (UDC_EP_Dir, UDC_EP_NUM);
	} else {
		/* deselect EP0 TX FIFO */
		outw (UDC_EP_Dir, UDC_EP_NUM);
	}
}

static void omap1510_udc_epn_rx (int ep)
{
	unsigned short status;

	/* Check endpoint status */
	status = inw (UDC_STAT_FLG);

	if (status & UDC_ACK) {
		int nbytes;
		struct usb_endpoint_instance *endpoint =
			omap1510_find_ep (ep);

		nbytes = omap1510_read_noniso_rx_fifo (endpoint);
		usbd_rcv_complete (endpoint, nbytes, 0);

		/* enable rx FIFO to prepare for next packet */
		outw (UDC_Set_FIFO_En, UDC_CTRL);
	} else if (status & UDC_STALL) {
		UDCDBGA ("STALL on RX endpoint %d", ep);
	} else if (status & UDC_NAK) {
		UDCDBGA ("NAK on RX ep %d", ep);
	} else {
		serial_printf ("omap-bi: RX on ep %d with status %x", ep,
			       status);
	}
}

static void omap1510_udc_epn_tx (int ep)
{
	unsigned short status;

	/*serial_printf("omap1510_udc_epn_tx( %x )\n",ep); */

	/* Check endpoint status */
	status = inw (UDC_STAT_FLG);

	if (status & UDC_ACK) {
		struct usb_endpoint_instance *endpoint =
			omap1510_find_ep (ep);

		/* We need to transmit a terminating zero-length packet now if
		 * we have sent all of the data in this URB and the transfer
		 * size was an exact multiple of the packet size.
		 */
		if (endpoint->tx_urb
		    && (endpoint->last == endpoint->tx_packetSize)
		    && (endpoint->tx_urb->actual_length - endpoint->sent -
			endpoint->last == 0)) {
			/* Prepare to transmit a zero-length packet. */
			endpoint->sent += endpoint->last;
			/* write 0 bytes of data to FIFO */
			omap1510_write_noniso_tx_fifo (endpoint);
			/* enable tx FIFO to start transmission */
			outw (UDC_Set_FIFO_En, UDC_CTRL);
		} else if (endpoint->tx_urb
			   && endpoint->tx_urb->actual_length) {
			/* retire the data that was just sent */
			usbd_tx_complete (endpoint);
			/* Check to see if we have more data ready to transmit
			 * now.
			 */
			if (endpoint->tx_urb
			    && endpoint->tx_urb->actual_length) {
				/* write data to FIFO */
				omap1510_write_noniso_tx_fifo (endpoint);
				/* enable tx FIFO to start transmission */
				outw (UDC_Set_FIFO_En, UDC_CTRL);
			}
		}
	} else if (status & UDC_STALL) {
		UDCDBGA ("STALL on TX endpoint %d", ep);
	} else if (status & UDC_NAK) {
		UDCDBGA ("NAK on TX endpoint %d", ep);
	} else {
		/*serial_printf("omap-bi: TX on ep %d with status %x\n", ep, status); */
	}
}



void omap1510_udc_irq (void)
{
	u16 irq_src = inw (UDC_IRQ_SRC);
	int valid_irq = 0;

	if (!(irq_src & ~UDC_SOF_Flg))	/* ignore SOF interrupts ) */
		return;

	UDCDBGA ("< IRQ #%d start >- %x", udc_interrupts, irq_src);
	/*serial_printf("< IRQ #%d start >- %x\n", udc_interrupts, irq_src); */

	if (irq_src & UDC_DS_Chg) {
		/* Device status changed */
		omap1510_udc_state_changed ();
		valid_irq++;
	}
	if (irq_src & UDC_EP0_RX) {
		/* Endpoint 0 receive */
		outw (UDC_EP0_RX, UDC_IRQ_SRC); /* ack interrupt */
		omap1510_udc_ep0_rx (udc_device->bus->endpoint_array + 0);
		valid_irq++;
	}
	if (irq_src & UDC_EP0_TX) {
		/* Endpoint 0 transmit */
		outw (UDC_EP0_TX, UDC_IRQ_SRC); /* ack interrupt */
		omap1510_udc_ep0_tx (udc_device->bus->endpoint_array + 0);
		valid_irq++;
	}
	if (irq_src & UDC_Setup) {
		/* Device setup */
		omap1510_udc_setup (udc_device->bus->endpoint_array + 0);
		valid_irq++;
	}
	/*if (!valid_irq) */
	/*	serial_printf("unknown interrupt, IRQ_SRC %.4x\n", irq_src); */
	UDCDBGA ("< IRQ #%d end >", udc_interrupts);
	udc_interrupts++;
}

/* This function implements TRM Figure 14-26. */
void omap1510_udc_noniso_irq (void)
{
	unsigned short epnum;
	unsigned short irq_src = inw (UDC_IRQ_SRC);
	int valid_irq = 0;

	if (!(irq_src & (UDC_EPn_RX | UDC_EPn_TX)))
		return;

	UDCDBGA ("non-ISO IRQ, IRQ_SRC %x", inw (UDC_IRQ_SRC));

	if (irq_src & UDC_EPn_RX) {	/* Endpoint N OUT transaction */
		/* Determine the endpoint number for this interrupt */
		epnum = (inw (UDC_EPN_STAT) & 0x0f00) >> 8;
		UDCDBGA ("RX on ep %x", epnum);

		/* acknowledge interrupt */
		outw (UDC_EPn_RX, UDC_IRQ_SRC);

		if (epnum) {
			/* select the endpoint FIFO */
			outw (UDC_EP_Sel | epnum, UDC_EP_NUM);

			omap1510_udc_epn_rx (epnum);

			/* deselect the endpoint FIFO */
			outw (epnum, UDC_EP_NUM);
		}
		valid_irq++;
	}
	if (irq_src & UDC_EPn_TX) {	/* Endpoint N IN transaction */
		/* Determine the endpoint number for this interrupt */
		epnum = (inw (UDC_EPN_STAT) & 0x000f) | USB_DIR_IN;
		UDCDBGA ("TX on ep %x", epnum);

		/* acknowledge interrupt */
		outw (UDC_EPn_TX, UDC_IRQ_SRC);

		if (epnum) {
			/* select the endpoint FIFO */
			outw (UDC_EP_Sel | UDC_EP_Dir | epnum, UDC_EP_NUM);

			omap1510_udc_epn_tx (epnum);

			/* deselect the endpoint FIFO */
			outw (UDC_EP_Dir | epnum, UDC_EP_NUM);
		}
		valid_irq++;
	}
	if (!valid_irq)
		serial_printf (": unknown non-ISO interrupt, IRQ_SRC %.4x\n",
			       irq_src);
}




/* Called to start packet transmission. */
int udc_endpoint_write (struct usb_endpoint_instance *endpoint)
{
	unsigned short epnum =
		endpoint->endpoint_address & USB_ENDPOINT_NUMBER_MASK;

	UDCDBGA ("Starting transmit on ep %x", epnum);

	if (endpoint->tx_urb) {
		/* select the endpoint FIFO */
		outw (UDC_EP_Sel | UDC_EP_Dir | epnum, UDC_EP_NUM);
		/* write data to FIFO */
		omap1510_write_noniso_tx_fifo (endpoint);
		/* enable tx FIFO to start transmission */
		outw (UDC_Set_FIFO_En, UDC_CTRL);
		/* deselect the endpoint FIFO */
		outw (UDC_EP_Dir | epnum, UDC_EP_NUM);
	}

	return 0;
}

/* Start to initialize h/w stuff */
int udc_init (void)
{
	u16 udc_rev;
	uchar value;
	ulong gpio;
	int i;

	/* Let the device settle down before we start */
	for (i = 0; i < UDC_INIT_MDELAY; i++) udelay(1000);

	udc_device = NULL;

	UDCDBG ("starting");

	/* Check peripheral reset. Must be 1 to make sure
	   MPU TIPB peripheral reset is inactive */
	UDCREG (ARM_RSTCT2);

	/* Set and check clock control.
	 * We might ought to be using the clock control API to do
	 * this instead of fiddling with the clock registers directly
	 * here.
	 */
	outw ((1 << 4) | (1 << 5), CLOCK_CTRL);
	UDCREG (CLOCK_CTRL);

#ifdef CONFIG_OMAP1510
	/* This code was originally implemented for OMAP1510 and
	 * therefore is only applicable for OMAP1510 boards. For
	 * OMAP5912 or OMAP16xx the register APLL_CTRL does not
	 * exist and DPLL_CTRL is already configured.
	 */

	/* Set and check APLL */
	outw (0x0008, APLL_CTRL);
	UDCREG (APLL_CTRL);
	/* Set and check DPLL */
	outw (0x2210, DPLL_CTRL);
	UDCREG (DPLL_CTRL);
#endif
	/* Set and check SOFT
	 * The below line of code has been changed to perform a
	 * read-modify-write instead of a simple write for
	 * configuring the SOFT_REQ register. This allows the code
	 * to be compatible with OMAP5912 and OMAP16xx devices
	 */
	outw ((1 << 4) | (1 << 3) | 1 | (inw(SOFT_REQ)), SOFT_REQ);

	/* Short delay to wait for DPLL */
	udelay (1000);

	/* Print banner with device revision */
	udc_rev = inw (UDC_REV) & 0xff;
#ifdef CONFIG_OMAP1510
	printf ("USB:   TI OMAP1510 USB function module rev %d.%d\n",
		udc_rev >> 4, udc_rev & 0xf);
#endif

#ifdef CONFIG_OMAP1610
	printf ("USB:   TI OMAP5912 USB function module rev %d.%d\n",
		udc_rev >> 4, udc_rev & 0xf);
#endif

#ifdef CONFIG_OMAP_SX1
	i2c_read (0x32, 0x04, 1, &value, 1);
	value |= 0x04;
	i2c_write (0x32, 0x04, 1, &value, 1);

	i2c_read (0x32, 0x03, 1, &value, 1);
	value |= 0x01;
	i2c_write (0x32, 0x03, 1, &value, 1);

	gpio = inl(GPIO_PIN_CONTROL_REG);
	gpio |=  0x0002; /* A_IRDA_OFF */
	gpio |=  0x0800; /* A_SWITCH   */
	gpio |=  0x8000; /* A_USB_ON   */
	outl (gpio, GPIO_PIN_CONTROL_REG);

	gpio = inl(GPIO_DIR_CONTROL_REG);
	gpio &= ~0x0002; /* A_IRDA_OFF */
	gpio &= ~0x0800; /* A_SWITCH   */
	gpio &= ~0x8000; /* A_USB_ON   */
	outl (gpio, GPIO_DIR_CONTROL_REG);

	gpio = inl(GPIO_DATA_OUTPUT_REG);
	gpio |=  0x0002; /* A_IRDA_OFF */
	gpio &= ~0x0800; /* A_SWITCH   */
	gpio &= ~0x8000; /* A_USB_ON   */
	outl (gpio, GPIO_DATA_OUTPUT_REG);
#endif

	/* The VBUS_MODE bit selects whether VBUS detection is done via
	 * software (1) or hardware (0).  When software detection is
	 * selected, VBUS_CTRL selects whether USB is not connected (0)
	 * or connected (1).
	 */
	outl (inl (FUNC_MUX_CTRL_0) | UDC_VBUS_MODE, FUNC_MUX_CTRL_0);
	outl (inl (FUNC_MUX_CTRL_0) & ~UDC_VBUS_CTRL, FUNC_MUX_CTRL_0);
	UDCREGL (FUNC_MUX_CTRL_0);

	/*
	 * At this point, device is ready for configuration...
	 */

	UDCDBG ("disable USB interrupts");
	outw (0, UDC_IRQ_EN);
	UDCREG (UDC_IRQ_EN);

	UDCDBG ("disable USB DMA");
	outw (0, UDC_DMA_IRQ_EN);
	UDCREG (UDC_DMA_IRQ_EN);

	UDCDBG ("initialize SYSCON1");
	outw (UDC_Self_Pwr | UDC_Pullup_En, UDC_SYSCON1);
	UDCREG (UDC_SYSCON1);

	return 0;
}

/* Stall endpoint */
static void udc_stall_ep (unsigned int ep_addr)
{
	/*int ep_addr = PHYS_EP_TO_EP_ADDR(ep); */
	int ep_num = ep_addr & USB_ENDPOINT_NUMBER_MASK;

	UDCDBGA ("stall ep_addr %d", ep_addr);

	/* REVISIT?
	 * The OMAP TRM section 14.2.4.2 says we must check that the FIFO
	 * is empty before halting the endpoint.  The current implementation
	 * doesn't check that the FIFO is empty.
	 */

	if (!ep_num) {
		outw (UDC_Stall_Cmd, UDC_SYSCON2);
	} else if ((ep_addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT) {
		if (inw (UDC_EP_RX (ep_num)) & UDC_EPn_RX_Valid) {
			/* we have a valid rx endpoint, so halt it */
			outw (UDC_EP_Sel | ep_num, UDC_EP_NUM);
			outw (UDC_Set_Halt, UDC_CTRL);
			outw (ep_num, UDC_EP_NUM);
		}
	} else {
		if (inw (UDC_EP_TX (ep_num)) & UDC_EPn_TX_Valid) {
			/* we have a valid tx endpoint, so halt it */
			outw (UDC_EP_Sel | UDC_EP_Dir | ep_num, UDC_EP_NUM);
			outw (UDC_Set_Halt, UDC_CTRL);
			outw (ep_num, UDC_EP_NUM);
		}
	}
}

/* Reset endpoint */
#if 0
static void udc_reset_ep (unsigned int ep_addr)
{
	/*int ep_addr = PHYS_EP_TO_EP_ADDR(ep); */
	int ep_num = ep_addr & USB_ENDPOINT_NUMBER_MASK;

	UDCDBGA ("reset ep_addr %d", ep_addr);

	if (!ep_num) {
		/* control endpoint 0 can't be reset */
	} else if ((ep_addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT) {
		UDCDBGA ("UDC_EP_RX(%d) = 0x%04x", ep_num,
			 inw (UDC_EP_RX (ep_num)));
		if (inw (UDC_EP_RX (ep_num)) & UDC_EPn_RX_Valid) {
			/* we have a valid rx endpoint, so reset it */
			outw (ep_num | UDC_EP_Sel, UDC_EP_NUM);
			outw (UDC_Reset_EP, UDC_CTRL);
			outw (ep_num, UDC_EP_NUM);
			UDCDBGA ("OUT endpoint %d reset", ep_num);
		}
	} else {
		UDCDBGA ("UDC_EP_TX(%d) = 0x%04x", ep_num,
			 inw (UDC_EP_TX (ep_num)));
		/* Resetting of tx endpoints seems to be causing the USB function
		 * module to fail, which causes problems when the driver is
		 * uninstalled.	 We'll skip resetting tx endpoints for now until
		 * we figure out what the problem is.
		 */
#if 0
		if (inw (UDC_EP_TX (ep_num)) & UDC_EPn_TX_Valid) {
			/* we have a valid tx endpoint, so reset it */
			outw (ep_num | UDC_EP_Dir | UDC_EP_Sel, UDC_EP_NUM);
			outw (UDC_Reset_EP, UDC_CTRL);
			outw (ep_num | UDC_EP_Dir, UDC_EP_NUM);
			UDCDBGA ("IN endpoint %d reset", ep_num);
		}
#endif
	}
}
#endif

/* ************************************************************************** */

#if 0
int udc_check_ep (int logical_endpoint, int packetsize)
{
	if ((logical_endpoint == 0x80) ||
	    ((logical_endpoint & 0x8f) != logical_endpoint)) {
		return 0;
	}

	switch (packetsize) {
	case 8:
	case 16:
	case 32:
	case 64:
	case 128:
	case 256:
	case 512:
		break;
	default:
		return 0;
	}

	return EP_ADDR_TO_PHYS_EP (logical_endpoint);
}
#endif

void udc_setup_ep (struct usb_device_instance *device,
		   unsigned int ep, struct usb_endpoint_instance *endpoint)
{
	UDCDBGA ("setting up endpoint addr %x", endpoint->endpoint_address);

	/* This routine gets called by bi_modinit for endpoint 0 and from
	 * bi_config for all of the other endpoints.  bi_config gets called
	 * during the DEVICE_CREATE, DEVICE_CONFIGURED, and
	 * DEVICE_SET_INTERFACE events.	 We need to reconfigure the OMAP packet
	 * RAM after bi_config scans the selected device configuration and
	 * initializes the endpoint structures, but before this routine enables
	 * the OUT endpoint FIFOs.  Since bi_config calls this routine in a
	 * loop for endpoints 1 through UDC_MAX_ENDPOINTS, we reconfigure our
	 * packet RAM here when ep==1.
	 * I really hate to do this here, but it seems like the API exported
	 * by the USB bus interface controller driver to the usbd-bi module
	 * isn't quite right so there is no good place to do this.
	 */
	if (ep == 1) {
		omap1510_deconfigure_device ();
		omap1510_configure_device (device);
	}

	if (endpoint && (ep < UDC_MAX_ENDPOINTS)) {
		int ep_addr = endpoint->endpoint_address;

		if (!ep_addr) {
			/* nothing to do for endpoint 0 */
		} else if ((ep_addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN) {
			/* nothing to do for IN (tx) endpoints */
		} else {	/* OUT (rx) endpoint */
			if (endpoint->rcv_packetSize) {
				/*struct urb* urb = &(urb_out_array[ep&0xFF]); */
				/*urb->endpoint = endpoint; */
				/*urb->device = device; */
				/*urb->buffer_length = sizeof(urb->buffer); */

				/*endpoint->rcv_urb = urb; */
				omap1510_prepare_endpoint_for_rx (ep_addr);
			}
		}
	}
}

#if 0
void udc_disable_ep (unsigned int ep_addr)
{
	/*int ep_addr = PHYS_EP_TO_EP_ADDR(ep); */
	int ep_num = ep_addr & USB_ENDPOINT_NUMBER_MASK;
	struct usb_endpoint_instance *endpoint = omap1510_find_ep (ep_addr);	/*udc_device->bus->endpoint_array + ep; */

	UDCDBGA ("disable ep_addr %d", ep_addr);

	if (!ep_num) {
		/* nothing to do for endpoint 0 */ ;
	} else if ((ep_addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN) {
		if (endpoint->tx_packetSize) {
			/* we have a valid tx endpoint */
			/*usbd_flush_tx(endpoint); */
			endpoint->tx_urb = NULL;
		}
	} else {
		if (endpoint->rcv_packetSize) {
			/* we have a valid rx endpoint */
			/*usbd_flush_rcv(endpoint); */
			endpoint->rcv_urb = NULL;
		}
	}
}
#endif

/* ************************************************************************** */

#if 0
int udc_connected (void)
{
	return ((inw (UDC_DEVSTAT) & UDC_ATT) == UDC_ATT);
}
#endif

/* Turn on the USB connection by enabling the pullup resistor */
void udc_connect (void)
{
	UDCDBG ("connect, enable Pullup");
	outl (0x00000018, FUNC_MUX_CTRL_D);
}

/* Turn off the USB connection by disabling the pullup resistor */
void udc_disconnect (void)
{
	UDCDBG ("disconnect, disable Pullup");
	outl (0x00000000, FUNC_MUX_CTRL_D);
}

/* ************************************************************************** */


#if 0
void udc_disable_interrupts (struct usb_device_instance *device)
{
	UDCDBG ("disabling all interrupts");
	outw (0, UDC_IRQ_EN);
}
#endif

/* ************************************************************************** */

#if 0
int udc_ep0_packetsize (void)
{
	return EP0_PACKETSIZE;
}
#endif

/* Switch on the UDC */
void udc_enable (struct usb_device_instance *device)
{
	UDCDBGA ("enable device %p, status %d", device, device->status);

	/* initialize driver state variables */
	udc_devstat = 0;

	/* Save the device structure pointer */
	udc_device = device;

	/* Setup ep0 urb */
	if (!ep0_urb) {
		ep0_urb =
			usbd_alloc_urb (udc_device,
					udc_device->bus->endpoint_array);
	} else {
		serial_printf ("udc_enable: ep0_urb already allocated %p\n",
			       ep0_urb);
	}

	UDCDBG ("Check clock status");
	UDCREG (STATUS_REQ);

	/* The VBUS_MODE bit selects whether VBUS detection is done via
	 * software (1) or hardware (0).  When software detection is
	 * selected, VBUS_CTRL selects whether USB is not connected (0)
	 * or connected (1).
	 */
	outl (inl (FUNC_MUX_CTRL_0) | UDC_VBUS_CTRL | UDC_VBUS_MODE,
	      FUNC_MUX_CTRL_0);
	UDCREGL (FUNC_MUX_CTRL_0);

	omap1510_configure_device (device);
}

/* Switch off the UDC */
void udc_disable (void)
{
	UDCDBG ("disable UDC");

	omap1510_deconfigure_device ();

	/* The VBUS_MODE bit selects whether VBUS detection is done via
	 * software (1) or hardware (0).  When software detection is
	 * selected, VBUS_CTRL selects whether USB is not connected (0)
	 * or connected (1).
	 */
	outl (inl (FUNC_MUX_CTRL_0) | UDC_VBUS_MODE, FUNC_MUX_CTRL_0);
	outl (inl (FUNC_MUX_CTRL_0) & ~UDC_VBUS_CTRL, FUNC_MUX_CTRL_0);
	UDCREGL (FUNC_MUX_CTRL_0);

	/* Free ep0 URB */
	if (ep0_urb) {
		/*usbd_dealloc_urb(ep0_urb); */
		ep0_urb = NULL;
	}

	/* Reset device pointer.
	 * We ought to do this here to balance the initialization of udc_device
	 * in udc_enable, but some of our other exported functions get called
	 * by the bus interface driver after udc_disable, so we have to hang on
	 * to the device pointer to avoid a null pointer dereference. */
	/* udc_device = NULL; */
}

void udc_startup_events (struct usb_device_instance *device)
{
	/* The DEVICE_INIT event puts the USB device in the state STATE_INIT. */
	usbd_device_event_irq (device, DEVICE_INIT, 0);

	/* The DEVICE_CREATE event puts the USB device in the state
	 * STATE_ATTACHED.
	 */
	usbd_device_event_irq (device, DEVICE_CREATE, 0);

	/* Some USB controller driver implementations signal
	 * DEVICE_HUB_CONFIGURED and DEVICE_RESET events here.
	 * DEVICE_HUB_CONFIGURED causes a transition to the state STATE_POWERED,
	 * and DEVICE_RESET causes a transition to the state STATE_DEFAULT.
	 * The OMAP USB client controller has the capability to detect when the
	 * USB cable is connected to a powered USB bus via the ATT bit in the
	 * DEVSTAT register, so we will defer the DEVICE_HUB_CONFIGURED and
	 * DEVICE_RESET events until later.
	 */

	udc_enable (device);
}

void udc_irq(void)
{
	/* Loop while we have interrupts.
	 * If we don't do this, the input chain
	 * polling delay is likely to miss
	 * host requests.
	 */
	while (inw (UDC_IRQ_SRC) & ~UDC_SOF_Flg) {
		/* Handle any new IRQs */
		omap1510_udc_irq ();
		omap1510_udc_noniso_irq ();
	}
}

/* Flow control */
void udc_set_nak(int epid)
{
	/* TODO: implement this functionality in omap1510 */
}

void udc_unset_nak (int epid)
{
	/* TODO: implement this functionality in omap1510 */
}
