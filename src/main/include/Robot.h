#pragma once
#include "controllers/IMultiController.h"
#include "controllers/IPositionMultiController.h"
#include "controllers/IVelocityMultiController.h"
#include "Modules/ISwerveModule.h"
#include "subsystems/DriveTrain.h"
#include "subsystems/GyroSub.h"
#include "subsystems/VisionBridgeSub.h"
#include "OI.h"

#include <frc/AnalogInput.h>
#include <frc/commands/Command.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/TimedRobot.h>

#include <AHRS.h>
#include <ctre/Phoenix.h>

#define DIFFSWERVE 1

// If using DIFFSWERVE, must set ONE of the following to 1:
#define USING_DIFFSWERVE_TALON_FX 1
#define USING_DIFFSWERVE_TALON_SRX 0

class Robot : public frc::TimedRobot {
public:

#if DIFFSWERVE
	typedef IVelocityMultiController DRIVE_MOTOR_TYPE;
	typedef IVelocityMultiController STEER_MOTOR_TYPE;

#if USING_DIFFSWERVE_TALON_FX
	typedef CANCoder DRIVE_POSITION_ENCODER_TYPE;
#elif USING_DIFFSWERVE_TALON_SRX
	typedef frc::AnalogInput DRIVE_POSITION_ENCODER_TYPE;
#else
#error Unsupported configuration. Check USING_DIFFSWERVE_* #defines.
#endif

#else
	typedef IMultiController DRIVE_MOTOR_TYPE;
	typedef IPositionMultiController STEER_MOTOR_TYPE;
#endif

//======= System Declaration =======//

	static OI* oi;
	static DriveTrain* driveTrain;
	static GyroSub* gyroSub;
	static VisionBridgeSub* visionBridge;

//======= Drive Train =======//

	static ISwerveModule* frontLeftModule;
	static ISwerveModule* frontRightModule;
	static ISwerveModule* rearLeftModule;
	static ISwerveModule* rearRightModule;

//======= Subsystem Motors and Sensors =======//

	static IMultiController* clampMotor;

	static AHRS* navx;

//===========================================//

	// TimedRobot methods
	virtual void RobotInit() override;
	virtual void RobotPeriodic() override;
	virtual void DisabledInit() override;
	virtual void DisabledPeriodic() override;
	virtual void AutonomousInit() override;
	virtual void AutonomousPeriodic() override;
	virtual void TeleopInit() override;
	virtual void TeleopPeriodic() override;
	virtual void TestPeriodic() override;

private:

	DRIVE_MOTOR_TYPE* _driveTrainFrontLeftDrive;
	STEER_MOTOR_TYPE* _driveTrainFrontLeftSteer;

	DRIVE_MOTOR_TYPE* _driveTrainFrontRightDrive;
	STEER_MOTOR_TYPE* _driveTrainFrontRightSteer;

	DRIVE_MOTOR_TYPE* _driveTrainRearLeftDrive;
	STEER_MOTOR_TYPE* _driveTrainRearLeftSteer;

	DRIVE_MOTOR_TYPE* _driveTrainRearRightDrive;
	STEER_MOTOR_TYPE* _driveTrainRearRightSteer;

#if DIFFSWERVE
	DRIVE_POSITION_ENCODER_TYPE* _frontLeftPot;
	DRIVE_POSITION_ENCODER_TYPE* _frontRightPot;
	DRIVE_POSITION_ENCODER_TYPE* _rearLeftPot;
	DRIVE_POSITION_ENCODER_TYPE* _rearRightPot;
#endif

	frc::Compressor* _compressor;

	frc::Solenoid* _outsol1;
	frc::Solenoid* _insol1;
	frc::Solenoid* _outsol2;
	frc::Solenoid* _insol2;

	int _counter = 0;

	void DeviceInitialization();
};
