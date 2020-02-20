#include "subsystems/Winch.h"
#include <ctre/Phoenix.h>
#include "commands/WinchActive.h"
#include "controllers/VelocityTalonFXController.h"

// ==========================================================================

Winch::Winch(int canId)
:	IWinch("Winch") {
	_winch = std::make_unique<VelocityTalonFXController>(canId);
}

// ==========================================================================

void Winch::InitDefaultCommand() {
	// No default command needed for this subsystem.
	SetDefaultCommand(new WinchActive());
}

// ==========================================================================

void Winch::WinchUp() {
	_winch->SetPercentPower(0.10);
}

// ==========================================================================

void Winch::WinchDown() {
	_winch->SetPercentPower(-0.10);
}

// ==========================================================================

void Winch::WinchDrive(float speed) {
	_winch->SetPercentPower(speed);
}

// ==========================================================================

void Winch::WinchStop() {
	_winch->SetPercentPower(0);
}

// ==========================================================================
