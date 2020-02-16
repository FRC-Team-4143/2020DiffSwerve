#include "OI.h"
#include "commands/ExtendPickUp.h"
#include "commands/RetractPickUp.h"
#include "commands/ExtendClimber.h"
#include "commands/RetractClimber.h"
#include "commands/EngageBrake.h"
#include "commands/PickUpIntake.h"
#include "commands/PickUpRevIntake.h"
#include "commands/SetWheelOffsets.h"
#include "commands/ZeroYaw.h"
#include "Modules/Constants.h"
#include <frc/buttons/JoystickButton.h>
#include <frc/smartdashboard/SmartDashboard.h>

const uint32_t JOYSTICK_LX_AXIS = 0;
const uint32_t JOYSTICK_LY_AXIS = 1;
const uint32_t JOYSTICK_LTRIG_AXIS = 2;
const uint32_t JOYSTICK_RTRIG_AXIS = 3;
const uint32_t JOYSTICK_RX_AXIS = 4;
const uint32_t JOYSTICK_RY_AXIS = 5;

const uint32_t JOYSTICK_BUTTON_A = 1;
const uint32_t JOYSTICK_BUTTON_B = 2;
const uint32_t JOYSTICK_BUTTON_X = 3;
const uint32_t JOYSTICK_BUTTON_Y = 4;
const uint32_t JOYSTICK_BUTTON_LB = 5;
const uint32_t JOYSTICK_BUTTON_RB = 6;
const uint32_t JOYSTICK_BUTTON_BACK = 7;
const uint32_t JOYSTICK_BUTTON_START = 8;
const uint32_t JOYSTICK_BUTTON_LEFT = 9;
const uint32_t JOYSTICK_BUTTON_RIGHT = 10;

// ==========================================================================

OI::OI() {
	_driverJoystick = new frc::Joystick(0);
	_crabDrive = new CrabDrive();

	frc::SmartDashboard::PutData("Set WheelOffsets", new SetWheelOffsets());
	frc::SmartDashboard::PutData("Zero Yaw", new ZeroYaw());

	(new frc::JoystickButton(_driverJoystick, JOYSTICK_BUTTON_LEFT))->ToggleWhenPressed(_crabDrive);
	(new frc::JoystickButton(_driverJoystick, JOYSTICK_BUTTON_RB))->WhenPressed(new ExtendPickUp());
	(new frc::JoystickButton(_driverJoystick, JOYSTICK_BUTTON_LB))->WhenPressed(new RetractPickUp());
	(new frc::JoystickButton(_driverJoystick, JOYSTICK_BUTTON_X))->WhenPressed(new ExtendClimber());
	(new frc::JoystickButton(_driverJoystick, JOYSTICK_BUTTON_Y))->WhenPressed(new RetractClimber());
	(new frc::JoystickButton(_driverJoystick, JOYSTICK_BUTTON_BACK))->WhenPressed(new EngageBrake());
	(new frc::JoystickButton(_driverJoystick, JOYSTICK_BUTTON_A))->WhenPressed(new PickUpIntake());
	(new frc::JoystickButton(_driverJoystick, JOYSTICK_BUTTON_B))->WhenPressed(new PickUpRevIntake());

}

// ==========================================================================

float OI::GetJoystickX() {
	auto value = _driverJoystick->GetRawAxis(JOYSTICK_LX_AXIS);
	return (fabs(value) <= Constants::DEAD_ZONE) ? 0 : value;
}

// ==========================================================================

float OI::GetJoystickY() {
	auto value = _driverJoystick->GetRawAxis(JOYSTICK_LY_AXIS);
	return (fabs(value) <= Constants::DEAD_ZONE) ? 0 : value;
}

// ==========================================================================

float OI::GetJoystickZ() {
	auto value = _driverJoystick->GetRawAxis(JOYSTICK_RX_AXIS);
	return (fabs(value) <= Constants::DEAD_ZONE) ? 0 : value;
}

// ==========================================================================

float OI::GetRightJoystickY() {
	auto value = _driverJoystick->GetRawAxis(JOYSTICK_RY_AXIS);
	return (fabs(value) <= Constants::DEAD_ZONE) ? 0 : value;
}

// ==========================================================================

float OI::GetLeftTrigger() {
	float value = fabs(_driverJoystick->GetRawAxis(JOYSTICK_LTRIG_AXIS));
	return (value <= Constants::DEAD_ZONE) ? 0 : value;
}

// ==========================================================================

float OI::GetRightTrigger() {
	float value = fabs(_driverJoystick->GetRawAxis(JOYSTICK_RTRIG_AXIS));
	return (value <= Constants::DEAD_ZONE) ? 0 : value;
}

// ==========================================================================

bool OI::GetButtonLeft() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_LEFT);
}

// ==========================================================================

bool OI::GetButtonRight() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_RIGHT);
}

// ==========================================================================

bool OI::GetButtonA() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_A);
}

// ==========================================================================

bool OI::GetButtonB() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_B);
}

// ==========================================================================

bool OI::GetButtonX() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_X);
}

// ==========================================================================

bool OI::GetButtonY() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_Y);
}

// ==========================================================================

bool OI::GetButtonBack() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_BACK);
}

// ==========================================================================

bool OI::GetButtonStart() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_START);
}

// ==========================================================================

bool OI::GetLeftBumper() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_LB);
}

// ==========================================================================

bool OI::GetRightBumper() {
	return _driverJoystick->GetRawButton(JOYSTICK_BUTTON_RB);
}

// ==========================================================================
