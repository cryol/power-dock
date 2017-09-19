#! /bin/sh

## script to interact with the Power Dock 2

# global variables
bUsage=0
bJson=0

VbattMax=4.20

Usage () {
	echo ""
	echo "Usage: power-dock"
	echo ""
	echo "FUNCTIONALITY:"
	echo "Onion Power Dock 2: enables the Battery Level Indicator LEDs and outputs the battery voltage"
	echo ""
	echo "OPTIONS:"
	echo " -j 		json output"
	echo " -h 		help: show this prompt"
	echo ""
}

# find voltage measurement from ADC
getBatteryVoltage() {
	# find the ADC measurement
	adc=$(($(i2cget -y 0 0x4d 0x00 w | sed -e 's/0x\(..\)\(..\)/0x\2\1/')/4))
	#echo $adc

	Ain=$(echo "($adc/1024)*(3.3)" | bc -l)
	#echo $Ain

	Vbatt=$(echo "$Ain*4/3" | bc -l)
	echo "$Vbatt"
}


### MAIN PROGRAM ###
# parse arguments
while [ "$1" != "" ]
do
    case "$1" in
        -h|--h|help|-help|--help)
            bUsage=1
            shift
        ;;
        -j|--j|json|-json|--json)
            bJson=1
            shift
        ;;
        *)
            echo "ERROR: Invalid Argument: $1"
            shift
            exit
        ;;
    esac
done


# print usage and exit
if [ $bUsage == 1 ]; then
    Usage
    exit
fi

## normal operation
# read the battery level
Vbatt=$(getBatteryVoltage)
VbattRounded=$(echo "scale=2; $Vbatt/1" | bc -l)
battDecimal=$(echo "scale=2; $Vbatt/$VbattMax" | bc -l)
battPercent=$(echo "$battDecimal * 100" | bc -l)
battPercent=$(echo "scale=0; $battPercent / 1" | bc -l)

# enable the battery LEDs
/usr/bin/power-dock-leds -q2

# print output
if [ $bJson == 1 ]; then
	echo "{\"battery-voltage\":$VbattRounded}"
else
	echo "Battery Voltage Level: $VbattRounded V"
	#echo "Battery Level Percent: $battPercent %"
fi
