/************************************************************************
*	VANESSA MARQUES							*
*	KEY: BYG35I815U6CNKJJ						*
*	Channel: https://thingspeak.com/channels/246136			*
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <regex.h>
#include "ThingSpeakLinux.h"

#define PATH_MAX 100

char * Key = "BYG35I815U6CNKJJ";
int argc = 4;
char *argv[4];
int timestampArrival;
int timestampDeparture;

char * UUID = "310064a2-5bd6-4d97-80bf-d99fa7e9b72f";

void enableBluetooth()
{
	system("rfkill unblock bluetooth");
	system("killall bluetoothd");
	system("hciconfig hci0 up hciconfig hci0 leadv 3");
	system("hcitool -i hci0 cmd 0x08 0x0008 1c 02 01 06 03 03 aa fe 14 16 aa fe 10 00 02 62 69 74 2e 6c 79 2f 32 6b 6e 5a 4e 38 49 00 00 00");
}

void ThingSpeak()
{
	argv[1] = Key;

	//Arrival
	char strT1[20];
	sprintf(strT1, "%d", timestampArrival);
	argv[2] = strT1;

	//Departure
	char strT2[20];
	sprintf(strT2, "%d", timestampDeparture);
	argv[3] = strT2;

	float FieldsArray[argc-1];
	int i;

	for(i=2; i<argc; i++)
	{
		FieldsArray[i-2]=atof(argv[i]);
	}

	printf("Timestamp arrival: %d \r\n", timestampArrival);
	printf("Timestamp departure: %d \r\n", timestampDeparture);
	printf("Sending data to ThingSpeak... \r\n");

	SendDataToThingSpeak(argc-2, &FieldsArray[0], argv[1], sizeof(argv[1]));
}

int main()
{
	enableBluetooth();

	//beacon
	system("hcitool lescan --duplicates");

	char * line = "";
	char * packet = "";
	FILE *fp;
	int status;
	char path[PATH_MAX];

	fp = popen("hcidump --raw", "r");
	if (fp == NULL) {
	    printf("fp NULL \r\n");
	}

	while (fgets(path, PATH_MAX, fp) != NULL) {

		//TODO: Filter devices (Regular expression: ^04\ 3E\ 2A\ 02\ 01\ .{26}\ 02\ 01\ .{14}\ 02\ 15)

		timestampArrival = (int)time(NULL);

		line = path;
		printf("Line: %s \r\n", line );
    
		timestampDeparture = (int)time(NULL);
		
		ThingSpeak();
	}

	pclose(fp);
}
