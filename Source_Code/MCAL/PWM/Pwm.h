#ifndef PWM_H
#define PWM_H
typedef struct
{
	unsigned char TimerId;
	unsigned char TimerFrequence;
}TimerConfigType;

void PWM_Init(void);
void PWM_SetDutyCycle(unsigned char ChannelId,unsigned long int DutyCycle,unsigned long int Freequency);


#define TCCR0A  *((u8*)0x44)
#define WGM00  0
#define WGM01  1
#define COM0B0 4
#define COM0B1 5
#define COM0A0 6
#define COM0A1 7
#define TCCR0B  *((u8*)0x45)
#define CS00  0
#define CS01  1
#define CS02  2
#define WGM02 3
#define FOC0B 6
#define FOC0A 7
#define TCNT0   *((u8*)0x46)
#define OCR0A   *((u8*)0x47)
#define OCR0B   *((u8*)0x48)
#define TIMSK0	*((u8*)0x6E)
#define TOIE0  0
#define TIFR0	*((u8*)0x35)
#define TON0 0
#define OCF0A 1
#define OCF0B 2

#define PB7 0
#define PB5 1
#define PB4 2
#define PE3 3
#define PH3 4
#define PL3 5

#define Freq_31250Hz    0      //31250
#define Freq_3906Hz  1      //3906.25
#define Freq_488Hz    2      //488.3
#define Freq_pre122Hz   3      //122
#define Freq_30Hz       4      // 30



#endif
