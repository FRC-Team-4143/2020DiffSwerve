#include "Modules/ScriptEngine.h"
#include "Modules/ScriptCommandFactory.h"
#include "Modules/CommandListParser.h"
#include "Modules/Logger.h"

#include "commands/ScriptDriveCrab.h"
#include "commands/ScriptDriveFieldCentric.h"
#include "commands/ScriptSleep.h"

#include <frc/smartdashboard/SmartDashboard.h>

// ==========================================================================

ScriptEngine::ScriptEngine()
:	_initialized(false) {
}

// ==========================================================================

ScriptEngine& ScriptEngine::GetInstance() {
	static ScriptEngine instance;
	return instance;
}

// ==========================================================================

void ScriptEngine::Initialize() {
	if (!_initialized) {
		_InitializeDashboard();
		_InitializeParser();
		_initialized = true;
	}
}

// ==========================================================================

frc::Command* ScriptEngine::GetCommand() {
return ScriptCommandFactory::GetInstance().GetCommand().release();
}

// ==========================================================================

void ScriptEngine::_InitializeDashboard() {
	frc::SmartDashboard::PutString("ScriptCommand", "S(1)");
	frc::SmartDashboard::PutString("ScriptValid", "");
}

// ==========================================================================

void ScriptEngine::_InitializeParser() {
	LOG("ScriptEngine::_InitializeParser");

	if (_initialized) {
		return;
	}
	_initialized = true;

	CommandListParser& parser(CommandListParser::GetInstance());

	parser.AddCommand(
		CommandParseInfo(
			"Drive", {"DC", "dc"},
			[](std::vector<float> parameters, std::function<void(frc::Command*, float)> fCreateCommand) {
				parameters.resize(4);
				auto x = parameters[0];
				auto y = parameters[1];
				auto z = parameters[2];
				auto seconds = parameters[3];
				frc::Command* command = new ScriptDriveCrab("DriveCrab", x, y, z, seconds);
				fCreateCommand(command, 0);
			}
		)
	);

	parser.AddCommand(
		CommandParseInfo(
			"DriveFieldCentric", {"DF", "df"},
			[](std::vector<float> parameters, std::function<void(frc::Command*, float)> fCreateCommand) {
				parameters.resize(4);
				auto x = parameters[0];
				auto y = parameters[1];
				auto z = parameters[2];
				auto seconds = parameters[3];
				frc::Command* command = new ScriptDriveFieldCentric("DriveFieldCentric", x, y, z, seconds);
				fCreateCommand(command, 0);
			}
		)
	);

	parser.AddCommand(
		CommandParseInfo(
			"Sleep", {"S", "s"},
			[](std::vector<float> parameters, std::function<void(frc::Command*, float)> fCreateCommand) {
				parameters.resize(1);
				auto seconds = parameters[0];
				frc::Command* command = new ScriptSleep("Sleep", seconds);
				fCreateCommand(command, 0);
			}
		)
	);

	// Call IsValid to ensure that regular expressions
	// get built before the start of autonomous.
	parser.IsValid("S(0)");
}

// ==========================================================================
