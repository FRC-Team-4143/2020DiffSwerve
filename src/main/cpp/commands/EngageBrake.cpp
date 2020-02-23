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
	return false;
}

// ==========================================================================

void EngageBrake::End() {
	Robot::climber->ReleaseBrake();
}

// ==========================================================================

void EngageBrake::Interrupted() {
	End();
}

// ==========================================================================
