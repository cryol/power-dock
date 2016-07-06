#include <power-dock.h>

void usage(const char* progname) 
{
	printf("\n");
	printf("Usage: %s [-qvi]\n", progname);
	printf("\n");
	printf("FUNCTIONALITY:\n");
	printf("\tEnables the Battery Level Indicator LEDs on the Onion Power Dock.\n");
	printf("\n\n");
	printf("OPTIONS:\n");
	printf(" -q 		quiet: no output\n");
	printf(" -v 		verbose: lots of output\n");
	printf(" -h 		help: show this prompt\n");
	printf("\n");
}

int main(int argc, char** argv)
{
	int 	ch;
	const char *progname;
	char 	*command;
	int 	status;

	int 	verbose;
	int 	quiet;
	int 	level0, level1;
		
	// save the program name
	progname 	= argv[0];

	while ((ch = getopt(argc, argv, "vqht")) != -1) {
		switch (ch) {
			case 'v':
				// verbose output
				verbose++;
				break;
			case 'q':
				// quiet output
				verbose = ONION_VERBOSITY_NONE;
				break;
			case 't':
				// enable reading the battery level
				level0 	= 0;
				level1 	= 0;
				break;
			default:
				// display usage printout
				usage(progname);
				return 0;
		}
	}
	
	onionSetVerbosity(verbose);
	argc 	-= optind;
	argv	+= optind;


	// enable the battery level indicator LEDs
	onionPrint(ONION_SEVERITY_INFO, "> Enabling Battery Indicator LEDs\n");
	status  = enableBatteryLevelIndicator();


	// read the battery level
	if (level0 == 0 && level1 == 0) {
		onionPrint(ONION_SEVERITY_INFO, "> Reading Battery Level Pins\n");
		status 	|= readBatteryLevel(&level0, &level1);
		onionPrint(ONION_SEVERITY_INFO, "   Level0: %d (GPIO%d)\n", level0, POWERDOCK_BATTERY_LEVEL0_GPIO);
		onionPrint(ONION_SEVERITY_INFO, "   Level1: %d (GPIO%d)\n", level1, POWERDOCK_BATTERY_LEVEL1_GPIO);
	}

	return 0;
}
	