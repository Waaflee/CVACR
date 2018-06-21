/* I2C Echo Example */

#define	F_CPU 16000000				// Necesario para calcular los bps (baud rate) de la UART 
#define BAUD 9600					// Baud rate, 9600 bps 

#include <avr/io.h>					// Donde están declarados los registros de E/S y sus bits
#include "I2CSlave.h"

void mi_UART_Init( unsigned int);
int mi_putc(char);
int mi_getchar(void);

#define getc() mi_getc()
#define putc(x) mi_putc(x)
#define I2C_ADDR 0x8

volatile uint8_t data;


//---------------------------------------------------------------------------------
//		Inicializa UART.

void mi_UART_Init( unsigned int ubrr)
{
	UBRR0 = F_CPU/16/ubrr-1;				// Configura baudrate. Ver en sección UART de datasheet
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);			// Habilita bits TXEN0 y RXEN0
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);		// USBS0=1 2 bits stop, UCSZxx=3 8 bits
}

//---------------------------------------------------------------------------------
//		Pone caracter en UART. 

int mi_putc(char c)
{
	while(!(UCSR0A & (1<<UDRE0)) ); // Espera mientras el bit UDRE0=0 (buffer de transmisión ocupado)
	UDR0 = c;						// Cuando se desocupa, UDR0 puede recibir el nuevo dato c a trasmitir
	return 0;
}

//---------------------------------------------------------------------------------
//		Recibe caracter en UART.

int mi_getc()
{
	while ( !(UCSR0A & (1<<RXC0)) );//Espera mientras el bit RXC0=0 (recepción incompleta)
	return UDR0;					//Cuando se completa, se lee UDR0
}


void I2C_received(uint8_t received_data)
{
  data = received_data;
  putc(data);
}

void I2C_requested()
{
  I2C_transmitByte(data);
}

void setup()
{
  // set received/requested callbacks
  I2C_setCallbacks(I2C_received, I2C_requested);

  // init I2C
  I2C_init(I2C_ADDR);
}

int main()
{
  setup();				// Variable para recibir y transmitir datos por la uart
  mi_UART_Init(BAUD);		// Inicializa UART
  putc('o');putc('k');	// Señal de vida del programa.

  // Main program loop
  while(1);
}
