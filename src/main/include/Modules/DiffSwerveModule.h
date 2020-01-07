#pragma once
#include "controllers/VelocityMultiController.h"
#include "Modules/SwerveModuleInterface.h"
#include "frc/AnalogInput.h"
#include <string>

class DiffSwerveModule : public SwerveModuleInterface {
public:

	DiffSwerveModule(VelocityMultiController* master, VelocityMultiController* slave, std::string configName, frc::AnalogInput* headingSensor);
	double GetSteerPosition();
	void SetGeometry(double x, double y, double maxradius) override;
	void SetWheelOffset() override;
	void SetOffset(float off);
	void LoadWheelOffset() override;
	void SetDriveSpeed(float speed) override;
	double SetSteerDrive(double x, double y, double twist, bool operatorControl) override;
	void SetSteerSetpoint(float setpoint);
	double GetSetpoint();
	double GetPower();

private:

	double _setpoint;
	double _offset;
	double _x;
	double _y;
	double _radius;
	std::string _configName;
	double _steerPosition;
	double _lastPow;

	int _inverse = 1;
	VelocityMultiController* _master; // speed controller for the drive motor
	VelocityMultiController* _slave; // speed controller for the steer motor
	frc::AnalogInput* _headingSensor;

	double _voltageMin = .3;
	double _voltageMax = 4.5;

};
