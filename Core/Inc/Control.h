#ifndef P43_CALIBRATION
#define P43_CALIBRATION

#include "CustomStepperLib.h"

bool calibrationMode;

struct Position {
	float current; //In degrees
	float closed; //the angle required to turn from the leftmost to the rightmost position
	float open;
};
Position P;

int gRPM = 10; //global RPM

bool CalibrateClosed();

bool CalibrateOpen();

void ManualControl();

void Open();

void CloseToTheLimit();

void LightControl();

void TimeControl();

#endif