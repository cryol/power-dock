#include <powerdock-exp.h>

//Pin State Holders

int s15;
int s17;
int s15p;
int s17p;



int _GpioInit(int gpioPin) 
{
	int 	bRequest;

	// check that gpio is free
	if ((bRequest = gpio_is_requested(gpioPin)) < 0)
	{
		return EXIT_FAILURE;
	}

	// request the pin
	if (!bRequest) {
		if ((gpio_request(gpioPin, NULL)) < 0)
		{
			return EXIT_FAILURE;
		}
	}	

	return 	EXIT_SUCCESS;
}

int _GpioClose(int gpioPin)
{
	if (gpio_free(gpioPin) < 0)
	{
		return EXIT_FAILURE;
	}

	return 	EXIT_SUCCESS;
}

int _GpioSet (int gpioPin, int value)
{
	int 	status;

	// initialize the pin
	status 	= _GpioInit(gpioPin);

	if (status == EXIT_SUCCESS) {
		// set the value
		value 	= (value == 1 ? GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW);
		status 	= gpio_direction_output(gpioPin, value);

		if (status < 0) {
			status = EXIT_FAILURE;
		}

		// close the pin
		status 	|= _GpioClose(gpioPin);
	}

	return 	status;
}

int _GpioSetInput (int gpioPin)
{
	int 	status;

	// initialize the pin
	status 	= _GpioInit(gpioPin);

	if (status == EXIT_SUCCESS) {
		status 	= gpio_direction_input(gpioPin);

		if (status < 0) {
			status = EXIT_FAILURE;
		}

		// close the pin
		status 	|= _GpioClose(gpioPin);
	}

	return 	status;
}
int _GpioGet (int gpioPin)
{
	int 	reading;

	reading = gpio_get_value(gpioPin);

	return 	reading;
}
int convertToLevel(int batlevel1, int batlevel2){
	int level;
	if(batlevel1<batlevel2){
		level = batlevel1;
		return level;
	}
	else {
		level = batlevel2;
		return level;
	}
}

int convertReading(int val1, int val2){
	int level;
	if(val1==0 && val2==0){
		level = 1;
		return level;
	}
	else if(val1==0 && val2==1){
		level = 2;
		return level;
	}
	else if(val1==1 && val2==1){
		level = 3;
		return level;
	}
	else {
		level = 1;
		return level;
	}
//Make a Simple Decision Table and spit out the value.
	
}
int readPins(){
	printf("Beginning Reading Sequence\n");
	usleep(500000);
	s15 = _GpioGet(pinRead1);
	s17 = _GpioGet(pinRead2);
	usleep(500000);
	s15p = _GpioGet(pinRead1);
	s17p = _GpioGet(pinRead2);
	printf("Finished Reading Sequence\n");
	return 0;
	//Read and save states to s15 and s17
	//Wait 500 ms 
	//Read and save states to s15p and s17p
}
int pulseGen(){
	//Set GPIO 19 to Low
	//Wait for 200 ms 
	//Set GPIO 19 to High
	//Wait 100 ms 
	//Set GPIO19 back low
	printf("Beginning Pulse Gen Sequence\n");
	int status;
	status = _GpioSet(ctrl, 0);
	usleep(200000);
	status = _GpioSet(ctrl, 1);
	usleep(100000);
	status = _GpioSet(ctrl, 0);
	printf("Finsihed PulseGen Sequence\n");
	return 0;
} 
int levelCheck(){
	int	initpin1=_GpioSetInput(pinRead1);
	int	initpin2=_GpioSetInput(pinRead2);
	int level;
	int pulse;
	int pins;
	if (initpin1==0 & initpin2==0){
		int batlevel;
		int batlevelp;	
		pulse=pusleGen();
		pins=readPins();
		batlevel=convertReading(s15,s17);
		batlevelp=convertReading(s15p,s17p);
		level=convertToLevel(batlevel,batlevelp);
		return level;
	}
	else {
	printf("Was unable to get level because could not set the two pins to input \n");
	return level;
	}
}
int chargeCheck(){
	int check;
	int	initcp=_GpioSetInput(chargepin);	
	if( initcp==0){
		check=_GpioGet(chargepin);
		return check;
	}
	else {
	printf("Unable to initilize pin 16 for input \n");
	return initcp;
	}
}
int checkBattery(){
	//Hopefully implement later to check if battery is there
	return 0;
}
