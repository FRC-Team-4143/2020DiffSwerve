#pragma once
#include <frc/Joystick.h>
#include "commands/CrabDrive.h"

// ==========================================================================

class OI {
public:

	OI();

	float GetJoystickX();
	float GetJoystickY();
	float GetJoystickZ();
	float GetJoystick2X();
	float GetJoystick2Y();
	float GetJoystick2Z();

	float GetRightJoystickY();

	float GetLeftTrigger();
	float GetRightTrigger();
	float GetLeftTrigger2();
	float GetRightTrigger2();

	bool GetButtonLeft();
	bool GetButtonRight();
	bool GetButtonA();
	bool GetButtonB();
	bool GetButtonA2();
	bool GetButtonB2();
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
