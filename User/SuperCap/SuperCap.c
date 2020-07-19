#include "SuperCap.h"

// public
SuperCap_Control_t supercap_control;
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// private
static void SuperCapControl_GPIO_Init(void);
static void SuperCapControl_Set_Mode(SuperCap_Control_t *SuperCap_control);
static void SuperCapControl_Mode_Change_Transit(SuperCap_Control_t *SuperCap_control);
static void SuperCapControl_Feedback_Update(SuperCap_Control_t *SuperCap_control);
static void SuperCapControl_Set_Control(SuperCap_Control_t *SuperCap_control);
static void SuperCapControl_Data_Transmit(SuperCap_Control_t *SuperCap_control);

static void SuperCap_Charge_On(void);
static void SuperCap_Charge_Off(void);
static void SuperCap_Discharge_On(void);
static void SuperCap_Discharge_Off(void);


//PB0充电
//PB1放电
//均为高电平触发
void SuperCapControl_Init(void)
{
		SuperCapControl_GPIO_Init();
		
		supercap_control.rc_ctrl = get_remote_control_point();
	
		supercap_control.master_mcu_message = get_Master_Mcu_Msg_Point();
		
		supercap_control.PowerControl.board_current = 0;
		supercap_control.PowerControl.buck_module_mode = Waiting;
		supercap_control.PowerControl.boost_module_mode = Waiting;
	
		supercap_control.voltage = 0.0f;
	
		supercap_control.Boost_voltage = 0.0f;
		
}

void SuperCapControl_Task(void)
{
		SuperCapControl_Set_Mode(&supercap_control);
		SuperCapControl_Mode_Change_Transit(&supercap_control);
		SuperCapControl_Feedback_Update(&supercap_control);
		SuperCapControl_Set_Control(&supercap_control);
		SuperCapControl_Data_Transmit(&supercap_control);
}

static void SuperCapControl_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
		GPIO_Init(GPIOB, &GPIO_InitStructure);	

		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		
}

static void SuperCapControl_Set_Mode(SuperCap_Control_t *SuperCap_control)
{
	  if (SuperCap_control == NULL) return;
#ifdef MASTER_MCU_CONTROL	
		switch (SuperCap_control->master_mcu_message->msg2)
    {
			case 0:SuperCap_control->PowerControl.boost_module_mode = Waiting;	break;
			case 2:SuperCap_control->PowerControl.boost_module_mode =	Discharging; break;
			default:  break;
    }
		
		switch (SuperCap_control->master_mcu_message->msg1)
    {
			case 0:SuperCap_control->PowerControl.buck_module_mode = 	Waiting;	break;
			case 1:SuperCap_control->PowerControl.buck_module_mode =	Charging; break;
			default:  break;
    }
#endif
	
#ifdef RC_CONTROL
		switch (SuperCap_control->rc_ctrl->rc.s2)	//右杆 控制升压模块
    {
			case 2|3: SuperCap_control->PowerControl.boost_module_mode = 	Waiting;		 break;
			case 1:		SuperCap_control->PowerControl.boost_module_mode =	Discharging; break;
			default:  break;
    }
		
		switch (SuperCap_control->rc_ctrl->rc.s1)	//左杆 控制降压模块
    {
			case 2|3: SuperCap_control->PowerControl.buck_module_mode = 	Waiting;		 break;
			case 1:		SuperCap_control->PowerControl.buck_module_mode =		Charging; break;
			default:  break;
    }
#endif		
}

static void SuperCapControl_Mode_Change_Transit(SuperCap_Control_t *SuperCap_control)
{
    if (SuperCap_control == NULL)	return;
	
		
		
}

static void SuperCapControl_Feedback_Update(SuperCap_Control_t *SuperCap_control)
{
    if (SuperCap_control == NULL) return;		
		SuperCap_control->PowerControl.board_current = (float) ADC_ConvertedValue[0]/4096*3.3;
		SuperCap_control->voltage = ((float) ADC_ConvertedValue[1]/4096*3.3)*7.0606f;
		SuperCap_control->Boost_voltage = ((float) ADC_ConvertedValue[2]/4096*3.3)*11.0f;
}

static void SuperCapControl_Set_Control(SuperCap_Control_t *SuperCap_control)
{
    if (SuperCap_control == NULL) return;
	 		
		switch (SuperCap_control->PowerControl.boost_module_mode)
    {
			case Waiting:			SuperCap_Discharge_Off();	break;
			case Discharging:	SuperCap_Discharge_On(); 	break;
			default:  break;
    }
		
		switch (SuperCap_control->PowerControl.buck_module_mode)
    {
			case Waiting:			SuperCap_Charge_Off();	break;
			case Charging:		SuperCap_Charge_On(); 	break;
			default:  break;
    }		
		
}


static void SuperCap_Charge_On(void)
{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
static void SuperCap_Charge_Off(void)
{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

static void SuperCap_Discharge_On(void)
{
		GPIO_SetBits(GPIOB, GPIO_Pin_1);

}
static void SuperCap_Discharge_Off(void)
{
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}

static void SuperCapControl_Data_Transmit(SuperCap_Control_t *SuperCap_control)
{
		uint8_t msg1 = SuperCap_control->PowerControl.boost_module_mode;	//升压模块，即discharge mode
		uint8_t	msg2 = SuperCap_control->PowerControl.buck_module_mode;		//降压模块，即charge mode
		uint8_t	msg3 = ((uint16_t) (SuperCap_control->voltage * 100.0f)) >> 8;	
		uint8_t	msg4 = (uint16_t) (SuperCap_control->voltage * 100.0f);	
		uint8_t	msg5 = SuperCap_control->PowerControl.buck_module_mode;	
		uint8_t	msg6 = SuperCap_control->PowerControl.buck_module_mode;	
		uint8_t	msg7 = SuperCap_control->PowerControl.buck_module_mode;	
		uint8_t	msg8 = SuperCap_control->PowerControl.buck_module_mode;	
	
	  CAN_CMD_Master_MCU( msg1,  msg2,  msg3,  msg4, msg5, msg6, msg7, msg8);		
}	

