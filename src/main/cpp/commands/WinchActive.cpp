#include "commands/WinchActive.h"
#include "Robot.h"

// ==========================================================================

WinchActive::WinchActive()
:	frc::Command("WinchActive") {
	Requires(Robot::winch.get());
}

// ==========================================================================

void WinchActive::Initialize() {
	counter = 0;
}

// ==========================================================================

void WinchActive::Execute() {
	float joy2y = Robot::oi->GetJoystick2Y() * 0.5;
	if(joy2y != 0){
		counter++;
		Robot::winch->WinchBrake(false);
		if(counter > 25) Robot::winch->WinchDrive(joy2y);
	} else {
		counter = 0;
		Robot::winch->WinchBrake(true);
		Robot::winch->WinchDrive(0);
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
