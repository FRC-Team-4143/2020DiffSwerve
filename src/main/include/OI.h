#pragma once
#include <frc/Joystick.h>
#include "commands/SetWheelOffsets.h"
#include "commands/CrabDrive.h"
#include "commands/ZeroYaw.h"

using namespace frc;

class OI {
 public: 

  Joystick* driverjoystick;
  CrabDrive* crabDrive;

//======= OI Methods =======//
  OI();
  float GetJoystickX();
  float GetJoystickY();
  float GetJoystickZ();
  float GetRightJoystickY();
  float GetLeftTrigger();
  float GetRightTrigger();
  bool GetButtonLeft();
  bool GetButtonRight();
  bool GetButtonB();
  bool GetButtonX();
  bool GetButtonA();
  bool GetButtonY();
  bool GetButtonBack();
  bool GetButtonStart();
  bool GetRightBumper();
  bool GetLeftBumper();
};
