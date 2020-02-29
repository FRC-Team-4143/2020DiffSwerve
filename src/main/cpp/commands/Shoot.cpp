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
	counter = 0;
	//motor->SetPercentPower(0.0);
	_lastButton = false; 
}

// ==========================================================================

void Shoot::Execute() {

	float joyz = Robot::oi->GetJoystick2Z();
	Robot::shooter->TurretMove(joyz * 0.2);

	if(Robot::oi->GetRightTrigger2() > 0.5) {
		counter++;	
		if( Robot::oi->GetButtonX2()/*counter > 150*/) Robot::shooter->Feed();
		else Robot::shooter->FeedStop();
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
	//turret stuff
	float Kp_vel = 0.0010f; 
	auto button = Robot::oi->GetButtonStart();
	std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	float tx = table->GetNumber("tx", 0.0f);
	frc::SmartDashboard::PutNumber("TX",tx); //MAX: 15 MIN: -15

	if (button == 1){  //Left Bumper
		heading_error = tx;
		
		if(!_lastButton){ //Runs once when button is pressed
			steering_adjust = 0.0f;
			steering_adjust_last = 0.0f;
		}

		//Velocity Based Offset Code
		if (tx > 0.0){
			adjust_speed = Kp_vel*heading_error - 0.05;
		} else if (tx < 0.0){
			adjust_speed = Kp_vel*heading_error + 0.05;
		} else{
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
	Robot::shooter->TurretMove(0.);
}

// ==========================================================================

void Shoot::Interrupted() {
	End();
}

// ==========================================================================
