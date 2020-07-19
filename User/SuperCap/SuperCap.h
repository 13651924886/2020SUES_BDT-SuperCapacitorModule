#ifndef __SUPER_CAP_H__
#define __SUPER_CAP_H__

#include "stm32f10x.h"
#include "can.h"
#include "bsp_usart.h"
#include "bsp_adc.h"


/* 选择用外部MCU控制还是用单独的遥控器控制，前者用于实战后者用于测试 */
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
	Power_State_e buck_module_mode;				//功率控制板的状态
	Power_State_e boost_module_mode;
	uint8_t board_current;		//功率控制板的电流检测
	
}	PowerControlBoard_t;

typedef struct
{
		const RC_Ctl_t *rc_ctrl;	//遥控器指针
	
		const extended_mcu_msg_t *master_mcu_message;
		
		PowerControlBoard_t PowerControl; // 功率控制板状态信息
	
		float voltage;		//超级电容的电压 
	
		float Boost_voltage;

} SuperCap_Control_t;


extern void SuperCapControl_Init(void);
extern void SuperCapControl_Task(void);






#endif


