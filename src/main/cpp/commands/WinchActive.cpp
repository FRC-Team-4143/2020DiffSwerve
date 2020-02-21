#include "commands/WinchActive.h"
#include "Robot.h"

// ==========================================================================

WinchActive::WinchActive()
:	frc::Command("WinchActive") {
	Requires(Robot::winch.get());
}

// ==========================================================================

void WinchActive::Initialize() {
}

// ==========================================================================

void WinchActive::Execute() {
	Robot::winch->WinchDrive(Robot::oi->GetJoystick2Y());
}

// ==========================================================================

bool WinchActive::IsFinished() {
	return false;
}

// ==========================================================================

void WinchActive::End() {
	Robot::winch->WinchStop();
}

// ==========================================================================

void WinchActive::Interrupted() {
	End();
}

// ==========================================================================
