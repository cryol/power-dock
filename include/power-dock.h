#ifndef _POWERDOCK_EXP_H_
#define _POWERDOCK_EXP_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <ugpio/ugpio.h>
#include <onion-debug.h>


#define POWERDOCK_CTRL_GPIO 			19
#define POWERDOCK_BATTERY_LEVEL0_GPIO 	16
#define POWERDOCK_BATTERY_LEVEL1_GPIO 	18



#ifdef __cplusplus
extern "C" {
#endif

//// Functions
int 		enableBatteryLeds			();
int 		readLevelPins				(int *level0, int *level1);

int readPins			();

int levelCheck			();

int chargeCheck			();

int checkBattery		();


#ifdef __cplusplus
}
#endif
#endif // _POWERDOCK_EXP_H_