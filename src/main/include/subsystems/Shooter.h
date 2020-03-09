// ==========================================================================
// Shooter class
// The Shooter class implements an IShooter subsystem.
// ==========================================================================
#pragma once
#include "subsystems/IShooter.h"
#include "controllers/IMultiController.h"
#include "controllers/IPositionMultiController.h"
#include "controllers/IVelocityMultiController.h"
#include <networktables/NetworkTable.h>
#include <memory>

class Shooter : public IShooter {
public:

	Shooter(int shooterCANId, int turretCANId, int feederCANId, int stirCANId);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IShooter methods
	virtual void TurretMove(float degrees) override;
	virtual void TurretLeft() override;
	virtual void TurretStop() override;
	virtual void TurretRight() override;
	virtual void Feed(float feedspeed) override;
	virtual void FeedStop() override;
	virtual void Stir() override;
	virtual void StirReverse() override;
	virtual void StirStop() override;
	virtual void ShootStart(float speedPercent) override;
	virtual void ShootStop() override;
	virtual void TurretZero() override;
	
	std::unique_ptr<IPositionMultiController> _turret;

private:

	std::unique_ptr<IVelocityMultiController> _shooter;
	std::unique_ptr<IMultiController> _feeder;
	std::unique_ptr<IMultiController> _stir;
	std::shared_ptr<NetworkTable> _limelightTable;
};

// ==========================================================================
