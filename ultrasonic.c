#include <avr/io.h>
#include <util/delay.h>
#include "ultrasonic.h"


volatile unsigned long time_50microsecond = 0; 
volatile unsigned long start_time = 0;
volatile unsigned long stop_time = 0;
volatile unsigned long duration = 0;


void Timer1_Init() {
    DDRB |= (1<<PB5);
    TCCR1B = (1 << WGM12) | (1 << CS10); // CTC mode, no prescaling (Prescaler = 1)
    OCR1A = 799; // OCR1A = (16MHz * 0.00001) - 1 = 799 ------50 micro second
    TIMSK1 = (1 << OCIE1A); // Enable interrupt on compare match A
}

float GetUltrasonicDistance(){
    
    PORTB &= ~(1<<TriggerPin);
    _delay_us(2);
    PORTB |= (1<<TriggerPin);
    _delay_us(10);
    PORTB &= ~(1<<TriggerPin);
    
    //waits until echo pin is high
    while (!(PINB & (1<<EchoPin))){
    }

    time_50microsecond = 0;
    start_time = time_50microsecond;

    while (PINB & (1<<EchoPin)){
    }

    stop_time = time_50microsecond;
    duration = stop_time - start_time; 
    time_50microsecond = 0;
    return (duration * 0.343 * 5 )/2;
}


ISR(TIMER1_COMPA_vect) {
    time_50microsecond++;    
}




