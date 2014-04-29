#include "delay.h"

/**
  * @brief  Delay ms
  * @param  ms
  * @retval None
  */
void delay_ms(uint16 ms)
{
	uint16 i=0, j=0, k=0;
	
#if (PLL_200 == CORE_CLK_MHZ)
	for (k=0; k<ms; ++k) {
		for (i=0; i<100; ++i) {
			for (j=0; j<398; ++j)
				;
		}
	}
#else
	ASSERT(0);
#endif
}