#!/bin/sh

ReadGpio () {
	val=$(gpioctl get $1 | grep LOW)

	if [ "$val" != "" ]; then
		ret="0"
	else
		ret="1"
	fi

	echo "$ret"
}

CheckBatteryLevel () {
	charge=$(ReadGpio 16)
	echo "> Charging status: $charge"

	battery1=$(ReadGpio 17)
	battery2=$(ReadGpio 15)
	echo "> Battery Level: $battery2 $battery1"
}

echo "> Enabling Battery LEDs"

#while [ 1 ]
#do
#       gpioctl dirout-low 19
#       /usr/bin/sleep 0.1
#       gpioctl dirout-high 19
#
#       /usr/bin/sleep 0.1
#done

gpioctl dirin 15 >& /dev/null
gpioctl dirin 16 >& /dev/null
gpioctl dirin 17 >& /dev/null

echo "> Pulse"
gpioctl dirout-high 19 >& /dev/null
/usr/bin/sleep 0.1
gpioctl dirout-low 19 >& /dev/null

/usr/bin/sleep 0.5
CheckBatteryLevel

/usr/bin/sleep 1
echo "> Next battery check"
CheckBatteryLevel

