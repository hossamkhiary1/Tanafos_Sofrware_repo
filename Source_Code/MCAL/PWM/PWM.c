#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "std_types.h"
#include "utils.h"
#include "AVR_DIOREG.h"
#include <avr/interrupt.h>


void PWM_Init(void)
{
	TCCR0A = (1<<COM0A1) | (1<<WGM00) | (1<<WGM01) ; // setting the timer at fast pwm mode(non inverting) & compare matchn prop. with max. value 255

	TIMSK0 = (1<<TOIE0); // enabling the interrupt


}
void PWM_SetDutyCycle(unsigned char ChannelId,unsigned long int DutyCycle,unsigned long int Frequency)
{
	u32 Prescaler;
	
	/*switching on Register A pins */
	switch (ChannelId)
	{
	case PB7:
		Set_Bit(DDRB,PIN7);
		break;
	case PB5:
		Set_Bit(DDRB,PIN5);
		break;
	case PB4:
		Set_Bit(DDRB,PIN4);
		break;
	case PE3:
		Set_Bit(DDRE,PIN3);
		break;
	case PH3:
		Set_Bit(DDRH,PIN3);
		break;
	case PL3:
		Set_Bit(DDRL,PIN3);
		break;
	default:
		break;
	}

	OCR0A = ((DutyCycle*255)/100)-1 ; //adjusting the required duity cycle
	sei();

	switch(Frequency)
	{
	case Freq_31250Hz:
		TCCR0B = (1<<CS00);
		break;
	case Freq_3906Hz:
		TCCR0B = (1<<CS01);
		break;
	case Freq_488Hz:
		TCCR0B = (1<<CS00) | (1<<CS01);
		break;
	case Freq_pre122Hz:
		TCCR0B = (1<<CS02);
		break;
	case Freq_30Hz:
		TCCR0B = (1<<CS00) | (1<<CS02);
		break;
	default:
		break;

	}
	//TCCR0B = (1<<CS00); // selecting clock source ,No prescaller , starting pwm
}

ISR(TIMER0_OVF_vector)
{

}
