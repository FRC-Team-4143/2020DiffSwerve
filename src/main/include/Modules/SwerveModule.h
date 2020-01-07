#pragma once
#include "controllers/PositionMultiController.h"
#include "Modules/SwerveModuleInterface.h"
#include <string>

class SwerveModule : public SwerveModuleInterface {
public:

	SwerveModule(MultiController* drive, PositionMultiController* steer, std::string configName);
	double GetSteerPosition();
	void SetGeometry(double x, double y, double maxradius) override;
	void SetWheelOffset() override;
	void SetOffset(float off);
	void LoadWheelOffset() override;
	void SetDriveSpeed(float speed) override;
	double SetSteerDrive(double x, double y, double twist, bool operatorControl) override;
	void SetSteerSetpoint(float setpoint);

private:

	double _offset;
	double _x;
	double _y;
	double _radius;
	std::string _configName;
	double _steerPosition;
	double _lastPow;
	int _inverse = 1;
	MultiController* _drive; // speed controller for the drive motor
	PositionMultiController* _steer; // speed controller for the steer motor
};
