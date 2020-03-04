#include "commands/Shoot.h"
#include "OI.h"
#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>

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
	float joyz = Robot::oi->GetJoystick2Z();
	//Robot::shooter->TurretMove(joyz * 0.2);

	if (joyz > .3) degrees += joyz;
	if (joyz < -.3) degrees -= -joyz;
	if (degrees < 0) degrees = 0.;
	if (degrees > 270.) degrees = 270.;

	Robot::shooter->TurretMove(degrees);

	if (Robot::oi->GetRightTrigger2() > 0.5) {
		//counter++;
		Robot::shooter->ShootStart();
			
	}
	else {
		//counter = 0;
		Robot::shooter->ShootStop();
	}

	if (Robot::oi->GetButtonX2()) {
		Robot::shooter->Feed(1);
	}
	else if (Robot::oi->GetButtonY2()) {
		Robot::shooter->Feed(-0.5);
	}
	else {
		Robot::shooter->FeedStop();
	}

	if (Robot::oi->GetButtonA2()) {
		Robot::shooter->Stir();
	}
	else if (Robot::oi->GetButtonB2()) {
		Robot::shooter->StirReverse();
	}
	else {
		Robot::shooter->StirStop();
	}

	//turret stuff
	float Kp_vel = 0.0010f; 
	auto button = 0; //Robot::oi->GetButtonStart();
	std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	float tx = table->GetNumber("tx", 0.0f);
	frc::SmartDashboard::PutNumber("TX",tx); //MAX: 15 MIN: -15

	if (button == 1){  //Left Bumper
		auto heading_error = tx;

		if(!_lastButton){ //Runs once when button is pressed
			//steering_adjust = 0.0f;
			//steering_adjust_last = 0.0f;
		}

		//Velocity Based Offset Code
		if (tx > 0.0) {
			adjust_speed = Kp_vel*heading_error - 0.05;
		}
		else if (tx < 0.0) {
			adjust_speed = Kp_vel*heading_error + 0.05;
		}
		else {
			adjust_speed = 0; 
		}
	}

	//actual motor control
	//Robot::shooter->TurretMove(adjust_speed);

	/* save button state for on press detect */
	_lastButton = button; 
	frc::SmartDashboard::PutNumber("Adjust Speed", adjust_speed); 
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
