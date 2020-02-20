#include "commands/Shoot.h"
#include "Robot.h"

// ==========================================================================

Shoot::Shoot()
:	frc::Command("Shoot") {
	Requires(Robot::shooter.get());
}

// ==========================================================================

void Shoot::Initialize() {
}

// ==========================================================================

void Shoot::Execute() {
	Robot::shooter->Shoot();
	Robot::shooter->Feed();
	Robot::shooter->Stir();
}

// ==========================================================================

bool Shoot::IsFinished() {
	return false;
}

// ==========================================================================

void Shoot::End() {
	Robot::shooter->ShootStop();
	Robot::shooter->FeedStop();
}

// ==========================================================================

void Shoot::Interrupted() {
	End();
}

// ==========================================================================
