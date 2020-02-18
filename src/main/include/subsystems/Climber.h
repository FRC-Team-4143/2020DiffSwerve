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

	Climber(int extenderForwardChannel, int extenderReverseChannel, int brakeForwardChannel, int brakeReverseChannel);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IClimber methods
	virtual void Extend() override;
	virtual void Retract() override;
	virtual void EngageBrake() override;
	virtual void ReleaseBrake() override;

private:

	std::unique_ptr<frc::DoubleSolenoid> _extender;
	std::unique_ptr<frc::DoubleSolenoid> _brake;
};

// ==========================================================================
