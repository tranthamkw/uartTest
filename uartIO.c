
#include "uartIO.h"

// ADC variables
#define BASE 100
#define SPI_CHAN 0
#define RS485CONTROL 0
#define BAUD 9600
#define LISTEN 0
#define WRITE 1

// wiring pi GPIO pin assigments to stepper motor drivers

void delayMicrosecondsHard(unsigned int howLong);
int initialize_uart(void);
int fd;

void advance_spinner(){
	static int pos=0;
	char spinner[4] = {'/','-','\\','|'};
	printf("%c",spinner[pos]);
	fflush(stdout);
	printf("\b");
	pos=(pos+1)%4;
}

// these are for RS485 communications

long int calcDelay(int size){
	long int del;
	// calculate the delay needed. for RS485 communications. depends on the number of chars we are transmitting
	del=size*10*1000000;
	 /* (10=8bits+2parity)  bits per character  *  1000000 microseconds per second
		  8 bits per char plus start and stop bits. 
		Tested watching an O-scope with 4 to 10 input chars. */
	del=del/BAUD; // * 1 second per baud 
return del;
}

void delay_uS(int x){

delayMicrosecondsHard(x);

}

int initializeBoard(){

	if (wiringPiSetup () == -1) 
	  {
	    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
	    return 1 ;
	  }
	initialize_uart();
return 0;
}

int initialize_uart(void){
  if ((fd = serialOpen ("/dev/ttyAMA0", BAUD)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }
return 0;
}//end initialize


int closeBoard(){
	serialClose(fd);
return 0;
}



void write_UART(unsigned char* cmd, unsigned int numchar, unsigned char* pszEcho, unsigned int* sizeEcho){

	unsigned int i,j;
	unsigned int loop;
//	delayMicrosecondsHard(10);// minor wait to allow signals to settle

	for (j=0;j<numchar;j++){
		serialPutchar(fd,cmd[j]);
	}
	// cannot read in from UART until done transmitting, so wait . . . 
//	delayMicrosecondsHard(calcDelay(numchar+2));
//	printf("wrote %d chars to uart \n\n",numchar);

//	digitalWrite(RS485CONTROL,LISTEN);// now set control to READ (i.e. LISTEN)
	loop=0;
	i=0;
	do {
		while (serialDataAvail (fd)){
			pszEcho[i]=serialGetchar(fd);
			i++;
			loop=0;
			if ((i%100)==0)	advance_spinner();

		}
		delay(5);
		loop++;
	} while(loop<50);
//	printf("\nNum characters returned %d\n",i);
	*sizeEcho=i;
}

