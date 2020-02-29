#include "subsystems/Climber.h"
#include "controllers/VictorController.h"

// ==========================================================================

Climber::Climber(int extenderForwardChannel, int extenderReverseChannel, int boatCanId)
:	IClimber("Climber") {
	_extender = std::make_unique<frc::DoubleSolenoid>(extenderForwardChannel, extenderReverseChannel);
	_boatroller= std::make_unique<VictorController>(boatCanId);
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

void Climber::BalanceLeft() {
	_boatroller->SetPercentPower(-0.50);
}

// ==========================================================================

void Climber::BalanceRight() {
	_boatroller->SetPercentPower(0.50);
}

// ==========================================================================

void Climber::BalanceStop() {
	_boatroller->SetPercentPower(0);
}

// ==========================================================================