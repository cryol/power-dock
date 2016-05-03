#include <powerdock-exp.h>

void usage(const char* progName) 
{
	onionPrint(ONION_SEVERITY_FATAL, "\n");
	onionPrint(ONION_SEVERITY_FATAL, "Usage: powerdock-exp -i\n");
	onionPrint(ONION_SEVERITY_FATAL, "\n");
	onionPrint(ONION_SEVERITY_FATAL, "FUNCTIONALITY:\n");
	onionPrint(ONION_SEVERITY_FATAL, "\tChecks the battery level and if its charging.\n");
	onionPrint(ONION_SEVERITY_FATAL, "\n\n");
	onionPrint(ONION_SEVERITY_FATAL, "Usage: powerdock-exp [-qvi] command\n");
	onionPrint(ONION_SEVERITY_FATAL, "\n");
	onionPrint(ONION_SEVERITY_FATAL, "Commands:\n");
	onionPrint(ONION_SEVERITY_FATAL, "'BatteryLevel' checks the battery level, returns number from 1-4. 4 being full charged\n");
	onionPrint(ONION_SEVERITY_FATAL, "'ChargeCheck' checks if the battery is charging, return 0 if it is and 1 if its not charging\n");
	onionPrint(ONION_SEVERITY_FATAL, "OPTIONS:\n");
	onionPrint(ONION_SEVERITY_FATAL, " -q 		quiet: no output\n");
	onionPrint(ONION_SEVERITY_FATAL, " -v 		verbose: lots of output\n");
	onionPrint(ONION_SEVERITY_FATAL, " -h 		help: show this prompt\n");
	onionPrint(ONION_SEVERITY_FATAL, "\n");
}
int powerCommand(char *command){
	int level = 0;
	int charge = 0;
	int status;
	//perform the specified command
	onionPrint(ONION_SEVERITY_DEBUG_EXTRA, "command = '%s', param = '%s'\n", command, param);
	//Check if you have battery connected
	status = checkBattery();
	//If status is 0 then proceed with the other comamnds
	
	if(status==0){
		printf("Battery Present\n");
		if (strcmp(command,"BatterLevel")==0){
			//Check power level
			printf("Checking the battery level\n");
			level=levelCheck();
			printf("The battery level is %i \n",level);
			return level;
		}
		else if(strcmp(command,"ChargeCheck")==0){
			//Check charging level
			printf("Checking if charging\n");
			charge=chargeCheck();
			printf("The charge state is %i \n",charge);
			return charge;
		}
		else {
		usage(progname);
		printf("Invalid Commands /n");
		status=1;
		return status;
		}
	}
	else{
	printf("Check if your batttery dock is connected properly"); 
	return status;
	}
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

	const char *progname;
	char 	*command
	int status;
	progname = argsv[0];
	
	int verbose;
	int status;
	int quiet;
		
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
			usage(progname);
			break;
		default:
			usage(progname);
			return 0;
		}
	}
// ensure correct number of arguments
	/**
	 *if ( argc != 2) {
	 *	usage(progname);
	 *	onionPrint(ONION_SEVERITY_FATAL, "ERROR: invalid amount of arguments!\n");
	 *	return 0;
	 *}
	 */

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
			onionPrint(ONION_SEVERITY_FATAL, "ERROR: command '%s' failed!\n", command);
		}
		// decrement the number of arguments left
		argc	-= 2;
		argv	+= 2;

		onionPrint(ONION_SEVERITY_DEBUG, "> arguments remaining: %d\n", argc);
	}

	}
	return 0;
}