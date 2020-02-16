#include "subsystems/ControlPanel.h"

// ==========================================================================

ControlPanel::ControlPanel(int channelfwd, int channelrev)
:	IControlPanel("ControlPanel") {
	_solenoid1 = std::make_unique<frc::DoubleSolenoid>(channelfwd, channelrev);
}

// ==========================================================================

void ControlPanel::InitDefaultCommand() {
	// No default command needed for this subsystem.
}

// ==========================================================================

void ControlPanel::nothing() {
	_solenoid1->Set(frc::DoubleSolenoid::kForward);
}

