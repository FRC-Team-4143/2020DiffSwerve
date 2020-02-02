#pragma once
#include "Modules/SwerveModuleInterface.h"
#include "controllers/PositionMultiController.h"
#include <string>

class SwerveModule : public SwerveModuleInterface {
public:

	SwerveModule(MultiController* drive, PositionMultiController* steer, std::string configName);

	// SwerveModuleInterface methods
	virtual void SetGeometry(double x, double y, double maxradius) override;
	virtual void SetWheelOffset() override;
	virtual void LoadWheelOffset() override;
	virtual void SetDriveSpeed(float speed) override;
	virtual double GetSteerPosition();
	virtual double SetSteerDrive(double x, double y, double twist, bool operatorControl) override;
	virtual double GetSetpoint() override;
	virtual double GetPower() override;

private:

	MultiController* _drive; // speed controller for the drive motor
	PositionMultiController* _steer; // speed controller for the steer motor
	std::string _configName;
	double _x;
	double _y;
	double _radius;
	double _setpoint;
	double _offset;
	double _lastPow;
	int _inverse;

	static bool InDeadZone(double value);

	void SetOffset(float offset);
	void SetSteerSetpoint(float setpoint);
};
