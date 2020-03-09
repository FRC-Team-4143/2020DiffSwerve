#include "commands/ScriptStirForward.h"
#include "Modules/Logger.h"
#include "Robot.h"

// ==========================================================================

ScriptStirForward::ScriptStirForward(float seconds)
:	frc::Command("ScriptStirForward"), _seconds(seconds) {
	char szParams[64];
	sprintf(szParams, "(%f)", seconds);
	LOG(GetName() + "::ctor" + szParams);

	// ----------------------------------------------------
	// Do NOT require the Shooter subsystem. Otherwise, we
	// cannot do parallel Shooter-related script commands.
	// ----------------------------------------------------
	//Requires(Robot::shooter.get());
}

// ==========================================================================

void ScriptStirForward::Initialize() {
	LOG(GetName() + "::Initialize");

	SetTimeout(_seconds);

}

// ==========================================================================

void ScriptStirForward::Execute() {
	Robot::shooter->Stir();
	Robot::shooter->Feed(1);
	Robot::shooter->ShootStart();
}

// ==========================================================================

bool ScriptStirForward::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================

void ScriptStirForward::End() {
	LOG(GetName() + "::End");
	Robot::shooter->StirStop();
	Robot::shooter->FeedStop();
}

// ==========================================================================

void ScriptStirForward::Interrupted() {
	LOG(GetName() + "::Interrupted");
}

// ==========================================================================
