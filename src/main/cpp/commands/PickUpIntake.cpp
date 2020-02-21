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
	Robot::pickUp->Intake(1.00);
}

// ==========================================================================

bool PickUpIntake::IsFinished() {
	return false;
}

// ==========================================================================

void PickUpIntake::End() {
	Robot::pickUp->IntakeStop();
}

// ==========================================================================

void PickUpIntake::Interrupted() {
	End();
}

// ==========================================================================
