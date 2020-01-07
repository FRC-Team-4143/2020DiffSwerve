#pragma once
#include <ctre/Phoenix.h>
#include "controllers/MultiController.h"

class TalonController : public MultiController  {
public:
    TalonController(WPI_TalonSRX* motor);
    TalonController(int canId);
    virtual void SetPercentPower(double value) override;
    virtual double GetEncoderPosition() override;

private:
    WPI_TalonSRX* _motor;
};
