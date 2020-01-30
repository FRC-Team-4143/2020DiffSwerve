#pragma once
#include "controllers/VelocityMultiController.h"
#include <ctre/Phoenix.h>

class VelocityTalonFxController : public VelocityMultiController  {
public:
    //VelocityTalonFxController(rev::CANSparkMax* motor);
    VelocityTalonFxController(int canId);
    virtual void SetPercentPower(double value) override;
    virtual double GetEncoderPosition() override;
    virtual void SetVelocity(double value) override;
    virtual void ConfigPID() override;

private:
    TalonFX _motor;
    CANEncoder _encoder;
};