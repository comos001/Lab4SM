/*	Author: comos001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


unsigned char temp = 0x00;
unsigned char out = 0x00; //output

enum LED_States {Start, Init, BP1, BP2, BR1} State;

void LED_switch(){
	switch (State) {
		case Start:
			State = Init;
		break;
		case Init:
			if (temp == 0x00){
				State = Init;
				out = 0x01;
			} 	
			else {
				State = BP1;
				out = 0x02;
			}
		break;
		case BP1:
			if (temp == 0x01){
				State = BP1;
                                out = 0x02;
			}	
			else {
				State = BR1;
				out = 0x02;
			}
		break;
		case BR1:
			if (temp == 0x00){
				State = BR1;
				PORTB = 0x02;
			}
			else {
				State = BP2;
				PORTB = 0x01;
			}
		break;
		case BP2:
			if (temp == 0x00){
                                State = Init;
                                PORTB = 0x01;
                        }
                        else {
                                State = BP2;
                                PORTB = 0x01;
                        }
		 break;

		default:
 			State = Start;
			break;
		}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	unsigned char temp = 0x00;
	unsigned char out = 0x00;
	out = 0x00;
	/*initial conditions*/
	State = Start;
	PORTB = out;
    /* Insert your solution below */
    while (1) {
	LED_switch();
    }
	
	return 1;
}
