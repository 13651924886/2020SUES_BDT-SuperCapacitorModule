#ifndef MAIN_H
#define MAIN_H

#include "stm32f10x.h"
#include "stdint.h"

//ѡ��ϵͳʱ��
#define SysCoreClock 72
//ѡ���ж����ȼ�
#define RC_NVIC 4
#define CAN1_NVIC 4
#define CAN2_NVIC 4
#define TIM3_NVIC 5
#define TIM6_NVIC 4
#define SPI5_RX_NVIC 5
#define MPU_INT_NVIC 5
#define PUSH_WHEEL_INT_NVIC 5
#define TRIGGER_WHEEL_INT_NVIC 5
#define UART8_NVIC 1	// ����IMU
#define USART6_NVIC 7	// ����ϵͳ�û��ӿ�


#endif

