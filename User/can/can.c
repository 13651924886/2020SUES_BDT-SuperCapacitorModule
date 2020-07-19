#include "can.h"

#define get_motor_measure(ptr, rx_message)                                                     \
    {                                                                                          \
        (ptr)->last_ecd = (ptr)->ecd;                                                          \
        (ptr)->ecd = (uint16_t)((rx_message)->Data[0] << 8 | (rx_message)->Data[1]);           \
        (ptr)->speed_rpm = (uint16_t)((rx_message)->Data[2] << 8 | (rx_message)->Data[3]);     \
        (ptr)->given_current = (uint16_t)((rx_message)->Data[4] << 8 | (rx_message)->Data[5]); \
        (ptr)->temperate = (rx_message)->Data[6];                                              \
    }
#define get_gimbal_motor_measuer(ptr, rx_message)                                              \
    {                                                                                          \
        (ptr)->last_ecd = (ptr)->ecd;                                                          \
        (ptr)->ecd = (uint16_t)((rx_message)->Data[0] << 8 | (rx_message)->Data[1]);           \
        (ptr)->given_current = (uint16_t)((rx_message)->Data[2] << 8 | (rx_message)->Data[3]); \
        (ptr)->speed_rpm = (uint16_t)((rx_message)->Data[4] << 8 | (rx_message)->Data[5]);     \
        (ptr)->temperate = (rx_message)->Data[6];                                              \
    }

#define get_master_mcu_msg(ptr, rx_message)																							\
		{																																													\
				(ptr)->msg1 = (rx_message)->Data[0]; 					\
				(ptr)->msg2 = (rx_message)->Data[1];					\
				(ptr)->msg3 = (rx_message)->Data[2];					\
				(ptr)->msg4 =	(rx_message)->Data[3];					\
				(ptr)->msg5 =	(rx_message)->Data[4];					\
				(ptr)->msg6 =	(rx_message)->Data[5];					\
				(ptr)->msg7 =	(rx_message)->Data[6];					\
				(ptr)->msg8 =	(rx_message)->Data[7];					\
		}	

extended_mcu_msg_t master_mcu_message;

static void CAN_hook(CanRxMsg *rx_message);
		

static void CAN_hook(CanRxMsg *rx_message)
{
    switch (rx_message->StdId)
    {

		case CAN_Master_MCU_ID:
		{
				get_master_mcu_msg(&master_mcu_message, rx_message);			
				break;
		}

    default:
    {
        break;
    }
    }
}

void CAN_mode_init(uint8_t tsjw, uint8_t tbs2, uint8_t tbs1, uint16_t brp, uint8_t mode)//6x
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

//    RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, ENABLE);
//    RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, DISABLE);
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;                              /*复用推挽 */
	GPIO_Init( GPIOA, &GPIO_InitStructure );                                        /* 初始化IO */

	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;                                /*上拉输入 */
	GPIO_Init( GPIOA, &GPIO_InitStructure );                                        /* 初始化IO */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);


    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = ENABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = ENABLE;
    CAN_InitStructure.CAN_Mode = mode;
    CAN_InitStructure.CAN_SJW = tsjw;
    CAN_InitStructure.CAN_BS1 = tbs1;
    CAN_InitStructure.CAN_BS2 = tbs2;
    CAN_InitStructure.CAN_Prescaler = brp;
    CAN_Init(CAN1, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber = 10;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x8000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
		CAN_ITConfig( CAN1, CAN_IT_TME, ENABLE );

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//返回yaw电机变量地址，通过指针方式获取原始数据
const extended_mcu_msg_t *get_Master_Mcu_Msg_Point(void)
{
    return &master_mcu_message;
}


void CAN_CMD_Master_MCU(uint8_t msg1, uint8_t msg2, uint8_t msg3, uint8_t msg4,uint8_t msg5,uint8_t msg6,uint8_t msg7,uint8_t msg8)
{
    CanTxMsg TxMessage;
    TxMessage.StdId = CAN_Super_Power_MCU_ID	;	//0x301
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = 0x08;
    TxMessage.Data[0] = msg1;
    TxMessage.Data[1] = msg2;
    TxMessage.Data[2] = msg3;
    TxMessage.Data[3] = msg4;
    TxMessage.Data[4] = msg5;
    TxMessage.Data[5] = msg6;
    TxMessage.Data[6] = msg7 ;
    TxMessage.Data[7] = msg8;

    CAN_Transmit(EXTENDED_MCU_CAN, &TxMessage);
}


void USB_LP_CAN1_RX0_IRQHandler( void )
{
    static CanRxMsg rx1_message;

    if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
    {
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
        CAN_Receive(CAN1, CAN_FIFO0, &rx1_message);
        CAN_hook(&rx1_message);
    }
}