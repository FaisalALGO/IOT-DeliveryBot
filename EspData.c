#include <avr/io.h>
#include "EspData.h"

/*
Uart Config to process data recieved from ESP 
*/


volatile int state = 0;
volatile unsigned char receivedbyte = 0;


void initUART(unsigned int baud_rate) {
    unsigned int ubrr = 16000000 / 16 / baud_rate - 1;
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Enable transmit and receive and receive interrupt
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); 
}

void CheckValidByte(){

    if (receivedbyte >= '0' && receivedbyte <= '9'){
        state = receivedbyte - '0' ;//convert to integer
    }

}


ISR(USART_RX_vect){

    receivedbyte = UDR0;
    CheckValidByte();
}

