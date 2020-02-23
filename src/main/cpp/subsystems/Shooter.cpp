#include "subsystems/Shooter.h"
#include <ctre/Phoenix.h>
#include "controllers/VictorController.h"
#include "controllers/SparkMaxController.h"
#include "controllers/VelocityTalonFXController.h"
#include "commands/Shoot.h"
#include <frc/smartdashboard/SmartDashboard.h>


// ==========================================================================

Shooter::Shooter(int shooterCANId, int turretCANId, int feederCANId, int stirCANId)
:	IShooter("Shooter") {
	_shooter = std::make_unique<VelocityTalonFXController>(shooterCANId);
	_turret = std::make_unique<SparkMaxController>(turretCANId);
	_feeder = std::make_unique<VictorController>(feederCANId);
	_stir = std::make_unique<VictorController>(stirCANId);
}

// ==========================================================================

void Shooter::InitDefaultCommand() {
	// No default command needed for this subsystem.
	SetDefaultCommand(new Shoot());
}

// ==========================================================================

void Shooter::TurretMove(float velocity){
	_turret->SetPercentPower(velocity);
}

// ==========================================================================
void Shooter::TurretLeft() {
	_turret->SetPercentPower(0.10);
}

// ==========================================================================

void Shooter::TurretStop() {
	_turret->SetPercentPower(0);
}

// ==========================================================================

void Shooter::TurretRight() {
	_turret->SetPercentPower(-0.10);
}

// ==========================================================================

void Shooter::Feed() {
	//frc::SmartDashboard::PutNumber("shooter speed", _shooter->GetEncoderPosition());
	//if(_shooter->GetEncoderPosition() > 3000) {
		_feeder->SetPercentPower(1.0);
	//}
}

// ==========================================================================

void Shooter::FeedStop() {
	_feeder->SetPercentPower(0.00);
}

// ==========================================================================

void Shooter::Stir() {
	_stir->SetPercentPower(1.00);
}

// ==========================================================================

void Shooter::StirReverse() {
	_stir->SetPercentPower(-1.00);
}

// ==========================================================================

void Shooter::StirStop() {
	_stir->SetPercentPower(0);
}

// ==========================================================================

void Shooter::ShootStart() {
	_shooter->SetPercentPower(.80);
}

// ==========================================================================

void Shooter::ShootStop() {
	_shooter->SetPercentPower(0);
}

// ==========================================================================
