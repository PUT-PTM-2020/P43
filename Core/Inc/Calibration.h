#ifndef CALIBRATION
#define CALIBRATION

#include "CustomStepperLib.h"
#include "Communication.h"

struct Position {
	float Current;
	float FullyTurned; //the angle required to turn from the leftmost to the rightmost position
	bool Closed; //0 for the leftmost, and 1 for the rightmost position
	float Open;
};

bool CalibrateRightBoundary(Position& P) {
}

bool CalibrateLeftBoundary(Position& P) {

}

bool MarkOpen(Position& P) {

}

bool MarkClosed(Position& P) {

}

#endif