#pragma once
#include "controllers/MultiController.h"
#include <ctre/Phoenix.h>

class VictorController : public MultiController  {
public:
    VictorController(WPI_VictorSPX* motor);
    VictorController(int canId);
    virtual void SetPercentPower(double value) override;
    virtual double GetEncoderPosition() override;
    

private:
    WPI_VictorSPX* _motor;
};
