#include "commands/Shoot.h"
#include "OI.h"
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

	float joyx = Robot::oi->GetJoystick2X();
	Robot::shooter->TurretMove(joyx);
	//Robot::shooter->ShootStart();
	//Robot::shooter->Feed();
}

// ==========================================================================

bool Shoot::IsFinished() {
	return false;
}

// ==========================================================================

void Shoot::End() {
	Robot::shooter->ShootStop();
	Robot::shooter->FeedStop();
	Robot::shooter->TurretMove(0.);
}

// ==========================================================================

void Shoot::Interrupted() {
	End();
}

// ==========================================================================
