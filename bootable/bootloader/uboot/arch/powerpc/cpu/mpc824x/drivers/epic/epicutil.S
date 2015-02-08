

#include <ppc_asm.tmpl>
#include <ppc_defs.h>

      .text
      .align 2
      .global load_runtime_reg

load_runtime_reg:

		  xor r5,r5,r5
	  or  r5,r5,r3       /* save eumbbar */

	      lwbrx	r3,r4,r5
	      sync

	      bclr 20, 0

	   .text
	   .align 2
	   .global store_runtime_reg
store_runtime_reg:

		  xor r0,r0,r0

	      stwbrx r5,  r4, r3
	      sync

		  bclr   20,0
