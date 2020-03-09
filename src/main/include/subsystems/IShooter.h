// ==========================================================================
// IShooter interface
// ==========================================================================
#pragma once
#include <frc/commands/Subsystem.h>
#include "controllers/IPositionMultiController.h"

class IShooter : public frc::Subsystem {
public:

	IShooter(const wpi::Twine& name);
	virtual void TurretMove(float velocity) = 0; 
	virtual void TurretLeft() = 0;
	virtual void TurretRight() = 0;
	virtual void TurretStop() = 0;
	virtual void Feed(float feedspeed) = 0;
	virtual void FeedStop() = 0;
	virtual void Stir() = 0;
	virtual void StirReverse() = 0;
	virtual void StirStop() = 0;
	virtual void ShootStart(float speedPercent) = 0;
	virtual void ShootStop() = 0;
	virtual void TurretZero() = 0;

	std::unique_ptr<IPositionMultiController> _turret = 0;
};

// ==========================================================================
