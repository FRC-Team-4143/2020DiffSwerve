#pragma once
#include "controllers/VelocityMultiController.h"
#include <rev/CANSparkMax.h>

class VelocitySparkController : public VelocityMultiController  {
public:
    //VelocitySparkController(rev::CANSparkMax* motor);
    VelocitySparkController(int canId);
    virtual void SetPercentPower(double value) override;
    virtual double GetEncoderPosition() override;
    virtual void SetVelocity(double value) override;
    virtual void ConfigPID() override;

private:
    double kMaxVel;
    double kMinVel;
    double kMaxAcc;
    double kAllErr;
    rev::CANSparkMax _motor;
    rev::CANPIDController _pidController;
    rev::CANEncoder _encoder;
};
