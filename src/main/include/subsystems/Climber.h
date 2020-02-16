// ==========================================================================
// Climber class
// The Climber class implements an IClimber subsystem. (Modeled after Pickup System)
// ==========================================================================
#pragma once
#include "subsystems/IClimber.h"
#include <frc/DoubleSolenoid.h>
#include <frc/Solenoid.h>
#include <memory>

class Climber : public IClimber {
public:

	Climber(int solenoid1ForwardChannel, int solenoid1ReverseChannel, int solenoid2ForwardChannel, int solenoid2ReverseChannel, int solenoidBrakeChannel);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IClimber methods
	virtual void Extend() override;
	virtual void Retract() override;
	virtual void Brake() override;

private:

	std::unique_ptr<frc::DoubleSolenoid> _solenoid1;
	std::unique_ptr<frc::DoubleSolenoid> _solenoid2;
	std::unique_ptr<frc::Solenoid> _brake;
};

// ==========================================================================