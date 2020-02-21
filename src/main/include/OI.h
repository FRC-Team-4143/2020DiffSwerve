#pragma once
#include <frc/Joystick.h>
#include "commands/CrabDrive.h"

// ==========================================================================

class OI {
public:

	OI();

	float GetJoystickX();
	float GetJoystick2X();
	float GetJoystickY();
	float GetJoystickZ();

	float GetRightJoystickY();

	float GetLeftTrigger();
	float GetRightTrigger();

	bool GetButtonLeft();
	bool GetButtonRight();
	bool GetButtonA();
	bool GetButtonB();
	bool GetButtonX();
	bool GetButtonY();
	bool GetButtonBack();
	bool GetButtonStart();
	bool GetLeftBumper();
	bool GetRightBumper();

private:

	frc::Joystick* _driverJoystick;
	frc::Joystick* _driverJoystick2;
	CrabDrive* _crabDrive;
};

// ==========================================================================
