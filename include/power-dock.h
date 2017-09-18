#ifndef _POWERDOCK_EXP_H_
#define _POWERDOCK_EXP_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <gpio.h>
#include <onion-debug.h>


#define POWERDOCK_CTRL_GPIO 			19
#define POWERDOCK2_CTRL_GPIO 			16

#define POWERDOCK_BATTERY_LEVEL0_GPIO 	16
#define POWERDOCK_BATTERY_LEVEL1_GPIO 	18

#define POWERDOCK_MAX_BATTERY_LEVEL		4



#ifdef __cplusplus
extern "C" {
#endif

//// Functions
int 		enableBatteryLevelIndicator			(int dockVersion);
int 		readBatteryLevel					(int *level0, int *level1);
int 		convertBatteryInputsToLevel			(int level0, int level1);



#ifdef __cplusplus
}
#endif
#endif // _POWERDOCK_EXP_H_
