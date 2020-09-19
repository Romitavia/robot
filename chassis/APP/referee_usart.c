#include "referee_usart.h"

#include <stdio.h>
#include <string.h>

#include "freertos.h"
#include "task.h"

#include "referee.h"
#include "referee_send.h"
#include "dma.h"
#include "bsp_usart.h"
#include "bsp_can.h"
#include "led.h"

#define RE_huart  huart1
#define RE_UART		USART1
#define RE_dma_rx		hdma_usart1_rx
#define RE_dma_tx   hdma_usart1_tx


//����ԭʼ���ݣ�Ϊ18���ֽڣ�����36���ֽڳ��ȣ���ֹDMA����Խ��
static uint8_t referee_rx_buf[2][REFEREE_RX_BUF_NUM];
uint8_t referee_rx_data[REFEREE_RX_BUF_NUM];
static void REFEREE_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num);

uint8_t canTX_gimbal(int8_t robot_id, int16_t heat0, int16_t heat0_limit ,int16_t bullet_speed, uint8_t bullet_speedlimit);


void Referee_Usart_Task(void const * argument)
{
		
		referee_usart_init();
		UI_init();
	
		portTickType currentTime;
		currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
		while(1)
		{
			led_blin(4,&led[3]);
			/*������������*/
			referee_data_solve(referee_rx_data);
			/*************/
			
			/*���������ϴ�����*/
			UI_show();
			/*************/
			
			/*����̨��ֵ*/
			uint8_t id,bullet_freq,bullet_speedlimit;
			uint16_t heat0_limit, heat0;
			float bullet_speed;
			get_shoot_heat0_limit_and_heat0(&heat0_limit,	&heat0);
			get_shoot_data(&bullet_freq, &bullet_speed,&bullet_speedlimit);
			id = get_robot_id();
			canTX_gimbal(id, heat0 ,heat0_limit, bullet_speed, bullet_speedlimit);
			/************/	


			
			vTaskDelayUntil(&currentTime,15);
		}
}

//��������ʼ������
void referee_usart_init(void)
{
    REFEREE_init(referee_rx_buf[0], referee_rx_buf[1], REFEREE_RX_BUF_NUM);
}

static void REFEREE_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
{
		//enable the DMA transfer for the receiver request
		//ʹ�� DMA ���ڽ���
		SET_BIT(RE_huart.Instance->CR3, USART_CR3_DMAR);
		SET_BIT(RE_huart.Instance->CR3, USART_CR3_DMAT);
		//enalbe idle interrupt
		//ʹ�ܿ����ж�
		__HAL_UART_ENABLE_IT(&RE_huart, UART_IT_IDLE);
		//disable DMA
		//ʧЧ DMA
		__HAL_DMA_DISABLE(&RE_dma_rx);
	
		while(RE_dma_rx.Instance->CR & DMA_SxCR_EN)
		{
				__HAL_DMA_DISABLE(&RE_dma_rx);
		}
		__HAL_DMA_CLEAR_FLAG(&RE_dma_rx, DMA_LISR_TCIF2);
		
		RE_dma_rx.Instance->PAR = (uint32_t) & (RE_UART->DR);
		//memory buffer 1
		//�ڴ滺���� 1
		RE_dma_rx.Instance->M0AR = (uint32_t)(rx1_buf);
		//memory buffer 2
		//�ڴ滺���� 2
		RE_dma_rx.Instance->M1AR = (uint32_t)(rx2_buf);
		//data length
		//���ݳ���
		RE_dma_rx.Instance->NDTR = dma_buf_num;
		//enable double memory buffer
		//ʹ��˫������
		SET_BIT(RE_dma_rx.Instance->CR, DMA_SxCR_DBM);
		//enable DMA
		//ʹ�� DMA
		__HAL_DMA_ENABLE(&RE_dma_rx);
		
		//disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(&RE_dma_tx);

    while(RE_dma_tx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&RE_dma_tx);
    }

    RE_dma_tx.Instance->PAR = (uint32_t) & (RE_UART->DR);
}


