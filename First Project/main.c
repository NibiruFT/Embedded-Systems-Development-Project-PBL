/*
 * Primeiro Programa.c
 *
 * Created: 6/24/2025 11:15:54 AM
 * Author : Window 10
 */ 

#define F_CPU 16000000UL 
#include <avr/io.h> 
#include <util/delay.h> 

int main(void) 
{ 
	/* Replace with your application code */ 
	DDRB = 0b00100000; //Habilita o pino PB5 como sa�da
	while (1) 
	{ 
		PORTB = 0b00100000; //Pino PB5 em n�vel alto 
		_delay_ms(500); 
		PORTB = 0b00000000; //Pino PB5 em n�vel baixo 
		_delay_ms(500); 
	} 
}

