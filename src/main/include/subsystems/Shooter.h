// ==========================================================================
// Shooter class
// The Shooter class implements an IShooter subsystem.
// ==========================================================================
#pragma once
#include "subsystems/IShooter.h"
#include "controllers/IMultiController.h"
#include <memory>

class Shooter : public IShooter {
public:

	Shooter(int shooterCANId, int turretCANId, int feederCANId, int stirCANId);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IShooter methods
    virtual void TurretLeft() override;
    virtual void TurretStop() override;
    virtual void TurretRight() override;
    virtual void Feed() override;
    virtual void Stir() override;
    virtual void StirStop() override;
    virtual void Shoot() override;
private:
	std::unique_ptr<IMultiController> _shooter;
	std::unique_ptr<IMultiController> _turret;
	std::unique_ptr<IMultiController> _feeder;
	std::unique_ptr<IMultiController> _stir;

};

// ==========================================================================
