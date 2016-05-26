#include <power-dock.h>

void usage() 
{
	printf("\n");
	printf("Usage: powerdock-exp -i\n");
	printf("\n");
	printf("FUNCTIONALITY:\n");
	printf("\tChecks the battery level and if its charging.\n");
	printf("\n\n");
	printf("Usage: powerdock-exp [-qvi] command\n");
	printf("\n");
	printf("Commands:\n");
	printf("'BatteryLevel' checks the battery level, returns number from 1-4. 4 being full charged\n");
	printf("'ChargeCheck' checks if the battery is charging, return 0 if it is and 1 if its not charging\n");
	printf("OPTIONS:\n");
	printf(" -q 		quiet: no output\n");
	printf(" -v 		verbose: lots of output\n");
	printf(" -h 		help: show this prompt\n");
	printf("\n");
}

int powerCommand(char *command){
	// int level = 0;
	// int charge = 0;
	// int status;
	// //perform the specified command
	// printf("command = '%s'\n", command);
	// //Check if you have battery connected
	// status = checkBattery();
	// //If status is 0 then proceed with the other comamnds
	
	// if(status==0){
	// 	printf("Battery Present\n");
	// 	if (strcmp(command,"BatteryLevel")==0){
	// 		//Check power level
	// 		printf("Checking the battery level\n");
	// 		level=levelCheck();
	// 		printf("The battery level is %i \n",level);
	// 		return level;
	// 	}
	// 	else if(strcmp(command,"ChargeCheck")==0){
	// 		//Check charging level
	// 		printf("Checking if charging\n");
	// 		charge=chargeCheck();
	// 		printf("The charge state is %i \n",charge);
	// 		return charge;
	// 	}
	// 	else {
	// 	usage();
	// 	printf("Invalid Commands /n");
	// 	status=1;
	// 	return status;
	// 	}
	// }
	// else{
	// 	printf("Check if your batttery dock is connected properly"); 
	// 	return status;
	// }
	return 0;
}

int main(int argc, char** argv)
{
//Two possible inputs:
//Battery Level
//Charging Status

//options
//-v 
//-h
//-q
	int 	ch;
	const char *progname;
	char 	*command;
	int 	status;

	int 	verbose;
	int 	quiet;
	int 	level0, level1;
		
	// save the program name
	progname 	= argv[0];

	while ((ch = getopt(argc, argv, "vqh:")) != -1) {
		switch (ch) {
			case 'v':
				// verbose output
				verbose++;
				break;
			case 'q':
				// quiet output
				verbose = ONION_VERBOSITY_NONE;
				break;
			case 'h':
				// display help menu
				usage();
				break;
			default:
				usage();
				return 0;
		}
	}
// ensure correct number of arguments
	/**
	 *if ( argc != 2) {
	 *	usage(progname);
	 *	printf("ERROR: invalid amount of arguments!\n");
	 *	return 0;
	 *}
	 */


	// LAZAR: for factory testing purposes
	printf("> Enabling Battery IC\n");
	status  = enableBatteryLeds();

	printf("> Reading Battery Level Pins\n");
	status 	|= readLevelPins(&level0, &level1);
	printf("   Level0: %d (GPIO%d)\n", level0, POWERDOCK_BATTERY_LEVEL0_GPIO);
	printf("   Level1: %d (GPIO%d)\n", level1, POWERDOCK_BATTERY_LEVEL1_GPIO);

	return 0;
	//LAZAR: done

	onionSetVerbosity(verbose);
	argc 	-= optind;
	argv	+= optind;

	//// parse the command arguments
	while ( argc > 0 ) {
		// first arg - command
		strcpy(command, argv[0]);

		// perform the specified command
		status 	= powerCommand(command);
		if (status != EXIT_SUCCESS) {
			printf("ERROR: command '%s' failed!\n", command);
		}
		// decrement the number of arguments left
		argc	-= 2;
		argv	+= 2;

		printf("> arguments remaining: %d\n", argc);
	}

	return 0;
}
	