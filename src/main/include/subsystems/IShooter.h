// ==========================================================================
// IShooter interface
// ==========================================================================
#pragma once
#include <frc/commands/Subsystem.h>

class IShooter : public frc::Subsystem {
public:

	IShooter(const wpi::Twine& name);

	virtual void TurretLeft() = 0;
	virtual void TurretRight() = 0;
	virtual void TurretStop() = 0;
	virtual void Feed() = 0;
	virtual void Stir() = 0;
	virtual void StirStop() = 0;
	virtual void Shoot() = 0;
};

// ==========================================================================
