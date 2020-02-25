// ==========================================================================
// Winch class
// The Winch class implements an IWinch subsystem.
// ==========================================================================
#pragma once
#include "subsystems/IWinch.h"
#include "controllers/IMultiController.h"
#include <memory>
#include "frc/Solenoid.h"

class Winch : public IWinch {
public:

	Winch(int canId, int brakeChannel);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IWinch methods
	virtual void WinchUp() override;
	virtual void WinchDown() override;
	virtual void WinchDrive(float speed) override;
	virtual void WinchStop() override;
	virtual void WinchBrake(bool engageBrake) override;

private:

	std::unique_ptr<IMultiController> _winch;
	std::unique_ptr<frc::Solenoid>_winchBrake;
};

// ==========================================================================
