// ==========================================================================
// Winch class
// The Winch class implements an IWinch subsystem.
// ==========================================================================
#pragma once
#include "subsystems/IWinch.h"
#include "controllers/IMultiController.h"
#include <memory>

class Winch : public IWinch {
public:

	Winch(int canId);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IWinch methods
	virtual void WinchUp() override;
	virtual void WinchDown() override;
	virtual void WinchDrive(float speed) override;
	virtual void WinchStop() override;

private:

	std::unique_ptr<IMultiController> _winch;
};

// ==========================================================================
