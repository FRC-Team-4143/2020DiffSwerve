#include <iostream>
#include "controllers/VelocityTalonFXController.h"

//#define BOTTOMLIMIT 1

struct Gains {
		double kP;
		double kI;
		double kD;
		double kF;
		double kIzone;
		double kPeakOutput;
};
constexpr static Gains kGains_Velocit = { 0.2, 0.0, 0.0, 0.05,  300,  0.50 };
const static int kSlot_Velocit = 2;
const static int kTimeoutMs = 30;
//kFF 0.000156
#define kMINOUTPUT -1
#define kMAXOUTPUT 1
#define ENCODER_COUNTS_PER_TURN 2048
//VelocitySparkController::VelocitySparkController(rev::CANSparkMax* motor) : _pidController(motor->GetPIDController()), _encoder(motor->GetEncoder()){
//    _motor = motor;
//	ConfigPID();
//}
VelocityTalonFxController::VelocityTalonFxController(int canId)
    : _motor{canId}
	, _encoder(_motor.GetIntegratedSensor())
{
	ConfigPID();
}
void VelocityTalonFxController::SetPercentPower(double value){
}
double VelocityTalonFxController::GetEncoderPosition(){
    return _encoder.GetVelocity();
}
void VelocityTalonFxController::SetVelocity(double value){
	_motor.Set(ControlMode:: Velocity, value);
	// GetY()*2048*10 (maybe)
}
void VelocityTalonFxController::ConfigPID(){
	_motor.RestoreFactoryDefaults();
	_motor.Config_kP(kSlot_Velocit, kGains_Velocit.kP, kTimeoutMs);
	_motor.Config_kI(kSlot_Velocit, kGains_Velocit.kI, kTimeoutMs);
	_motor.Config_kD(kSlot_Velocit, kGains_Velocit.kD, kTimeoutMs);
	_motor.Config_kF(kSlot_Velocit, kGains_Velocit.kF, kTimeoutMs);
	_motor.Config_IntegralZone(kSlot_Velocit, kGains_Velocit.kIzone, kTimeoutMs);
	_motor.ConfigClosedLoopPeakOutput(kSlot_Velocit,kGains_Velocit.kPeakOutput,kTimeoutMs);
}