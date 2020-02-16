// ==========================================================================
// ControlPanel class
// The ControlPanel class implements an IControlPanel subsystem. (Modeled after Climber System)
// ==========================================================================
#pragma once
#include "subsystems/IControlPanel.h"
#include <frc/DoubleSolenoid.h>
#include <frc/Solenoid.h>
#include <memory>

class ControlPanel : public IControlPanel {
public:

	ControlPanel(int channelfwd, int channelrev);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IControlPanel methods
	virtual void nothing() override;

private:

	std::unique_ptr<frc::DoubleSolenoid> _solenoid1;

};

// ==========================================================================