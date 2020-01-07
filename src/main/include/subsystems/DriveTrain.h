#pragma once

#include <frc/commands/Subsystem.h>
#include "modules/SwerveModule.h"
#include "Modules/DiffSwerveModule.h"
#include "EncoderConstants.h"



class DriveTrain : public frc::Subsystem {
 public:

  DriveTrain();
  void InitDefaultCommand() override;
  void SetWheelbase(double width, double length, double xOffset = 0, double yOffset = 0);
  void SetWheelOffsets();
  void LoadWheelOffsets();
  void Crab(float twist, float y, float x, bool operatorControl);
  void FieldCentricCrab(float twist, float y, float x, bool operatorControl);
  double GyroRotate();
  double GetNearestHeading();
  void RotateAboutPoint(double currentheading);


 private:

  static constexpr double pi = 3.141592653589793238462643383;

  double X;
  double Y; 

  double yaw;
  double joystickAngle;

  bool fieldCentricMode;
  
	float lastx;
	float lasty;
	float lasttwist;

    SwerveModuleInterface* frontLeftModule;
    SwerveModuleInterface* frontRightModule;
    SwerveModuleInterface* rearLeftModule;
    SwerveModuleInterface* rearRightModule;
  };
