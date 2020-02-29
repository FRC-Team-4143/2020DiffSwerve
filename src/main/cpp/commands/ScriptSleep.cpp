#include "commands/ScriptSleep.h"
#include "Modules/Logger.h"

// ==========================================================================

ScriptSleep::ScriptSleep(std::string name, float seconds)
:	frc::Command(name), _seconds(seconds) {
	char szParams[64];
	sprintf(szParams, "(%f)", seconds);
	LOG(GetName() + "::ctor" + szParams);
}

// ==========================================================================

void ScriptSleep::Initialize() {
	LOG(GetName() + "::Initialize");

	SetTimeout(_seconds);
}

// ==========================================================================

void ScriptSleep::Execute() {
}

// ==========================================================================

bool ScriptSleep::IsFinished() {
	return IsTimedOut();
}

// ==========================================================================

void ScriptSleep::End() {
	LOG(GetName() + "::End");
}

// ==========================================================================

void ScriptSleep::Interrupted() {
	LOG(GetName() + "::Interrupted");
}

// ==========================================================================
