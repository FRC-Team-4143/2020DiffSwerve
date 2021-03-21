#include "commands/Shoot.h"
#include "OI.h"
#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>
#include <algorithm>

// ==========================================================================

Shoot::Shoot()
:	frc::Command("Shoot") {
	Requires(Robot::shooter.get());
}

// ==========================================================================

void Shoot::Initialize() {
	//counter = 0;
	//motor->SetPercentPower(0.0);
	_lastButton = false; 
}

// ==========================================================================

void Shoot::Execute() {
	
	speedPercent = frc::SmartDashboard::GetNumber("Pure Speed", 14400);

	// ---------------
	// Turret control
	// ---------------
	Robot::shooter->LimeLightControl(false);

	// ----------------
	// Shooter control
	// ----------------
	constexpr int MaxShootSpeed = 16000; //may be a problem

	if (Robot::oi->GetRightTrigger2() > 0.25) {
		//counter++;
		Robot::shooter->ShootStart(speedPercent);
	}
	else {
		//counter = 0;
		Robot::shooter->ShootStop();
	}
	if(Robot::oi->GetRightBumper2() && (speedPercent < MaxShootSpeed)) speedPercent += 200; //INCREASES speed
	if(Robot::oi->GetLeftBumper2() && (speedPercent > 200)) speedPercent -= 200; //DECREASES speed
	frc::SmartDashboard::PutNumber("Speed Percent", (speedPercent/MaxShootSpeed)*100);
	frc::SmartDashboard::PutNumber("Pure Speed", speedPercent);

	// ---------------
	// Feeder control
	// ---------------

	if (Robot::oi->GetButtonX2()) {
		Robot::shooter->Feed(1);
	}
	else if (Robot::oi->GetButtonY2()) {
		Robot::shooter->Feed(-0.5);
	}
	else {
		Robot::shooter->FeedStop();
	}

	// ----------------
	// Stirrer control
	// ----------------

	if (Robot::oi->GetButtonA2()) {
		Robot::shooter->Stir();
	}
	else if (Robot::oi->GetButtonB2()) {
		Robot::shooter->StirReverse();
	}
	else {
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
	//Robot::shooter->TurretMove(0.);
}

// ==========================================================================

void Shoot::Interrupted() {
	End();
}

// ==========================================================================
