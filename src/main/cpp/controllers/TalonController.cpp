#include "controllers/TalonController.h"

TalonController::TalonController(WPI_TalonSRX* motor){
    _motor = motor;
}

TalonController::TalonController(int canId){
    _motor = new WPI_TalonSRX(canId);
}

void TalonController::SetPercentPower(double value){
    _motor->Set(ControlMode::PercentOutput, value);
}

double TalonController::GetEncoderPosition(){
    return _motor->GetSelectedSensorPosition();
}


