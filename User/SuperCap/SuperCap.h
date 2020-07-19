#ifndef __SUPER_CAP_H__
#define __SUPER_CAP_H__

#include "stm32f10x.h"
#include "can.h"
#include "bsp_usart.h"
#include "bsp_adc.h"


/* ѡ�����ⲿMCU���ƻ����õ�����ң�������ƣ�ǰ������ʵս�������ڲ��� */
#define MASTER_MCU_CONTROL
//#define RC_CONTROL 

typedef enum
{
	Waiting = 0,
	Charging = 1,
	Discharging,
	
}	Power_State_e;


typedef struct
{
	Power_State_e buck_module_mode;				//���ʿ��ư��״̬
	Power_State_e boost_module_mode;
	uint8_t board_current;		//���ʿ��ư�ĵ������
	
}	PowerControlBoard_t;

typedef struct
{
		const RC_Ctl_t *rc_ctrl;	//ң����ָ��
	
		const extended_mcu_msg_t *master_mcu_message;
		
		PowerControlBoard_t PowerControl; // ���ʿ��ư�״̬��Ϣ
	
		float voltage;		//�������ݵĵ�ѹ 
	
		float Boost_voltage;

} SuperCap_Control_t;


extern void SuperCapControl_Init(void);
extern void SuperCapControl_Task(void);






#endif


