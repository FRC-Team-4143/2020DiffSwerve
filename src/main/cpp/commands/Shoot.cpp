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

	// ---------------
	// Turret control
	// ---------------

	auto joyz = Robot::oi->GetJoystick2Z();
	//Robot::shooter->TurretMove(joyz * 0.2);
	std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	float tx = table->GetNumber("tx", 0.0f);
	frc::SmartDashboard::PutNumber("TX",tx); //MAX: 15 MIN: -15

	constexpr float MIN_ALLOWED_ANGLE = -20;
	constexpr float MAX_ALLOWED_ANGLE = 250;

	constexpr int GYRO_DELAY_TICKS = 7 * 50;

	_gyroCounter++;

	if (joyz != 0) {
		_targetDegrees += joyz;
		_gyroCounter = 0;
	}

	if (Robot::oi->GetLeftTrigger2() < .5 && _gyroCounter >= GYRO_DELAY_TICKS) {
		
			if (Robot::oi->GetRightTrigger2() > 0.75 ){
			  if (_targetDegrees > 0.001 || _targetDegrees < -0.001)
				_targetDegrees += tx/4.0;
			} else {
				_targetDegrees = -Robot::gyroSub->PIDGet();
				// Gyro returns -180 to +180. Convert to 0 to 360.
				if (_targetDegrees < 0)
					_targetDegrees += 360;
			}
	} 
	
	if (_targetDegrees < MIN_ALLOWED_ANGLE) {
		_targetDegrees = MIN_ALLOWED_ANGLE;
	}
	else if (_targetDegrees > MAX_ALLOWED_ANGLE) {
		_targetDegrees = MIN_ALLOWED_ANGLE;
	}

	Robot::shooter->TurretMove(_targetDegrees);
	frc::SmartDashboard::PutNumber("Target Degrees", _targetDegrees); 

	// ----------------
	// Shooter control
	// ----------------

	if (Robot::oi->GetRightTrigger2() > 0.25) {
		//counter++;
		Robot::shooter->ShootStart();
	}
	else {
		//counter = 0;
		Robot::shooter->ShootStop();
	}

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
