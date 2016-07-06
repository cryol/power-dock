#include <power-dock.h>


///////////////////////////////////////
// Battery IC Functions
///////////////////////////////////////

int enableBatteryLevelIndicator(){
	int status;

	//Set GPIO 19 to Low
	//Wait for 200 ms 
	//Set GPIO 19 to High
	//Wait 100 ms 
	//Set GPIO19 back low
	
	status = GpioSet(POWERDOCK_CTRL_GPIO, 0);
	usleep(200 * 1000);
	status |= GpioSet(POWERDOCK_CTRL_GPIO, 1);
	usleep(100 * 1000);
	status |= GpioSet(POWERDOCK_CTRL_GPIO, 0);
	
	return status;
} 

int readBatteryLevel(int *level0, int *level1) {
	int status;

	status 	= GpioGet(POWERDOCK_BATTERY_LEVEL0_GPIO, level0);
	status 	|= GpioGet(POWERDOCK_BATTERY_LEVEL1_GPIO, level1);

	return status;
}
///////////////////////////////////////



