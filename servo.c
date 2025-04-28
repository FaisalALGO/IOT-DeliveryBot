#include <avr/io.h>

void ServoConfig(){
    TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); // TIMER2 - Fast PWM configuration
    TCCR2B = (1 << CS22) | (1 << CS20) | (1<<CS21); // Prescaler of 1024 -- (16000000/(256*1024) = 61Hz)
    DDRB |= (1 << PB3); // Set PB3 as output (OC2A pin)
}

void LoadLeft(){
    OCR2A = 23;
}

void LoadRight(){
    OCR2A = 40;
}

void DoneLoading(){
    OCR2A = 32;
}



