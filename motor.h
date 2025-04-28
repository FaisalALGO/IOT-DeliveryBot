#ifndef MOTOR_H
#define MOTOR_H

#define DEFAULT_SPEED 40
#define standby_pin PD3
#define right_wheels PD7
#define left_wheels PB0

#include <stdint.h>

void MotorsConfig();
void SetSpeed (uint8_t);
void SetWheelDirection(uint8_t, uint8_t);
//--------------------------------
void DriveStraight();
void Reverse();
void TurnRight();
void TurnLeft();
void StopVehicle();

#endif

