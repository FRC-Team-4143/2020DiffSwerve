#include "subsystems/DriveTrain.h"
#include "Modules/Constants.h"
#include "Modules/Logger.h"
#include "Robot.h"
#include "commands/CrabDrive.h"
#include "commands/FieldCentric.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <algorithm>
#include <cmath>

//const float DEAD_ZONE = 0.15;

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain") {
	frontLeftModule = Robot::frontLeftModule;
	frontRightModule = Robot::frontRightModule;
	rearLeftModule = Robot::rearLeftModule;
	rearRightModule = Robot::rearRightModule;

	SetWheelbase(14, 14);
	yaw = 0;
	joystickAngle = 0;
	fieldCentricMode = false;
}

// ================================================================

void DriveTrain::InitDefaultCommand() {
	//SetDefaultCommand(new FieldCentric());
	SetDefaultCommand(new CrabDrive());
}

// ================================================================

void DriveTrain::SetWheelbase(double width, double length, double xOffset, double yOffset) {
	if (width != 0 || length != 0) {
		X = width;
		Y = length;
	}

	double halfWidth = X / 2;
	double halfLength = Y / 2;

	auto maxradius = std::sqrt(pow(halfWidth + fabs(xOffset), 2) + pow(halfLength + fabs(yOffset), 2));

	frontLeftModule->SetGeometry(halfWidth - xOffset, -halfLength - yOffset, maxradius);
	frontRightModule->SetGeometry(halfWidth - xOffset, halfLength - yOffset, maxradius);
	rearLeftModule->SetGeometry(-halfWidth - xOffset, -halfLength - yOffset, maxradius);
	rearRightModule->SetGeometry(-halfWidth - xOffset, halfLength - yOffset, maxradius);
}

// ================================================================

void DriveTrain::SetWheelOffsets() {
	frontLeftModule->SetWheelOffset();
	frontRightModule->SetWheelOffset();
	rearLeftModule->SetWheelOffset();
	rearRightModule->SetWheelOffset();
}

// ================================================================

void DriveTrain::LoadWheelOffsets() {
	frontLeftModule->LoadWheelOffset();
	frontRightModule->LoadWheelOffset();
	rearLeftModule->LoadWheelOffset();
	rearRightModule->LoadWheelOffset();
}

// ================================================================

void DriveTrain::Crab(float twist, float y, float x, bool operatorControl) {
	if (operatorControl && x == 0.0 && y == 0.0 && twist == 0.0 && false) {
		if (fabs(lasty) > 0 || fabs(lastx) > 0 || fabs(lasttwist) > 0) {
			y = std::min(std::max(lasty, -Constants::DEAD_ZONE), Constants::DEAD_ZONE);
			x = std::min(std::max(lastx, -Constants::DEAD_ZONE), Constants::DEAD_ZONE);
			twist = std::min(std::max(lasttwist, -Constants::DEAD_ZONE), Constants::DEAD_ZONE);
		}
		else {
			y = .05;
			//default wheel position
		}
	}
	else {
		lastx = x;
		lasty = y;
		lasttwist = twist;
	}

	x *= 0.25;
	y *= 0.25;
	twist *= 0.25;

	//if (operatorControl && !Robot::oi->GetLeftBumper()) { // Increase spin speed
	//	twist *= 0.65;
		// scale for operator control
	//	x *= 1;
	//	y *= 1;
	//	float avg = (abs(x) + abs(y)) / 2;
	//	float scale = 1 - avg / 2;
	//	twist *= scale; // TWISTSCALE;
	//}

	auto leftTrigger = Robot::oi->GetLeftTrigger();
	auto rightTrigger = Robot::oi->GetRightTrigger();

	if (leftTrigger > 0 || rightTrigger > 0) { // turbo mode
		x *= 2.0;
		y *= 2.0;
	}

/*
	if (false && leftTrigger > 0 || rightTrigger > 0) { // Spin from corner

		 x = 0;
		 y = 0;

		double pivotAngle = 0;
		if (yaw == 0) {
			yaw = Robot::navx->GetYaw();
			joystickAngle = atan2(Robot::oi->GetJoystickX(), -Robot::oi->GetJoystickY()) * 180/pi ;
			SmartDashboard::PutNumber("JoystickAngle", joystickAngle);
		}

		if (joystickAngle > -90 && joystickAngle < 90) {
			if (rightTrigger) {
				pivotAngle = joystickAngle + 45;
				twist = -1;
			}
			else {
				pivotAngle = joystickAngle - 45;
				twist = 1;
			}
		}
		else {
			if (leftTrigger) {
				pivotAngle = joystickAngle + 45;
				twist = -1;
			}
			else {
				pivotAngle = joystickAngle - 45;
				twist = 1;
			}
		}
		pivotAngle -= yaw;

		SetWheelbase(0, 0, cos(pivotAngle * pi / 180) * 20, sin(pivotAngle * pi / 180) * 20);
	}
	else {
		yaw = 0;
		joystickAngle = 0;

		//if (Mode::IsHatchMode()) {
		//	if (fieldCentricMode) {
		//		SetWheelbase(0, 0, 20, 0); //center of hatch panel
		//	}
		//	else {
		//		SetWheelbase(0, 0, 10, 0); // center of camera
		//	}
		//}
		//else {
			SetWheelbase(0, 0, 0, 0); // center of robot
		//}
	}
	*/

	//if (Robot::oi->GetButtonRight()) {
	//	y = 0;
	//	x = 0;
	//	twist = GyroRotate();
	//	twist = std::min(0.18, std::max(-0.18, twist * 0.025));
	//}

	double speeds[4];

	speeds[0] = frontLeftModule->SetSteerDrive(x, y, twist, operatorControl);
	speeds[1] = frontRightModule->SetSteerDrive(x, y, twist, operatorControl);
	speeds[2] = rearLeftModule->SetSteerDrive(x, y, twist, operatorControl);
	speeds[3] = rearRightModule->SetSteerDrive(x, y, twist, operatorControl);

	double maxspeed = *std::max_element(speeds, speeds + 4);

	if (maxspeed > 1) {
		frontLeftModule->SetDriveSpeed(speeds[0]/maxspeed);
		frontRightModule->SetDriveSpeed(speeds[1]/maxspeed);
		rearLeftModule->SetDriveSpeed(speeds[2]/maxspeed);
		rearRightModule->SetDriveSpeed(speeds[3]/maxspeed);
	}
	else {
		frontLeftModule->SetDriveSpeed(speeds[0]);
		frontRightModule->SetDriveSpeed(speeds[1]);
		rearLeftModule->SetDriveSpeed(speeds[2]);
		rearRightModule->SetDriveSpeed(speeds[3]);
	}

	frc::SmartDashboard::PutNumber("FL Speed", speeds[0]);
	frc::SmartDashboard::PutNumber("FR Speed", speeds[1]);
	frc::SmartDashboard::PutNumber("RL Speed", speeds[2]);
	frc::SmartDashboard::PutNumber("RR Speed", speeds[3]);

	fieldCentricMode = false;
}

