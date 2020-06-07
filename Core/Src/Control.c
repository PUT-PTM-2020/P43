#include "Control.h"

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
	while (currentPos < openPos) {
		stepper_motor_rotate_by_angle(10, 1, gRPM);
		currentPos += 10;
	}
}

void CloseToTheLimit() {
	while (currentPos > closedPos) {
		stepper_motor_rotate_by_angle(10, 0, gRPM);
		currentPos -= 10;
	}
}

void LightControl() {
	while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {
		//do stuff here
	}
}

void TimeControl() {
	while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET) {
		//while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET){} //Ustawianie czasu
	}
}
