


#ifndef IxEthDBPortDefs_H
#define IxEthDBPortDefs_H

typedef enum
{
    IX_ETH_GENERIC = 0, /**< generic ethernet port */
    IX_ETH_NPE          /**< specific Ethernet NPE */
} IxEthDBPortType;

typedef enum
{
    IX_ETH_NO_CAPABILITIES = 0,   /**< no aging capabilities */
    IX_ETH_ENTRY_AGING     = 0x1  /**< aging capabilities present */
} IxEthDBPortCapability;

typedef struct
{
    IxEthDBPortType type;
    IxEthDBPortCapability capabilities;
} IxEthDBPortDefinition;

static const IxEthDBPortDefinition ixEthDBPortDefinitions[] = 
{
    /*    id       type              capabilities */
    {   /* 0 */    IX_ETH_NPE,       IX_ETH_NO_CAPABILITIES },    /* Ethernet NPE B */
    {   /* 1 */    IX_ETH_NPE,       IX_ETH_NO_CAPABILITIES },    /* Ethernet NPE C */
    {   /* 2 */    IX_ETH_NPE,       IX_ETH_NO_CAPABILITIES },    /* Ethernet NPE A */
    {   /* 3 */    IX_ETH_GENERIC,   IX_ETH_NO_CAPABILITIES },    /* WAN port */
};

#define IX_ETH_DB_NUMBER_OF_PORTS (sizeof (ixEthDBPortDefinitions) / sizeof (ixEthDBPortDefinitions[0]))

#define IX_ETH_DB_UNKNOWN_PORT (0xff)

#define IX_ETH_DB_ALL_PORTS (IX_ETH_DB_NUMBER_OF_PORTS + 1)

#define IX_ETH_DB_PORTS_ASSERTION { switch(0) { case 0 : ; case 1 : ; case IX_ETH_DB_NUMBER_OF_PORTS : ; }}

#define IX_ETH_DB_CHECK_PORT(portID) \
{ \
  if ((portID) >= IX_ETH_DB_NUMBER_OF_PORTS) \
  { \
      return IX_ETH_DB_INVALID_PORT; \
  } \
  \
  if (!ixEthDBPortInfo[(portID)].enabled) \
  { \
      return IX_ETH_DB_PORT_UNINITIALIZED; \
  } \
}

#define IX_ETH_DB_CHECK_PORT_ALL(portID) \
{ \
  if ((portID) != IX_ETH_DB_ALL_PORTS) \
    IX_ETH_DB_CHECK_PORT(portID) \
}

#endif /* IxEthDBPortDefs_H */
