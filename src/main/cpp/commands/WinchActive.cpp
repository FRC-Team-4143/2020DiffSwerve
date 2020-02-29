#include "commands/WinchActive.h"
#include "Robot.h"

// ==========================================================================

WinchActive::WinchActive()
:	frc::Command("WinchActive") {
	Requires(Robot::winch.get());
}

// ==========================================================================

void WinchActive::Initialize() {
	_counter = 0;
}

// ==========================================================================

void WinchActive::Execute() {
	float joy2y = Robot::oi->GetJoystick2Y() * 0.5;
	if (joy2y != 0) {
		_counter++;
		Robot::winch->WinchBrake(true);
		if(_counter > 25) {
			Robot::winch->WinchDrive(joy2y);
		}
	}
	else {
		_counter = 0;
		Robot::winch->WinchBrake(false);
		Robot::winch->WinchDrive(0);
	}

	if (Robot::oi->GetButtonStart()) {
		Robot::climber->BalanceRight();
	}
	else if (Robot::oi->GetButtonBack()) {
		Robot::climber->BalanceLeft();
	}
	else {
		Robot::climber->BalanceStop();
	}
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
