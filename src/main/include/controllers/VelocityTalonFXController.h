#pragma once
#include "controllers/IVelocityMultiController.h"
#include <ctre/Phoenix.h>
#include <memory>

// ================================================================

class VelocityTalonFXController : public IVelocityMultiController {
public:

	VelocityTalonFXController(int canId);

	// IVelocityMultiController methods
	virtual void SetPercentPower(double value) override;
	virtual double GetEncoderPosition() override;
	virtual void SetVelocity(double value) override;
	virtual void ConfigPID() override;
	
	std::unique_ptr<WPI_TalonFX> _motor;

private:

};

// ================================================================
