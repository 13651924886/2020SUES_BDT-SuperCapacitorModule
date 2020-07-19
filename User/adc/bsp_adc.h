#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

#define    NOFCHANEL										 3

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADCx                          ADC1
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA 
#define    ADC_PORT                      GPIOA

// PC1-ͨ��11 ����IO
#define    ADC_PIN                       GPIO_Pin_1
#define    ADC_CHANNEL                   ADC_Channel_1

// ADC1������ͨ������DMA1_Channel1
#define    ADC_DMA_CHANNEL               DMA1_Channel1


//ADC1_IN5  PA5	���ڼ�ⳬ�����ݵ�ѹ

#define    ADC_VoltageMeasure_PORT                      GPIOA
#define    ADC_VoltageMeasure_PIN                       GPIO_Pin_5
#define    ADC_VoltageMeasure_CHANNEL                   ADC_Channel_5


//ADC1_IN7  PA7 ������ѹģ��������
#define    ADC_BoostVoltageMeasure_PORT                 GPIOA
#define    ADC_BoostVoltageMeasure_PIN                  GPIO_Pin_7
#define    ADC_BoostVoltageMeasure_CHANNEL              ADC_Channel_7

void ADCx_Init(void);


#endif /* __ADC_H */

