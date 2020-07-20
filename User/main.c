#include "bsp_usart.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "bmp.h"
#include "SuperCap.h"
#include "can.h"
#include "bsp_adc.h"
#include "start_task.h"  // test

void BSP_init(void);


int main(void)
{	
		BSP_init();
    delay_ms(100);// ��֤ǰ������
		Scheduler_Setup();// �������������ʼ�������������̣߳�������������		
		while(1)
		{	
       Scheduler_Run();			//�������������������ϵͳ���ܣ������жϷ������������������������� ;
		}	
}

void BSP_init(void)
{
		delay_init();	    	 //��ʱ������ʼ��	 
		USART3_DMA_Config();//USART3+DMA RX:PB11
		ADCx_Init();//ADC
		CAN_mode_init(CAN_SJW_1tq, CAN_BS1_3tq, CAN_BS2_2tq, 6, CAN_Mode_Normal);
		SuperCapControl_Init();
		OLED_Init();
		OLED_Clear();
}
/*********************************************END OF FILE**********************/
