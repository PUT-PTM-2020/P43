#include "Control.h"
#include <cmath>

int gRPM = 10;

float currentPos; //In degrees
float closedPos; //the angle required to turn from the leftmost to the rightmost position
float openPos;

bool CalibrateClosed() {
	ManualControl();
	closedPos = currentPos = 0;
	CalibrateOpen();
}

bool CalibrateOpen() {
	ManualControl();
	openPos = currentPos;
}

void ManualControl() {
	do {
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == GPIO_PIN_SET) {
			stepper_motor_rotate_by_angle(10, 1, gRPM);
			currentPos += 10;
		}
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14) == GPIO_PIN_SET) {
			stepper_motor_rotate_by_angle(10, 0, gRPM);
			currentPos -= 10;
		}
	} while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET || HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET);
}

void Open() {
	if (openPos - currentPos < 0) {
		stepper_motor_rotate_by_angle(abs(currentPos - openPos), 1, gRPM);
		currentPos== openPos;
	}
	else if (openPos - currentPos > 0) {
		stepper_motor_rotate_by_angle(abs(currentPos - openPos), 0, gRPM);
		currentPos== openPos;
	}
}

void CloseToTheLimit() {
	if (closedPos - currentPos < 0) {
		stepper_motor_rotate_by_angle(abs(currentPos - openPos), 0, gRPM);
		currentPos == closedPos;
	}
}

void TimeControl() {
	while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET) {
		//while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET){} //Ustawianie czasu
	}
}
