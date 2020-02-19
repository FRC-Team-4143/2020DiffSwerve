#include "subsystems/Shooter.h"
#include <ctre/Phoenix.h>
#include "controllers/VictorController.h"

// ==========================================================================

Shooter::Shooter(int shooterCANId, int turretCANId, int feederCANId, int stirCANId)
:	IShooter("Shooter") {
	//_shooter = std::make_unique<TalonFX>(shooterCANId);
	_turret = std::make_unique<VictorController>(turretCANId);
	_feeder = std::make_unique<VictorController>(feederCANId);
	_stir = std::make_unique<VictorController>(stirCANId);
}

// ==========================================================================

void Shooter::InitDefaultCommand() {
	// No default command needed for this subsystem.
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
	_feeder->SetPercentPower(0.10);
}

// ==========================================================================

void Shooter::FeedStop() {
	_feeder->SetPercentPower(0.00);
}

// ==========================================================================

void Shooter::Stir() {
	_stir->SetPercentPower(0.10);
}

// ==========================================================================

void Shooter::StirStop() {
	_stir->SetPercentPower(0.10);
}

// ==========================================================================

void Shooter::Shoot() {
	_shooter-> SetPercentPower(0);
}

// ==========================================================================
