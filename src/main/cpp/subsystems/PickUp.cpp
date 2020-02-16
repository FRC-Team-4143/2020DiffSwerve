#include "subsystems/PickUp.h"

// ==========================================================================

PickUp::PickUp(int solenoid1ForwardChannel, int solenoid1ReverseChannel, int solenoid2ForwardChannel, int solenoid2ReverseChannel)
:	IPickUp("PickUp") {
	_solenoid1 = std::make_unique<frc::DoubleSolenoid>(solenoid1ForwardChannel, solenoid1ReverseChannel);
	_solenoid2 = std::make_unique<frc::DoubleSolenoid>(solenoid2ForwardChannel, solenoid2ReverseChannel);
}

// ==========================================================================

void PickUp::InitDefaultCommand() {
	// No default command needed for this subsystem.
}

// ==========================================================================

void PickUp::Extend() {
	_solenoid1->Set(frc::DoubleSolenoid::kForward);
	_solenoid2->Set(frc::DoubleSolenoid::kForward);
}

// ==========================================================================

void PickUp::Retract() {
	_solenoid1->Set(frc::DoubleSolenoid::kReverse);
	_solenoid2->Set(frc::DoubleSolenoid::kReverse);
}

// ==========================================================================
