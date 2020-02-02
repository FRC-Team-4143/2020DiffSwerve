#pragma once
#include "Modules/SwerveModuleInterface.h"
#include "controllers/VelocityMultiController.h"
#include "frc/AnalogInput.h"
#include <string>

class DiffSwerveModule : public SwerveModuleInterface {
public:

	DiffSwerveModule(VelocityMultiController* master, VelocityMultiController* slave, std::string configName, frc::AnalogInput* headingSensor);

	void SetGeometry(double x, double y, double maxradius) override;
	void SetWheelOffset() override;
	void LoadWheelOffset() override;
	void SetDriveSpeed(float speed) override;
	double GetSteerPosition();
	double SetSteerDrive(double x, double y, double twist, bool operatorControl) override;
	double GetSetpoint();
	double GetPower();

private:

	VelocityMultiController* _master; // speed controller for the drive motor
	VelocityMultiController* _slave; // speed controller for the steer motor
	std::string _configName;
	frc::AnalogInput* _headingSensor;
	double _x;
	double _y;
	double _radius;
	double _setpoint;
	double _offset;
	double _lastPow;
	int _inverse = 1;

	double _voltageMin = .3;
	double _voltageMax = 4.5;

	static bool InDeadZone(double value);

	void SetOffset(float off);
	void SetSteerSetpoint(float setpoint);
};
