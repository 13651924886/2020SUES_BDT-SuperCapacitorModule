#ifndef _OLED_H
#define _OLED_H
#include "sys.h"


#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	


#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý



void OLED_Init(void);
void OLED_Task(void);


void OLED_WR_Byte(unsigned dat,unsigned cmd); 
void Write_OLED_Command(unsigned char IIC_Command);
void Write_OLED_Data(unsigned char IIC_Data);
void fill_picture(unsigned char fill_Data);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_On(void);
u32 oled_pow(uint8_t m,uint8_t n);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLED_ShowNum(uint8_t x,uint8_t y,u32 num,uint8_t len,uint8_t size2);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t chr[],uint8_t Char_Size);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

#endif
