#include "led.h"


void LED_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
			/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		/*�ر�����led*/
		GPIO_SetBits(GPIOA, GPIO_Pin_9);
}

