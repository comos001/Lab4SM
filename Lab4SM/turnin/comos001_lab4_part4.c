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



enum Lock_States {Init, Press1, Press2, Unlock} State;

        /*initial conditions*/


void safelock(){
	switch (State) {
		case Init:
			if (PINA == 0x04){
				State = Press1;
			} 	
			else {
				State = Init;
			}
		break;		
		case Press1:
			if (PINA == 0x04){
				State = Press1;
			}
			else if (PINA == 0x00){
				State = Press2;
			}
			else {
				State = Init;
			}
		break;
		case Press2:
			if (PINA == 0x00){
				State = Press2;
			}	
			else if (PINA == 0x02){
                                State = Unlock;
                        }
			else{
				State = Init;
			}
		break;
		case Unlock:
			if (PINA == 0x80){
				State = Init;
				PORTB = 0x00;
			}		
			else if (PORTB == 0x00) {		
				PORTB = 0x01;
			}
			else {
				PORTB = 0x00;
			} 
			break;
		default:
 			State = Init;
			break;
		}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; 
	DDRB= 0xFF; PORTB = 0x00;
	/*initial conditions*/
	State = Init;
	PORTB = 0x00;;
    /* Insert your solution below */
    while (1) {
	safelock();

    }
	
return 1;
}
