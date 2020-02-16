// ==========================================================================
// PickUp class
// The PickUp class implements an IPickUp subsystem.
// ==========================================================================
#pragma once
#include "subsystems/IPickup.h"
#include <frc/DoubleSolenoid.h>
#include <memory>

class PickUp : public IPickUp {
public:

	PickUp(int solenoid1ForwardChannel, int solenoid1ReverseChannel, int solenoid2ForwardChannel, int solenoid2ReverseChannel);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IPickUp methods
	virtual void Extend() override;
	virtual void Retract() override;

private:

	std::unique_ptr<frc::DoubleSolenoid> _solenoid1;
	std::unique_ptr<frc::DoubleSolenoid> _solenoid2;
};

// ==========================================================================
