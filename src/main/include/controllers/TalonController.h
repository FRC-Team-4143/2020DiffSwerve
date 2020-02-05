#pragma once
#include "controllers/IMultiController.h"
#include <ctre/Phoenix.h>

class TalonController : public IMultiController {
public:

	TalonController(WPI_TalonSRX* motor);
	TalonController(int canId);

	// IMultiController methods
	virtual void SetPercentPower(double value) override;
	virtual double GetEncoderPosition() override;

private:

	WPI_TalonSRX* _motor;
};
