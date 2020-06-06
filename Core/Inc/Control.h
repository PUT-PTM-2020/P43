#ifndef P43_CALIBRATION
#define P43_CALIBRATION

#include "CustomStepperLib.h"

bool calibrationMode;

struct Position {
	float current; //In degrees
	float closed; //the angle required to turn from the leftmost to the rightmost position
	float open; 
};
Position& P;

int gRPM = 10; //global RPM

bool CalibrateClosed() {
	ManualControl();
	P.closed==P.current;
	CalibrateOpen();
}

bool CalibrateOpen() {
	ManualControl();
	P.open == P.current;
}

void ManualControl() {
	do {
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == GPIO_PIN_SET) {
			stepper_motor_rotate_by_angle(10, 1, gRPM);
			P.current += 10;
		}
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14) == GPIO_PIN_SET) {
			stepper_motor_rotate_by_angle(10, 0, gRPM);
			P.current -= 10;
		}
	} while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET);
}

void OpenToTheLimit() {
	if (P.current < P.closed) {
		stepper_motor_rotate_by_angle(10, 1, gRPM);
		P.current += 10;
	}
}

void CloseToTheLimit() {
	if (P.current > 0) {
		stepper_motor_rotate_by_angle(10, 0, gRPM);
		P.current -= 10;
	}
}

void LightControl() {

}
void TimeControl() {

}
#endif