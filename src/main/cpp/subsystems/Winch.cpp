#include "subsystems/Winch.h"
#include <ctre/Phoenix.h>
#include "commands/WinchActive.h"
#include "controllers/VelocityTalonFXController.h"
#include "frc/Solenoid.h"

// ==========================================================================

Winch::Winch(int canId, int brakeChannel)
:	IWinch("Winch") {
	_winch = std::make_unique<VelocityTalonFXController>(canId);
	_winchBrake = std::make_unique<frc::Solenoid>(brakeChannel);
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

void Winch::WinchBrake(bool engageBrake) {
	_winchBrake->Set(engageBrake);
}

// ==========================================================================
