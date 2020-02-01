#pragma once
#include "controllers/VelocityMultiController.h"
#include "Modules/SwerveModuleInterface.h"
#include "frc/AnalogInput.h"
#include <string>
#include <ctre/Phoenix.h>

class TalonFXDiffSwerveModule : public SwerveModuleInterface {
public:

	TalonFXDiffSwerveModule(int masterid, int slaveid, std::string configName, CANCoder* headingSensor);
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
	TalonFX _master; // speed controller for the drive motor
	TalonFX _slave; // speed controller for the steer motor
	CANCoder* _headingSensor;

	double _voltageMin = .3;
	double _voltageMax = 4.5;


     void SetPercentPower(double value) ;
     double GetEncoderPosition() ;
     void SetVelocity(double value) ;
     void ConfigMotors() ;

};
