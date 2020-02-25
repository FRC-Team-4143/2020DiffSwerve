#include "subsystems/Climber.h"

// ==========================================================================

Climber::Climber(int extenderForwardChannel, int extenderReverseChannel)
:	IClimber("Climber") {
	_extender = std::make_unique<frc::DoubleSolenoid>(extenderForwardChannel, extenderReverseChannel);
}

// ==========================================================================

void Climber::InitDefaultCommand() {
	// No default command needed for this subsystem.
}

// ==========================================================================

void Climber::Extend() {
	_extender->Set(frc::DoubleSolenoid::kReverse);
}

// ==========================================================================

void Climber::Retract() {
	_extender->Set(frc::DoubleSolenoid::kForward);
}

// ==========================================================================
