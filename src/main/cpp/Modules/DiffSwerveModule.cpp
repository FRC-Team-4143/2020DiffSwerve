#include "modules/DiffSwerveModule.h"
#include "subsystems/EncoderConstants.h"
#include "modules/Constants.h"
#include <frc/Preferences.h>
#include <iostream>

DiffSwerveModule::DiffSwerveModule(VelocityMultiController* master, VelocityMultiController* slave, std::string configName, frc::AnalogInput* headingSensor) {
	_master = master;
	_slave = slave;
	_configName = configName;
	_headingSensor = headingSensor;
	_lastPow = 0;
	LOG("DiffSwerveModule construct");
}

// ================================================================

void DiffSwerveModule::SetGeometry(double x, double y, double maxradius) {
	_x = x;
	_y = y;
	_radius = maxradius;
}

// ================================================================

double DiffSwerveModule::GetSteerPosition() {
	float voltage = _headingSensor->GetVoltage();
	if(voltage > .1 && voltage < _voltageMin) _voltageMin = voltage;
    if(voltage < 4.9 && voltage > _voltageMax) _voltageMax = voltage;
    double voltageWidth = _voltageMax - _voltageMin;
	voltage = (voltage - _voltageMin) / voltageWidth;  // scale to full 0-5v range
    return voltage * EncoderConstants::FULL_TURN;
}

// ================================================================

void DiffSwerveModule::SetWheelOffset() {
	_steerPosition = GetSteerPosition();
	auto prefs = frc::Preferences::GetInstance();
	prefs->PutDouble(_configName, _steerPosition);
	SetOffset(_steerPosition);
}

// ================================================================

void DiffSwerveModule::SetOffset(float off) {
	_offset = off;
}

// ================================================================

void DiffSwerveModule::LoadWheelOffset() {
	LOG("DiffSwerveModule: LoadWheelOffsets");
	auto prefs = frc::Preferences::GetInstance();
	_steerPosition = prefs->GetDouble(_configName);
	SetOffset(_steerPosition);
}

double DiffSwerveModule::GetSetpoint() { return _setpoint; }
double DiffSwerveModule::GetPower() { return _lastPow; }

// ================================================================

void DiffSwerveModule::SetDriveSpeed(float speed) {
	_lastPow = speed;

    double turn = GetSteerPosition() - _setpoint;
	//if(turn > EncoderConstants::HALF_TURN) turn -= EncoderConstants::FULL_TURN; 
    //if(turn < -EncoderConstants::HALF_TURN) turn += EncoderConstants::FULL_TURN;

	if(fabs(turn) < .02) 
		turn = 0;
	else
	    turn *= 1.0/2.5*1000;  // simple gain on steering error  - TODO: improve

	_master->SetVelocity((speed * _inverse * 5000) - turn);
	_slave->SetVelocity(-(speed * _inverse * 5000) - turn);

}

// ================================================================

double DiffSwerveModule::SetSteerDrive(double x, double y, double twist, bool operatorControl) {
	static constexpr double pi = 3.141592653589793238462643383;

	//auto signX = (_x >= 0) ? 1 : -1;
	//auto signY = (_y >= 0) ? 1 : -1;

	auto BP = x + twist * (_x) / _radius;
	auto CP = y - twist * (_y) / _radius;

	float setpoint = EncoderConstants::HALF_TURN;

	if (BP != 0 || CP != 0) {
		setpoint = (EncoderConstants::HALF_TURN + EncoderConstants::HALF_TURN / pi * atan2(BP, CP));
	}

	setpoint = -setpoint;
	SetSteerSetpoint(setpoint + _offset);

	auto power = sqrt(pow(BP, 2) + pow(CP, 2));

	if (operatorControl && fabs(x) <= Constants::DEAD_ZONE && fabs(y) <= Constants::DEAD_ZONE && fabs(twist) <= Constants::DEAD_ZONE) {
		power = 0;
	}
/*
	if (signX == signY){
		power = -power;
	}
	if (signX == -1) power = -power;
*/
	return power;
}

// ================================================================

void DiffSwerveModule::SetSteerSetpoint(float setpoint) {
	float currentPosition = GetSteerPosition() / EncoderConstants::COUNTS_PER_TURN;
	int turns = trunc(currentPosition);
	float currentAngle = currentPosition - turns;

	currentPosition *= EncoderConstants::FULL_TURN;
	turns *= EncoderConstants::FULL_TURN;
	currentAngle *= EncoderConstants::FULL_TURN;

	float angleOptions[6];
	angleOptions[0] = turns - EncoderConstants::FULL_TURN + setpoint;
	angleOptions[1] = turns - EncoderConstants::FULL_TURN + setpoint + EncoderConstants::HALF_TURN;
	angleOptions[2] = turns + setpoint;
	angleOptions[3] = turns + setpoint + EncoderConstants::HALF_TURN;
	angleOptions[4] = turns + EncoderConstants::FULL_TURN + setpoint;
	angleOptions[5] = turns + EncoderConstants::FULL_TURN + setpoint + EncoderConstants::HALF_TURN;

	int firstoption = 0;
	int optionincr = 1;

    // this prevents motors from having to reverse
	// if they are already rotating
	// they may take a longer rotation but will keep spinning the same way
	if(_lastPow > .3) {  // maybe should read speed instead of last power
		optionincr = 2;
		if(_inverse == -1)
			firstoption = 1;
	}

	float minMove = 360*5; //impossibly big angle
	int minI = 0;
	for (int i = firstoption; i < 6; i+=optionincr){
		if (fabs(currentPosition - angleOptions[i]) < minMove){
			minMove = fabs(currentPosition - angleOptions[i]);
			minI = i;
		}
	}

	_setpoint = angleOptions[minI];

	if (minI % 2)
		_inverse = -1;
	else
		_inverse = 1;
}