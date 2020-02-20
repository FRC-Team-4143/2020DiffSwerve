// ==========================================================================
// IWinch interface
// ==========================================================================
#pragma once
#include <frc/commands/Subsystem.h>

class IWinch : public frc::Subsystem {
public:

	IWinch(const wpi::Twine& name);

	virtual void WinchUp() = 0;
	virtual void WinchDown() = 0;
	virtual void WinchDrive(float speed) = 0;
	virtual void WinchStop() = 0;
};

// ==========================================================================
