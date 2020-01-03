/*
 */

#include <stdio.h>
#include <string.h>
#include "uartIO.h"



int main(int argc,char* argv[])
{


unsigned char cmd[3], command[64],returnData[48000];

int status,k;
unsigned char terminator;


// open and configure the serial port
	initializeBoard();

if (argc==2){

	strcpy((char*)command,argv[1]);  // command to send to a GPIB device
	terminator=13;
//(unsigned short)strtol(argv[2],NULL,16);
// CR = asci 13
//	chan=(unsigned short)strtol(argv[3],NULL,16);
//	gpib=(unsigned short)strtol(argv[4],NULL,16);
//	printf("RS485 to GPIB Bridge: RS485  Address %02x = %d\n",chan,chan);
//	printf("Address of GPIB device attached to bridge %02x = %d\n",gpib,gpib);

	status = strlen(command);
	command[status] = terminator;
	command[status+1]=0;

	printf("UART Tx:> %s\n\n",command);
//	status=sendGPIBData(command,gpib,chan);
	write_UART(command,status+1,returnData,&k);
	printf("UART Rx:> %s\n\n",returnData);
	printf("%d characters returned\n",k);
}else {
printf("usage ./gpibBridge \"texttosend\" <terminator> <HEX RS485Address of bridge> <HEX GPIB address on bus> \n");

}

// exit normally
    return 0;
}

