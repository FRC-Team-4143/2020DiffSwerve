#include "commands/EngageBrake.h"
#include "Robot.h"

// ==========================================================================

EngageBrake::EngageBrake()
:	frc::Command("Engage Brake") {
	Requires(Robot::climber.get());
}

// ==========================================================================

void EngageBrake::Initialize() {
}

// ==========================================================================

void EngageBrake::Execute() {
	Robot::climber->EngageBrake();
}

// ==========================================================================

bool EngageBrake::IsFinished() {
	return true;
}

// ==========================================================================

void EngageBrake::End() {
}

// ==========================================================================

void EngageBrake::Interrupted() {
	End();
}

// ==========================================================================