/*
 * ADC_ATMEGA16.c
 *
 * Created: 21/09/2020 04:58:30
 * Author : DELL
 */ 

#include <avr/io.h>
#ifndef F_CPU
	#define F_CPU 8000000UL
#endif





void ADC_Init()
{
	
	ADCSRA = 0x87;							// Enable ADC, fr/128  
	ADMUX = 0x40;							// Vref: Avcc, ADC channel: 0 
	
}

int ADC_Read(unsigned char channel)
{
	if(channel == 0)						// setting port A channels as input based on chosen adc channel
		DDRA = DDRA&(0b11111110);
	else if(channel == 1)
		DDRA = DDRA&(0b10111101);
	else if(channel == 2)
		DDRA = DDRA&(0b11011011);
	else if(channel == 3)
		DDRA = DDRA&(0b11110111);
	else if(channel == 4)
		DDRA = DDRA&(0b11101111);
	else if(channel == 5)
		DDRA = DDRA&(0b11011111);
	else if(channel == 6)
		DDRA = DDRA&(0b10111111);
	else if(channel == 7)
		DDRA = DDRA&(0b01111111);
	
	int Ain=0,AinLow=0;
	
	ADMUX=ADMUX|(channel & 0x0f);			// Set input channel to read

	ADCSRA |= (1<<ADSC);					// Start conversion
	while((ADCSRA&(1<<ADIF))==0);			// Monitor end of conversion interrupt
	
	_delay_us(10);
	AinLow = (int)ADCL;						// Read lower byte
	Ain = ((int)ADCH)*256;					// Read higher 2 bits and
	
	Ain = Ain+AinLow;
	return(Ain);							// Return digital value
	
}

