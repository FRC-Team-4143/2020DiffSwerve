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
	Robot::winch->WinchActive(-Robot::oi->GetRightTrigger() + Robot::oi->GetLeftTrigger());
}

// ==========================================================================

bool WinchActive::IsFinished() {
	return false;
}

// ==========================================================================

void WinchActive::End() {
	//Robot::winch->WinchActiveStop();
}

// ==========================================================================

void WinchActive::Interrupted() {
	End();
}

// ==========================================================================
