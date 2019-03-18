/*
 * ReactiveLamp.c
 *
 * Created: 3/2/2019 7:53:02 PM
 * Author : Stephanie Italiaie
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "timer.h"
#include "adc.c"
#include "bit.h"
#include "usart.h"

enum States {init, start, LampON, LampOFF} state;

unsigned short soundDetector = 0x0000;
unsigned char count=0;
//int mine;

void Tick() {
	//soundDetector = ADC;
	
	switch(state) {
		case init:
			state = start;
			while (!USART_IsSendReady(0));
			USART_Send(0, 0);
			while(!USART_HasTransmitted(0));
			break;
		case start:
			count++;
			if(count == 20) {
				state = LampON;
			}
			else {
				state = start;
			}
			break;
		case LampON:
			count++;
			if(count == 2400) {
				state = LampOFF;
			}
			else {
				state = LampON;
			}
			break;
		case LampOFF:
			count++;
			if(count == 2450) {
				count = 0;
				state = start;
			}
			else
			{
				state = LampOFF;
			}
			break;
		default:
			state = init;
			break;
	}
	
	switch(state) {
		case init:
			break;
		case start:
			break;
		case LampON:
			soundDetector = ADC;
			break;
		case LampOFF:
			soundDetector = 0x0000;
			break;
		default:
			break;
		
	}
}

int main() {
	DDRA = 0x00; PORTA = 0xFF; // input on A
	DDRB = 0xFF; PORTB = 0x00; //output is on B

	ADC_init();
	TimerSet(100);
	TimerOn();
	initUSART(0);
	USART_Flush(0);
	
	state = init;
	
	while(1) {
		Tick();
		while (!USART_IsSendReady(0));
		USART_Send((soundDetector & 0x00FF), 0);
		while(!USART_HasTransmitted(0));
		/*
		unsigned char send_data = soundDetector;
		while (!USART_IsSendReady(0));
		for (int i = 0 ; i < 8; i++) {
			send_data = (send_data >> 1) & 0x7F;
		}
		USART_Send(send_data, 0);
		while(!USART_HasTransmitted(0));
		*/
		while (!TimerFlag) {} // Wait for timer period
		TimerFlag = 0; // Lower flag raised by timer
	}
	
	/*while(1) {
		if(USART_HasReceived(0)) {
			PORTB = USART_Receive(0);
		}
	}
	
	int mine = 1;
	while (1) {
		if(mine) {
			while (!USART_IsSendReady(0));
			USART_Send(1, 0);
			while(!USART_HasTransmitted(0));
			mine = 0;
		}
		else {
			while (!USART_IsSendReady(0));
			USART_Send(0, 0);
			while(!USART_HasTransmitted(0));
			mine = 1;
		}
		tempB = blinkingLed;
		while (!TimerFlag) {} // Wait for timer period
		TimerFlag = 0; // Lower flag raised by timer
	}*/
}