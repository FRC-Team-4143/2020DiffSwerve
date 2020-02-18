// ==========================================================================
// IClimber interface
// The IClimber interface represents the functionality of a climber subsystem.
// ==========================================================================
#pragma once
#include <frc/commands/Subsystem.h>

class IClimber : public frc::Subsystem {
public:

	IClimber(const wpi::Twine& name);

	virtual void Extend() = 0;
	virtual void Retract() = 0;
	virtual void EngageBrake() = 0;
	virtual void ReleaseBrake() = 0;
};

// ==========================================================================
