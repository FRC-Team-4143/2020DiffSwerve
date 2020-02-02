#pragma once
#include "controllers/MultiController.h"
#include <ctre/Phoenix.h>

class TalonController : public MultiController {
public:

	TalonController(WPI_TalonSRX* motor);
	TalonController(int canId);

	// MultiController methods
	virtual void SetPercentPower(double value) override;
	virtual double GetEncoderPosition() override;

private:

	WPI_TalonSRX* _motor;
};
