#ifndef _POWERDOCK_EXP_H_
#define _POWERDOCK_EXP_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "ugpio/ugpio.h"
#include "onion-debug.h"


unsigned int ctrl = 19;
unsigned int pinRead1 = 15;
unsigned int pinRead2 = 17;
unsigned int chargepin = 16;


#ifdef __cplusplus
extern "C" {
#endif

//// Functions
void pulseGen();

void readPins();

int levelCheck();

int chargeCheck();

int checkBattery();


#ifdef __cplusplus
}
#endif
#endif // _POWERDOCK_EXP_H_