#include "commands/ScriptShoot.h"
#include "Modules/Logger.h"
#include "Robot.h"

// ==========================================================================

ScriptShoot::ScriptShoot(float seconds)
:	frc::Command("ScriptShoot"), _seconds(seconds) {
	char szParams[64];
	sprintf(szParams, "(%f)", seconds);
	LOG(GetName() + "::ctor" + szParams);

	Requires(Robot::shooter.get());
}

// ==========================================================================

void ScriptShoot::Initialize() {
	LOG(GetName() + "::Initialize");
	SetTimeout(_seconds);

}

// ==========================================================================

void ScriptShoot::Execute() {
	Robot::shooter->Feed(0);
	Robot::shooter->ShootStart(14400);
	Robot::shooter->LimeLightControl(true);
}

// ==========================================================================

bool ScriptShoot::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================

void ScriptShoot::End() {
	LOG(GetName() + "::End");
	//Robot::shooter->ShootStop();
}

// ==========================================================================

void ScriptShoot::Interrupted() {
	LOG(GetName() + "::Interrupted");
}

// ==========================================================================
