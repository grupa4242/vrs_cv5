#include <stddef.h>
#include "stm32l1xx.h"
#include "vrs_cv5.h"


void adc_init()
{
	ADC_InitTypeDef ADC_InitStructure;

	RCC_HSICmd (ENABLE);

	while (RCC_GetFlagStatus (RCC_FLAG_HSIRDY) == RESET);

	RCC_APB2PeriphClockCmd (RCC_APB2Periph_ADC1, ENABLE);

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

	ADC_StructInit (&ADC_InitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init (ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig (ADC1, ADC_Channel_1, 1, ADC_SampleTime_384Cycles);

	ADC_Cmd (ADC1, ENABLE);

	while (ADC_GetFlagStatus (ADC1, ADC_FLAG_ADONS) == RESET){}

	ADC_SoftwareStartConv(ADC1);
}

void gpio_init()
{
	GPIO_InitTypeDef conf;

	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);

	conf.GPIO_Pin = GPIO_Pin_1;
	conf.GPIO_Speed = GPIO_Speed_40MHz;
	conf.GPIO_Mode = GPIO_Mode_AN;
	conf.GPIO_PuPd = GPIO_PuPd_NOPULL;
	conf.GPIO_OType = GPIO_OType_PP;
	GPIO_Init (GPIOA, &conf);

	conf.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	conf.GPIO_Mode = GPIO_Mode_AF;

	GPIO_Init (GPIOA, &conf);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

}

void uart_init()
{
	USART_InitTypeDef conf;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	conf.USART_BaudRate = 9600;
	conf.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	conf.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	conf.USART_Parity = USART_Parity_No;
	conf.USART_StopBits = USART_StopBits_1;
	conf.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART1, &conf);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);

	USART_Cmd(USART1, ENABLE);
}

void int_init()
{
	NVIC_InitTypeDef conf;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	conf.NVIC_IRQChannel = ADC1_IRQn;
	conf.NVIC_IRQChannelCmd = ENABLE;
	conf.NVIC_IRQChannelPreemptionPriority = 1;
	conf.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&conf);

	conf.NVIC_IRQChannel = USART1_IRQn;
	conf.NVIC_IRQChannelPreemptionPriority = 2;

	NVIC_Init(&conf);
}
