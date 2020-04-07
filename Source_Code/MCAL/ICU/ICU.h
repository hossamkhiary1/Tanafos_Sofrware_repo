#ifndef ICU_H
#define ICU_H
typedef enum {FALLING_EDFGE, RISING_EDGE}ICU_CapturedEventType;
typedef enum {TIMER_NOT_STARTED, EVENT_NOT_DETECTED, EVENT_DETECTED} ICU_EventType;
typedef void (*ICU_CallbackType)(void);
typedef struct 
{
	unsigned char TimerID;
	unsigned long int MaximamCaptureTime;
	ICU_CallbackType InputCaptureCbkNotif;
}ICU_ConfigParamType;
void ICU_Init(void);
void ICU_StartTimer(unsigned char TimerChannel, ICU_CapturedEventType CapturedEvent);
ICU_EventType ICU_GetCapturedTime(unsigned char TimerChannel, unsigned long int* TimePtr);
#endif