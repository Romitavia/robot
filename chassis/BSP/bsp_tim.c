#include "bsp_tim.h"

/*
	tim6 ��ʱ����
*/

void BSP_delayInit(void)
{
	MX_TIM6_Init();
	HAL_TIM_Base_Start(&htim6);
}

void DELAY_us(uint16_t us)  //���780us
{
		htim6.Instance->CNT=0;
		while(htim6.Instance->CNT<us*84);
}
