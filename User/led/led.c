#include "led.h"


void LED_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
			/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		/*关闭所有led*/
		GPIO_SetBits(GPIOA, GPIO_Pin_9);
}


