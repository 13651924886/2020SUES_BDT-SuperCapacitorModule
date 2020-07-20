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
    delay_ms(100);// 保证前面运行
		Scheduler_Setup();// 软件（变量）初始化：创建任务（线程）、创建调度器		
		while(1)
		{	
       Scheduler_Run();			//运行任务调度器，所有系统功能，除了中断服务函数，都在任务调度器内完成 ;
		}	
}

void BSP_init(void)
{
		delay_init();	    	 //延时函数初始化	 
		USART3_DMA_Config();//USART3+DMA RX:PB11
		ADCx_Init();//ADC
		CAN_mode_init(CAN_SJW_1tq, CAN_BS1_3tq, CAN_BS2_2tq, 6, CAN_Mode_Normal);
		SuperCapControl_Init();
		OLED_Init();
		OLED_Clear();
}
/*********************************************END OF FILE**********************/
