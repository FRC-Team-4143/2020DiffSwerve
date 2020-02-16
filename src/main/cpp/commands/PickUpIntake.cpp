#include "commands/PickUpIntake.h"
#include "Robot.h"

// ==========================================================================

PickUpIntake::PickUpIntake()
:	frc::Command("PickUp Intake") {
	Requires(Robot::pickUp.get());
}

// ==========================================================================

void PickUpIntake::Initialize() {
}

// ==========================================================================

void PickUpIntake::Execute() {
	Robot::pickUp->Intake();
}

// ==========================================================================

bool PickUpIntake::IsFinished() {
	return true;
}

// ==========================================================================

void PickUpIntake::End() {
    Robot::pickUp->StopIntake();
}

// ==========================================================================

void PickUpIntake::Interrupted() {
	End();
}

// ==========================================================================
