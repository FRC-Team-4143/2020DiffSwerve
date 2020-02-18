#include "subsystems/Climber.h"

// ==========================================================================

Climber::Climber(int extenderForwardChannel, int extenderReverseChannel, int brakeForwardChannel, int brakeReverseChannel)
:	IClimber("Climber") {
	_extender = std::make_unique<frc::DoubleSolenoid>(extenderForwardChannel, extenderReverseChannel);
	_brake = std::make_unique<frc::DoubleSolenoid>(brakeForwardChannel, brakeReverseChannel);
}

// ==========================================================================

void Climber::InitDefaultCommand() {
	// No default command needed for this subsystem.
}

// ==========================================================================

void Climber::Extend() {
	_extender->Set(frc::DoubleSolenoid::kForward);
}

// ==========================================================================

void Climber::Retract() {
	_extender->Set(frc::DoubleSolenoid::kReverse);
}

// ==========================================================================

void Climber::EngageBrake() {
	_brake->Set(frc::DoubleSolenoid::kForward);
}

// ==========================================================================

void Climber::ReleaseBrake() {
	_brake->Set(frc::DoubleSolenoid::kReverse);
}

// ==========================================================================
