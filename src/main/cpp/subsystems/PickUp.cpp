#include "subsystems/PickUp.h"
#include "commands/PickUpIntake.h"
#include "controllers/VictorController.h"

// ==========================================================================

PickUp::PickUp(int solenoid1ForwardChannel, int solenoid1ReverseChannel, int solenoid2ForwardChannel, int solenoid2ReverseChannel, int intakeCANId)
:	IPickUp("PickUp") {
	_solenoid1 = std::make_unique<frc::DoubleSolenoid>(solenoid1ForwardChannel, solenoid1ReverseChannel);
	_solenoid2 = std::make_unique<frc::DoubleSolenoid>(solenoid2ForwardChannel, solenoid2ReverseChannel);
	_intakeMotor = std::make_unique<VictorController>(intakeCANId);
}

// ==========================================================================

void PickUp::InitDefaultCommand() {
	SetDefaultCommand(new PickUpIntake());
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

void PickUp::Intake(float intakeSpeed) {
	_intakeMotor->SetPercentPower(intakeSpeed);
}

// ==========================================================================

void PickUp::StopIntake() {
	_intakeMotor->SetPercentPower(0);
}
// ==========================================================================

