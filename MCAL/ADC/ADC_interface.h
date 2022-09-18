#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define CHANNEL0   0
#define CHANNEL1   1
#define CHANNEL2   2
#define CHANNEL3   3
#define CHANNEL4   4
#define CHANNEL5   5
#define CHANNEL6   6
#define CHANNEL7   7

void ADC_voidInit(void);

u8 ADC_voidStartConversionSynchronous(u8 copy_u8ChannelNumber);
u16 ADC_voidStartConversionAsynchronous(u8 copy_u8ChannelNumber,void(*Copy_pvCallBackFunction)(void));



#endif
