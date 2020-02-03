#pragma once
#include "controllers/MultiController.h"
#include "controllers/PositionMultiController.h"
#include "controllers/VelocityMultiController.h"
#include "Modules/SwerveModuleInterface.h"
#include "subsystems/DriveTrain.h"
#include "subsystems/GyroSub.h"
#include "subsystems/VisionBridgeSub.h"
#include "OI.h"

#include <frc/AnalogInput.h>
#include <frc/commands/Command.h>
#include <frc/Compressor.h>
#include <frc/I2C.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Solenoid.h>
#include <frc/TimedRobot.h>

#include <rev/CANSparkMax.h>
#include <rev/SparkMax.h>

#include <ctre/Phoenix.h>

#include <AHRS.h>

#define DIFFSWERVE 1

// If using DIFFSWERVE, must set ONE of the following to 1:
#define USING_DIFFSWERVE_TALON_FX 1
#define USING_DIFFSWERVE_TALON_SRX 0

class Robot : public frc::TimedRobot {
public:

#if DIFFSWERVE
	typedef VelocityMultiController DRIVE_MOTOR_TYPE;
	typedef VelocityMultiController STEER_MOTOR_TYPE;

#if USING_DIFFSWERVE_TALON_FX
	typedef CANCoder DRIVE_POSITION_ENCODER_TYPE;
#elif USING_DIFFSWERVE_TALON_SRX
	typedef frc::AnalogInput DRIVE_POSITION_ENCODER_TYPE;
#else
#error Unsupported configuration. Check USING_DIFFSWERVE_* #defines.
#endif

#else
	typedef MultiController DRIVE_MOTOR_TYPE;
	typedef PositionMultiController STEER_MOTOR_TYPE;
#endif

//======= System Declaration =======//

	static OI* oi;
	static DriveTrain* driveTrain;
	static GyroSub* gyroSub;
	static VisionBridgeSub* visionBridge;
	static frc::PowerDistributionPanel* pdp;
	static frc::Compressor* comp;

//======= Drive Train =======//

	static SwerveModuleInterface* frontLeftModule;
	static SwerveModuleInterface* frontRightModule;
	static SwerveModuleInterface* rearLeftModule;
	static SwerveModuleInterface* rearRightModule;

//======= Susystem Motors and Sensors =======//

	static PositionMultiController* armMotor;
	static MultiController* clampMotor;
	static MultiController* frontClimberMotor;
	static MultiController* rearClimberMotor;
	static PositionMultiController* elevatorMotor;
	static MultiController* rollerMotor;
	static MultiController* testElevator;

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

	int counter = 0;
	static double xCenterOffset;
	static double yCenterOffset;

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

	frc::Solenoid* _outsol;
	frc::Solenoid* _insol;

	void DeviceInitialization();
};
