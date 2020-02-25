// ==========================================================================
// Climber class
// The Climber class implements an IClimber subsystem.
// ==========================================================================
#pragma once
#include "subsystems/IClimber.h"
#include <frc/DoubleSolenoid.h>
#include <memory>

class Climber : public IClimber {
public:

	Climber(int extenderForwardChannel, int extenderReverseChannel);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IClimber methods
	virtual void Extend() override;
	virtual void Retract() override;

private:

	std::unique_ptr<frc::DoubleSolenoid> _extender;
};

// ==========================================================================
