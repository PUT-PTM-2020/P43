#include "Control.h"



bool CalibrateClosed() {
	ManualControl();
	P.closed = P.current = 0;
	CalibrateOpen();
}

bool CalibrateOpen() {
	ManualControl();
	P.open = P.current;
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

void Open() {
	while (P.current < P.open) {
		stepper_motor_rotate_by_angle(10, 1, gRPM);
		P.current += 10;
	}
}

void CloseToTheLimit() {
	while (P.current > P.closed) {
		stepper_motor_rotate_by_angle(10, 0, gRPM);
		P.current -= 10;
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
