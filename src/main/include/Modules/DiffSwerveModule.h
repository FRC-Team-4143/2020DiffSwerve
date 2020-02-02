#pragma once
#include "Modules/SwerveModuleInterface.h"
#include "controllers/VelocityMultiController.h"
#include "frc/AnalogInput.h"
#include <string>

class DiffSwerveModule : public SwerveModuleInterface {
public:

	DiffSwerveModule(VelocityMultiController* master, VelocityMultiController* slave, std::string configName, frc::AnalogInput* headingSensor);

	// SwerveModuleInterface methods
	virtual void SetGeometry(double x, double y, double maxradius) override;
	virtual void SetWheelOffset() override;
	virtual void LoadWheelOffset() override;
	virtual void SetDriveSpeed(float speed) override;
	virtual double GetSteerPosition() override;
	virtual double SetSteerDrive(double x, double y, double twist, bool operatorControl) override;
	virtual double GetSetpoint() override;
	virtual double GetPower() override;

private:

	VelocityMultiController* _master; // speed controller for the drive motor
	VelocityMultiController* _slave; // speed controller for the steer motor
	std::string _configName;
	frc::AnalogInput* _headingSensor;

	double _x;
	double _y;
	double _radius;
	double _offset;
	double _setpoint;
	double _lastPow;
	int _inverse;

	double _voltageMin = .3;
	double _voltageMax = 4.5;

	static bool InDeadZone(double value);

	void SetOffset(float offset);
	void SetSteerSetpoint(float setpoint);
};
