#pragma once
#include <frc/commands/Command.h>

// ==========================================================================

class Shoot : public frc::Command {
public:

	Shoot();

	// Command methods
	virtual void Initialize() override;
	virtual void Execute() override;
	virtual bool IsFinished() override;
	virtual void End() override;
	virtual void Interrupted() override;

private:

	//int counter;
	bool _lastButton;
	//double targetPositionRotations;	/** save the target position to servo to */
	//float steering_adjust_last; //Steering adjust will stay at last value if target goes out of frame
	//float heading_error;
	//float steering_adjust;
	float adjust_speed; 
	float degrees = 0.;
	int countNav = 0;
};

// ==========================================================================
