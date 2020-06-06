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


/*Placeholders*/
bool b1, b2, b3, b4, b5, b6, b7, b8;
/*End of placeholders*/

bool CalibrateClosed(Position& P) {
	ManualControl();
	P.closed==P.current;
}

bool CalibrateOpen(Position& P) {
	ManualControl();
	P.closed == P.current;
}

void ManualControl() {
	if (b7 == 1) {
		stepper_motor_rotate_by_angle(10, 1, gRPM);
		P.current += 10;
	}
	else if (b8 == 1) {
		stepper_motor_rotate_by_angle(10, 0, gRPM);
		P.current -= 10;
	}
	if (calibrationMode && b6 == 1)
		return;
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

#endif