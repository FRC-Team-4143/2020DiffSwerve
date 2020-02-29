// ==========================================================================
// IControlPanel interface
// The IControlPanel interface represents the functionality of the Control Panel subsystem.
// ==========================================================================
#pragma once
#include <frc/commands/Subsystem.h>

class IControlPanel : public frc::Subsystem {
public:

	IControlPanel(const wpi::Twine& name);

	virtual void ColorUp() = 0;
	virtual void ColorDown() = 0; 
	virtual void TogglePanel() = 0;
};

// ==========================================================================