// ================================================================

void DriveTrain::FieldCentricCrab(float twist, float y, float x, bool operatorControl) {
	fieldCentricMode = true;

	float FWD = y;
	float STR = x;

	auto robotangle = Robot::gyroSub->PIDGet() * pi / 180;

	FWD = y * cos(robotangle) + x * sin(robotangle);
	STR = -y * sin(robotangle) + x * cos(robotangle);

	Crab((twist), FWD, STR, operatorControl); // twist * 0.65
}

// ================================================================

double DriveTrain::GyroRotate() {
	auto yaw = Robot::gyroSub->PIDGet();
	float desiredangle = 0;

	if (yaw > 45 && yaw < 135) {
		desiredangle = 90;
	}
	else if ((yaw > 135 && yaw < 179) || (yaw < -135 && yaw > -179)) {
		desiredangle = 180;
	}
	else if (yaw > -135 && yaw < -45) {
		desiredangle = -90;
	}
	else if (yaw < 45 && yaw > -45) {
		desiredangle = 0;
	}

	float twist = desiredangle - yaw;
	while (twist > 180.0) {
		twist -= 360.0;
	}
	while (twist < -180.0) {
		twist += 360.0;
	}

	return twist;
}

// ================================================================

double DriveTrain::GetNearestHeading() {
	auto yaw = Robot::gyroSub->PIDGet();
	auto currentheading = 0;

	if (yaw > 45 && yaw <= 135) {
		currentheading = 90;
	}
	else if ((yaw > 135 && yaw <= 180) || (yaw < -135 && yaw >= -180)) {
		currentheading = 180;
	}
	else if (yaw > -135 && yaw <= -45) {
		currentheading = -90;
	}
	else if (yaw < 45 && yaw >= -45) {
		currentheading = 0;
	}

	return currentheading;
}

// ================================================================

void DriveTrain::RotateAboutPoint(double currentheading) {
	if (currentheading == 0) {
		if (Robot::oi->GetJoystickZ() > 0) {
			Robot::driveTrain->SetWheelbase(0, 0, 14, -14);
		}
		else {
			Robot::driveTrain->SetWheelbase(0, 0, 14, 14);
		}
	}
	else if (currentheading == 90) {
		if (Robot::oi->GetJoystickZ() > 0) {
			Robot::driveTrain->SetWheelbase(0, 0, -14, -14);
		}
		else {
			Robot::driveTrain->SetWheelbase(0, 0, 14, -14);
		}
	}
	else if (currentheading == 180) {
		if (Robot::oi->GetJoystickZ() > 0) {
			Robot::driveTrain->SetWheelbase(0, 0, -14, 14);
		}
		else {
			Robot::driveTrain->SetWheelbase(0, 0, -14, -14);
		}
	}
	else {
		if (Robot::oi->GetJoystickZ() > 0) {
			Robot::driveTrain->SetWheelbase(0, 0, 14, 14);
		}
		else {
			Robot::driveTrain->SetWheelbase(0, 0, -14, 14);
		}
	}
}

// ================================================================
