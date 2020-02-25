#pragma once
#include <frc/commands/Command.h>

// ==========================================================================

class WinchActive : public frc::Command {
public:

	WinchActive();

	int counter = 0;

	// Command methods
	virtual void Initialize() override;
	virtual void Execute() override;
	virtual bool IsFinished() override;
	virtual void End() override;
	virtual void Interrupted() override;
};

// ==========================================================================
