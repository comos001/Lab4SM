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



enum ID_States {Start, Init, RES, INC, DEC, INCWAIT, DECWAIT } State;

        /*initial conditions*/


void ID_switch(){
	switch (State) {
		case Start:
			State = Init;
		break;
		case Init:
			if (PINA == 0x01){
				State = INC;
			} 	
			else if (PINA == 0x02){
				State = DEC;
			}
			else if (PINA == 0x03){
				State = RES;
			}
			else {
				State = Init;
			}
		break;		
		case INC:
			if (PORTC < 9){
			PORTC = PORTC + 1;
			}
			State = INCWAIT;
		break;
		case INCWAIT:
			if (PINA == 0x01){
				State = INCWAIT;
			}	
			else if (PINA == 0x03){
                                State = RES;
                        }

			else{
				State = Start;
			}
		break;
		case DEC:
			if (PORTC > 0){
			PORTC = PORTC - 1;
			}				
			State = DECWAIT;
		break;
		case DECWAIT:
			if (PINA == 0x02){
                                State = DECWAIT;
                     	}
			else if (PINA == 0x03){
				State = RES;
			}
                        else {
                                State = Start;
                        }
		break;
		case RES:
			PORTC = 0x00;
		break;
		default:
 			State = Start;
			break;
		}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; 
	DDRC = 0xFF; PORTC = 0x00;
	/*initial conditions*/
	State = Start;
	PORTC = 0x07;
    /* Insert your solution below */
    while (1) {
	ID_switch();
    }
	
return 1;
}
