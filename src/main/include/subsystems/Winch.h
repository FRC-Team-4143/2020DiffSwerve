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

	Winch(int WinchCANId);

	// Subsystem methods
	virtual void InitDefaultCommand() override;

	// IWinch methods
	virtual void WinchUp() override;
	virtual void WinchStop() override;
	virtual void WinchDown() override;
    virtual void WinchActive(float WinchSpeed) override;
    virtual void WinchActiveStop() override;

private:

	std::unique_ptr<IMultiController> _winch;
};

// ==========================================================================
