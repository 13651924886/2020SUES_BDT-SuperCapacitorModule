#ifndef _CAN_H_
#define _CAN_H_

#include "main.h"

#define CHASSIS_CAN CAN1
#define GIMBAL_CAN CAN1
#define EXTENDED_MCU_CAN CAN1


typedef enum
{	
		CAN_Master_MCU_ID = 0x301,	//机器人上主控单片机的消息报文ID
		CAN_Super_Power_MCU_ID = 0x302,

} can_msg_id_e;


typedef struct
{
		uint8_t msg1;
		uint8_t msg2;
		uint8_t	msg3;
		uint8_t	msg4;
		uint8_t msg5;
		uint8_t msg6;
		uint8_t msg7;
		uint8_t msg8;
	
		
} extended_mcu_msg_t;

const extended_mcu_msg_t *get_Master_Mcu_Msg_Point(void);

void CAN_mode_init(uint8_t tsjw, uint8_t tbs2, uint8_t tbs1, uint16_t brp, uint8_t mode);
void CAN_CMD_Master_MCU(uint8_t msg1, uint8_t msg2, uint8_t msg3, uint8_t msg4,uint8_t msg5,uint8_t msg6,uint8_t msg7,uint8_t msg8);

#endif

