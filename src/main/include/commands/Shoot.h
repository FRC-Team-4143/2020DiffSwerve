#pragma once
#include <frc/commands/Command.h>

// ==========================================================================

class Shoot : public frc::Command {
public:
    int counter;
	Shoot();

	// Command methods
	virtual void Initialize() override;
	virtual void Execute() override;
	virtual bool IsFinished() override;
	virtual void End() override;
	virtual void Interrupted() override;
};

// ==========================================================================
