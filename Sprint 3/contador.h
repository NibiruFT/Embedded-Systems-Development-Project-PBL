#ifndef CONTADOR_H
#define CONTADOR_H


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// BOTÃO conectado em PC0 agora (era PD0)
#define BOTAO PC0

// Tabela de segmentos do display para 0–9
static const uint8_t LUT[10] = {
	0x7E, 0x30, 0x6D, 0x79, 0x33,
	0x5B, 0x5F, 0x70, 0x7F, 0x7B
};

// Variável global do contador
static uint16_t contador = 0;

// Inicialização dos pinos
static inline void contador_init(void) {
	DDRB = 0xFF;
	DDRD = 0xFF; // Agora PORTD controla os segmentos do display
	DDRC &= ~(1 << BOTAO); // BOTÃO agora está em PORTC
	PORTC |= (1 << BOTAO); // Pull-up ativado
}

// Incrementa o contador ao pressionar botão
static inline void contador_incrementar(void) {
	if ((PINC & (1 << BOTAO)) == 0) {
		_delay_ms(50); // debounce
		contador++;
		if (contador > 9999) contador = 0;
		while ((PINC & (1 << BOTAO)) == 0); // aguarda soltar
	}
}

// Exibe o valor do contador nos 4 dígitos
static inline void contador_mostrar(void) {
	uint8_t u = contador % 10;
	uint8_t d = (contador / 10) % 10;
	uint8_t c = (contador / 100) % 10;
	uint8_t m = (contador / 1000) % 10;

	for (uint8_t i = 0; i < 25; i++) {
		PORTD = LUT[u];
		PORTB = 0b00000100;
		_delay_ms(2);

		PORTD = LUT[d];
		PORTB = 0b00001000;
		_delay_ms(2);

		PORTD = LUT[c];
		PORTB = 0b00010000;
		_delay_ms(2);

		PORTD = LUT[m];
		PORTB = 0b00100000;
		_delay_ms(2);
	}
}
#endif