//д��stm32f4xx_it.c����usart1�ж�
void RE_IRQHandler(void)
{
		led_blin(50,&led[2]);
	
		static volatile uint8_t res;
		if(RE_huart.Instance->SR & UART_FLAG_RXNE)//���յ�����
		{
				__HAL_UART_CLEAR_PEFLAG(&RE_huart);
		}
		else if(RE_UART->SR & UART_FLAG_IDLE)
		{
				static uint16_t this_time_rx_len = 0;
			
				__HAL_UART_CLEAR_PEFLAG(&RE_huart);
			
				if ((RE_dma_rx.Instance->CR & DMA_SxCR_CT) == RESET)
				{
						/* Current memory buffer used is Memory 0 */
						//disable DMA
						//ʧЧ DMA
						__HAL_DMA_DISABLE(&RE_dma_rx);
						//get receive data length, length = set_data_length - remain_length
						//��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
						this_time_rx_len = REFEREE_RX_BUF_NUM - RE_dma_rx.Instance->NDTR;
						//reset set_data_lenght
						//�����趨���ݳ���
						RE_dma_rx.Instance->NDTR = REFEREE_RX_BUF_NUM;
						//set memory buffer 1
						//�趨������ 1
						RE_dma_rx.Instance->CR |= DMA_SxCR_CT;
						//enable DMA
						//ʹ�� DMA
						__HAL_DMA_ENABLE(&RE_dma_rx);
					
//						referee_data_solve(referee_rx_buf[0]);
						memcpy(referee_rx_data,referee_rx_buf[0],REFEREE_RX_BUF_NUM);
						memset(referee_rx_buf[0], 0, REFEREE_RX_BUF_NUM);
				}
				else
				{
						/* Current memory buffer used is Memory 1 */
						//disable DMA
						//ʧЧ DMA
						__HAL_DMA_DISABLE(&RE_dma_rx);
						//get receive data length, length = set_data_length - remain_length
						//��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
						this_time_rx_len = REFEREE_RX_BUF_NUM - RE_dma_rx.Instance->NDTR;
						//reset set_data_lenght
						//�����趨���ݳ���
						RE_dma_rx.Instance->NDTR = REFEREE_RX_BUF_NUM;
						//set memory buffer 0
						//�趨������ 0
						DMA1_Stream1->CR &= ~(DMA_SxCR_CT);
						//enable DMA
						//ʹ�� DMA
						__HAL_DMA_ENABLE(&RE_dma_rx);
					
//						referee_data_solve(referee_rx_buf[1]);
						memcpy(referee_rx_data,referee_rx_buf[1],REFEREE_RX_BUF_NUM);
						memset(referee_rx_buf[1], 0, REFEREE_RX_BUF_NUM);
				}
			}
}

/*���ڷ���*/
void RE_usart_tx_dma_enable(uint8_t *data, uint16_t len)
{
    //disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(&RE_dma_tx);

    while(RE_dma_tx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&RE_dma_tx);
    }

    __HAL_DMA_CLEAR_FLAG(&RE_dma_tx, DMA_HISR_TCIF7);

    RE_dma_tx.Instance->M0AR = (uint32_t)(data);
    __HAL_DMA_SET_COUNTER(&RE_dma_tx, len);

    __HAL_DMA_ENABLE(&RE_dma_tx);
}


uint8_t canTX_gimbal(int8_t robot_id, int16_t heat0, int16_t heat0_limit ,int16_t bullet_speed, uint8_t bullet_speedlimit)
{
	CAN_TxHeaderTypeDef canFrame;
	uint8_t data[8]={0};
	uint32_t temp=0;
	
	canFrame.IDE=CAN_ID_STD;
	canFrame.StdId=0x006;
	canFrame.RTR=CAN_RTR_DATA;
	canFrame.DLC=8;
	canFrame.TransmitGlobalTime=DISABLE;
	data[0]=robot_id;
	data[1]=heat0>>8;
	data[2]=heat0&0xff;
	data[3]=heat0_limit>>8;
	data[4]=heat0_limit&0xff;
	data[5]=bullet_speed>>8;
	data[6]=bullet_speed&0xff;
	data[7]=bullet_speedlimit;
	HAL_CAN_AddTxMessage(&hcan2, &canFrame, data,&temp);
	
	return temp;	
}
