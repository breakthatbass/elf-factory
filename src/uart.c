/**
 * uart.c - a simple program to print 'A' to the console about once every second
 *
 * an FTDI cable is needed to connect the UART pins to the computer.
 * from there run the command `screen <location-of-device> <baud rate>`
 * and that will open the console.
 *
 * Taylor Gamache, 2021-11-10
 *
 * This code comes from here:
 * https://stackoverflow.com/questions/60005647/msp430fr5994-uart-communication-with-pc-in-python
 *
 * */
#include<msp430.h>

void UART_init(void);

void main(void) {
  WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;

  UART_init();

  while (1) {
		UCA1TXBUF = 'A';
		__delay_cycles(500000L);
	}
}

void UART_init(void){
    P2SEL1 |= BIT5 + BIT6;              //Activate Pin for UART use
    P2SEL0 &= ~BIT5 + ~BIT6;            //Activate Pin for UART use

    UCA1CTLW0 |= UCSSEL_2;              //Select clock SMCLK

    UCA1BRW = 0x6;                      //Set Baud rate 9600 : UCA1BRW = INT(F_CPU/BAUD_soll) =         INT(1MHz/9600) = 104 with oversampling: 6
    UCA1MCTLW |= UCBRS5 + UCOS16 + UCBRF3;     //Modulation according to datasheet table: UCBRS = 0x20 = b100000 and UCOS16 = 1 and UCBRF = 8 = 0x8 = b1000

    UCA1CTLW0 &= ~UCSWRST;  //Reset UART module
 }
