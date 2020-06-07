#ifndef P43_CONTROL
#define P43_CONTROL

#include "CustomStepperLib.h"

bool CalibrateClosed();

bool CalibrateOpen();

void ManualControl();

void Open();

void CloseToTheLimit();

void LightControl();

void TimeControl();

#endif