/*

KENBOARD electrical layer for wiring Pi interface to RaspPi GPIO. See schematics

MODBUS RTU LAYER::
	uses Modbus 16 communcation protocal .  Modbus specifies how data is organized
	and can be transmitted over different types of electrical standards (e.g. rs485, rs232,...)
	Useful resource:
	http://www.lammertbies.nl/comm/info/modbus.html
	8 bits
	No parity
	1 stop bit(I think)
	9600 baud
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int initializeBoard();
//wiring pi setup , initialyze global variables
int closeBoard();

void delay_uS(int x);

void write_UART(unsigned char* cmd, unsigned int numchar, unsigned char* pszEcho, unsigned int* sizeEcho);
// uses RaspiUART and one GPIO pin to control serial IO through RS485
