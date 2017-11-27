#!/bin/bash
# iBeacon Scan by Radius Networks
# Modified by Vanessa Marques

initialize_gpio()
{
	echo -n "49"  > /sys/class/gpio/export
	echo -n "in"  > /sys/class/gpio/gpio49/direction
	echo -n "256" > /sys/class/gpio/export
	echo -n "out" > /sys/class/gpio/gpio256/direction
	echo -n "0"   > /sys/class/gpio/gpio256/value
	echo -n "224" > /sys/class/gpio/export
	echo -n "out" > /sys/class/gpio/gpio224/direction
}

turn_on_light()
{
	count=0
	echo "Light - Turn ON!"

	initialize_gpio
	
	echo -n "1" > /sys/class/gpio/gpio224/value
	sleep 1
}

turn_off_light()
{
	count=$[count + 1]
	echo "Count: $[count]"
	
	if [[ $count -ge 5 ]];
	then
		echo "Light - Turn OFF!"	
		
		initialize_gpio
		
		echo -n "0" > /sys/class/gpio/gpio224/value
		sleep 1
		
		count=0
	fi
}

# Check if the first argument is "parse"
if [[ $1 == "parse" ]];
then
	
	# Set parameters
	packet=""
	capturing=""
	count=0
	
	while read line
	do

		# Check if capturing is different from empty
		if [ ! -z "$capturing" ];
		then
			if [[ $line =~ ^[0-9a-fA-F]{2}\ [0-9a-fA-F] ]];
			then
				packet="$packet $line"
				echo "Packet: ${packet}"
				turn_on_light
			else
				turn_off_light
				capturing=""
				packet=""
			fi
		fi
				
		# Check if capturing is empty
		if [ ! "$capturing" ]; then
		  if [[ $line =~ ^\> ]]; then
			packet=`echo $line | sed 's/^>.\(.*$\)/\1/'`
			capturing=1
		  fi
		fi
			
	sleep 1

	done
else
	echo "Scanning..."
	
	sudo hcitool lescan --duplicates 1>/dev/null &

	if [ "$(pidof hcitool)" ]; 
	then
		sudo hcidump --raw | ./$0 parse $1
	fi
fi
