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
	//double target_RPM = joyForward * 1000; /* +- 500 RPM */
	//double target_unitsPer100ms = target_RPM * kSensorUnitsPerRotation / 600.0;
	//if(turn > EncoderConstants::HALF_TURN) turn -= EncoderConstants::FULL_TURN; 
    //if(turn < -EncoderConstants::HALF_TURN) turn += EncoderConstants::FULL_TURN;

	if(fabs(turn) < .02) 
		turn = 0;
	else
	    turn *= 1.0/2.5*1000;  // simple gain on steering error  - TODO: improve

	_master->SetVelocity((speed * _inverse * 5000) - turn);
	_slave->SetVelocity(-(speed * _inverse * 5000) - turn);
	//_target0 = target_unitsPer100ms;
	//_target1 = heading_units;
	//_master->Set(ControlMode::Velocity, _target0, DemandType_AuxPID, _target1);
	//_slave->Follow(*_talonRght, FollowerType::FollowerType_AuxOutput1);
	
	//ADDED FROM PHOENIX EXAMPLE
	/*
			double MaxCurrent = 10.0;

		SupplyCurrentLimitConfiguration supply (true,MaxCurrent,MaxCurrent,2);
    	StatorCurrentLimitConfiguration stator (true,MaxCurrent,MaxCurrent,2);
    	_talonRght->ConfigStatorCurrentLimit(stator);
    	_talonRght->ConfigSupplyCurrentLimit(supply);
		_talonLeft->ConfigStatorCurrentLimit(stator);
    	_talonLeft->ConfigSupplyCurrentLimit(supply);
		
	_talonRght->Set(ControlMode::Velocity, _target0, DemandType_AuxPID, _target1);
	_talonLeft->Follow(*_talonRght, FollowerType::FollowerType_AuxOutput1);
	_talonRght->SelectProfileSlot(kSlot_Velocit, PID_PRIMARY);
	_talonRght->SelectProfileSlot(kSlot_Turning, PID_TURN); 
	_talonRght->Config_kP(kSlot_Velocit, kGains_Velocit.kP, kTimeoutMs);
		_talonRght->Config_kI(kSlot_Velocit, kGains_Velocit.kI, kTimeoutMs);
		_talonRght->Config_kD(kSlot_Velocit, kGains_Velocit.kD, kTimeoutMs);
		_talonRght->Config_kF(kSlot_Velocit, kGains_Velocit.kF, kTimeoutMs);
		_talonRght->Config_IntegralZone(kSlot_Velocit, kGains_Velocit.kIzone, kTimeoutMs);
		_talonRght->ConfigClosedLoopPeakOutput(	kSlot_Velocit,
			kGains_Velocit.kPeakOutput,
	kTimeoutMs);

		_talonLeft->SetInverted(true);
		_talonLeft->SetSensorPhase(true);
		_talonRght->SetInverted(false); //Was True
		_talonRght->SetSensorPhase(true);
		_talonLeft->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder,
												PID_PRIMARY,
												kTimeoutMs);
		_talonRght->ConfigRemoteFeedbackFilter(	_talonLeft->GetDeviceID(),
												RemoteSensorSource::RemoteSensorSource_TalonSRX_SelectedSensor,
												REMOTE_0,
												kTimeoutMs);
		_talonRght->ConfigRemoteFeedbackFilter(	_talonPigeon->GetDeviceNumber(),
												RemoteSensorSource::RemoteSensorSource_CANCoder,
												REMOTE_1,
												kTimeoutMs);
	constexpr static Gains kGains_Distanc = { 0.1, 0.0,  0.0, 0.0,            100,  0.50 };
		constexpr static Gains kGains_Turning = { 0.1, 0.0,  0.0, 0.0,            200,  .25 };
		constexpr static Gains kGains_Velocit = { 0.2, 0.0, 0.0, 0.05,  300,  0.50 }; measured 6800 velocity units at full motor output
		constexpr static Gains kGains_MotProf = { 1.0, 0.0,  0.0, 1023.0/6800.0,  400,  1.00 };
			const static int kSensorUnitsPerRotation = 2048;
		constexpr static double kRotationsToTravel = 6;
		const int kHeadingSensorChoice = 1;
		const static int kEncoderUnitsPerRotation = 51711.0;
		const static int kPigeonUnitsPerRotation = 360.0;
			struct Gains {
		double kP;
		double kI;
		double kD;
		double kF;
		double kIzone;
		double kPeakOutput;
		const static int REMOTE_0 = 0;
		const static int REMOTE_1 = 1;
		const static int PID_PRIMARY = 0;
		const static int PID_TURN = 1;
		const static int SLOT_0 = 0;
		const static int SLOT_1 = 1;
		const static int SLOT_2 = 2;
		const static int SLOT_3 = 3;
	*/

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