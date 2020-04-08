#ifndef USD_H
#define USD_H
typedef enum {DISTANCE_VALID, DISTANCE_NOT_VALID}USD_DistanceResultType;
void USD_Init(void);
void USD_StartMeasurement(void);
void USD_StopMeasurement(void);
USD_DistanceResultType USD_GetLastDistance(void);
void USD_Main(void);
void USD_EchoDetectedNotifCbk(void);
#endif