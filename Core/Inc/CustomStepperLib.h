#ifndef P43_CUSTOMSTEPPERLIB
#define P43_CUSTOMSTEPPERLIB

#include "main.h"
#include <stdbool.h>
#include <cstdint>

#define spr 2038 //number of steps per revolution

void delay(uint16_t miliseconds);

void stepper_motor_set_rpm(uint8_t rpm);

void stepper_motor_full_drive(int step_id);

void stepper_motor_rotate_by_angle(float rotation_angle, bool dir, uint8_t rpm);

#endif
