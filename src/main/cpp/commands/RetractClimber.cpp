#include "commands/RetractClimber.h"
#include "Robot.h"

// ==========================================================================

RetractClimber::RetractClimber()
:	frc::Command("Retract Climber") {
}

// ==========================================================================

void RetractClimber::Initialize() {
}

// ==========================================================================

void RetractClimber::Execute() {
	Robot::pickUp->Retract();
}

// ==========================================================================

bool RetractClimber::IsFinished() {
	return true;
}

// ==========================================================================

void RetractClimber::End() {
}

// ==========================================================================

void RetractClimber::Interrupted() {
	End();
}

// ==========================================================================