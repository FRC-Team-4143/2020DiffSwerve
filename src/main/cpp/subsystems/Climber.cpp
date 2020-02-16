#include "subsystems/Climber.h"

// ==========================================================================

Climber::Climber(int solenoid1ForwardChannel, int solenoid1ReverseChannel, int solenoid2ForwardChannel, int solenoid2ReverseChannel, int solenoidBrakeChannel)
:	IClimber("Climber") {
	_solenoid1 = std::make_unique<frc::DoubleSolenoid>(solenoid1ForwardChannel, solenoid1ReverseChannel);
	_solenoid2 = std::make_unique<frc::DoubleSolenoid>(solenoid2ForwardChannel, solenoid2ReverseChannel);
	_brake = std::make_unique<frc::Solenoid>(solenoidBrakeChannel);
}

// ==========================================================================

void Climber::InitDefaultCommand() {
	// No default command needed for this subsystem.
}

// ==========================================================================

void Climber::Extend() {
	_solenoid1->Set(frc::DoubleSolenoid::kForward);
	_solenoid2->Set(frc::DoubleSolenoid::kForward);
}

// ==========================================================================

void Climber::Retract() {
	_solenoid1->Set(frc::DoubleSolenoid::kReverse);
	_solenoid2->Set(frc::DoubleSolenoid::kReverse);
}

// ==========================================================================

void Climber::Brake() {
	_brake->Set(true);
}

// ==========================================================================