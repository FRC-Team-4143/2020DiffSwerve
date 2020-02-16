#include "commands/PickUpRevIntake.h"
#include "Robot.h"

// ==========================================================================

PickUpRevIntake::PickUpRevIntake()
:	frc::Command("PickUp Reverse Intake") {
	Requires(Robot::pickUp.get());
}

// ==========================================================================

void PickUpRevIntake::Initialize() {
}

// ==========================================================================

void PickUpRevIntake::Execute() {
	Robot::pickUp->RevIntake();
}

// ==========================================================================

bool PickUpRevIntake::IsFinished() {
	return true;
}

// ==========================================================================

void PickUpRevIntake::End() {
    Robot::pickUp->StopIntake();
}

// ==========================================================================

void PickUpRevIntake::Interrupted() {
	End();
}

// ==========================================================================
