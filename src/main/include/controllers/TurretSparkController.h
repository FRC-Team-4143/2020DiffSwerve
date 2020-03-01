#pragma once
#include "controllers/IPositionMultiController.h"
#include <rev/CANSparkMax.h>

class TurretSparkController : public IPositionMultiController {
public:

	TurretSparkController(rev::CANSparkMax* motor);
	TurretSparkController(int canId);

	// IPositionMultiController methods
	virtual void SetPercentPower(double value) override;
	virtual double GetEncoderPosition() override;
	virtual void SetPosition(double value) override;
	virtual void ConfigPID() override;

private:

	double kMaxVel;
	double kMinVel;
	double kMaxAcc;
	double kAllErr;
	rev::CANSparkMax* _motor;
	//rev::CANPIDController _pidController;
};
