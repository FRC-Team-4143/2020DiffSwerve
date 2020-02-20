#include "subsystems/Winch.h"
#include <ctre/Phoenix.h>
#include "controllers/VictorController.h"
#include "controllers/VelocityTalonFXController.h"

// ==========================================================================

Winch::Winch(int WinchCANId)
:	IWinch("Winch") {
	_winch = std::make_unique<VelocityTalonFXController>(WinchCANId);
}
// ==========================================================================

void Winch::InitDefaultCommand() {
	// No default command needed for this subsystem.
}

// ==========================================================================

void Winch::WinchUp() {
	_winch->SetPercentPower(0.10);
}

// ==========================================================================

void Winch::WinchStop() {
	_winch->SetPercentPower(0);
}

// ==========================================================================

void Winch::WinchDown() {
	_winch->SetPercentPower(-0.10);
}

// ==========================================================================
void Winch::WinchActive(float WinchSpeed) {
	_winch->SetPercentPower(float (WinchSpeed));
}

// ==========================================================================

void Winch::WinchActiveStop() {
	_winch->SetPercentPower(0);
}