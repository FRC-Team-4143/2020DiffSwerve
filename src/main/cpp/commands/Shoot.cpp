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
	counter = 0;
}

// ==========================================================================

void Shoot::Execute() {

	float joyz = Robot::oi->GetJoystick2Z();
	Robot::shooter->TurretMove(joyz * 0.2);

	if(Robot::oi->GetRightTrigger2() > 0.5) {
		counter++;	
		if(counter > 150) Robot::shooter->Feed();
		Robot::shooter->ShootStart();
	
	} else {
		counter = 0;
		Robot::shooter->ShootStop();
		Robot::shooter->FeedStop();
	}

	if(Robot::oi->GetButtonA2()) {
		Robot::shooter->Stir();
	} 
	else if (Robot::oi->GetButtonB2()) {
		Robot::shooter->StirReverse();
	} else {
		Robot::shooter->StirStop();
	}
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
