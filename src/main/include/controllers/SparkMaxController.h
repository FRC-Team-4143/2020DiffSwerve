#pragma once
#include "controllers/MultiController.h"
#include <rev/CANSparkMax.h>

class SparkMaxController : public MultiController {
public:

	SparkMaxController(rev::CANSparkMax* motor);
	SparkMaxController(int canId);

	// MultiController methods
	virtual void SetPercentPower(double value) override;
	virtual double GetEncoderPosition() override;

private:

	rev::CANSparkMax* _motor;
};
