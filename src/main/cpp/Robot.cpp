#define DIFFSWERVE 1
#include "Robot.h"
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/RobotController.h>
#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>
#include <iostream>

#include "controllers/TalonController.h"
#include "controllers/VictorController.h"
#include "controllers/SteerTalonController.h"
#include "controllers/SparkMaxController.h"
#include "controllers/PositionSparkController.h"
#include "controllers/VelocitySparkController.h"

#include "Modules/Logger.h"
#include "Modules/Constants.h"

#define USINGSPARKMAXDRIVE 1
#define USINGVICTORDRIVE 0 // 1 for Comp Bot 
#define ONROBORIONAVX 0 // 0 for Comp Bot
#define TESTBOT (0.45)


#define TESTELEVATOR 21
#define ELEVATOR 11
#define CLAMP 12
#define ROLLER 13
#define ARM 14
#define FRONTCLIMBER 15
#define REARCLIMBER 16

/*
#define FLD 1
#define FLS 2

#define FRD 3
#define FRS 4

#define RLD 5
#define RLS 6

#define RRD 7
#define RRS 8
*/

//======= System Definition =======//
OI* Robot::oi = nullptr;
DriveTrain* Robot::driveTrain = nullptr;
GyroSub* Robot::gyroSub = nullptr;
VisionBridgeSub* Robot::visionBridge = nullptr;
PowerDistributionPanel* Robot::pdp = nullptr;
Compressor* Robot::comp = nullptr;

static constexpr auto i2cPort = frc::I2C::Port::kOnboard;

//======= Motor Definition =======//
#if DIFFSWERVE
VelocityMultiController* Robot::driveTrainFrontLeftDrive = nullptr;
VelocityMultiController* Robot::driveTrainFrontLeftSteer = nullptr;

VelocityMultiController* Robot::driveTrainFrontRightDrive = nullptr;
VelocityMultiController* Robot::driveTrainFrontRightSteer = nullptr;

VelocityMultiController* Robot::driveTrainRearLeftDrive = nullptr;
VelocityMultiController* Robot::driveTrainRearLeftSteer = nullptr;

VelocityMultiController* Robot::driveTrainRearRightDrive = nullptr;
VelocityMultiController* Robot::driveTrainRearRightSteer = nullptr;

SwerveModuleInterface* Robot::frontLeftModule = nullptr;
SwerveModuleInterface* Robot::frontRightModule = nullptr;
SwerveModuleInterface* Robot::rearLeftModule = nullptr;
SwerveModuleInterface* Robot::rearRightModule  = nullptr;

AnalogInput* Robot::frontRightPot = nullptr;
AnalogInput* Robot::frontLeftPot = nullptr;
AnalogInput* Robot::rearRightPot = nullptr;
AnalogInput* Robot::rearLeftPot = nullptr;

#else
MultiController* Robot::driveTrainFrontLeftDrive = nullptr;
PositionMultiController* Robot::driveTrainFrontLeftSteer = nullptr;

MultiController* Robot::driveTrainFrontRightDrive = nullptr;
PositionMultiController* Robot::driveTrainFrontRightSteer = nullptr;

MultiController* Robot::driveTrainRearLeftDrive = nullptr;
PositionMultiController* Robot::driveTrainRearLeftSteer = nullptr;

MultiController* Robot::driveTrainRearRightDrive = nullptr;
PositionMultiController* Robot::driveTrainRearRightSteer = nullptr;

SwerveModuleInterface* Robot::frontLeftModule = nullptr;
SwerveModuleInterface* Robot::frontRightModule = nullptr;
SwerveModuleInterface* Robot::rearLeftModule = nullptr;
SwerveModuleInterface* Robot::rearRightModule  = nullptr;
#endif

MultiController* Robot::clampMotor = nullptr;

Servo* Robot::frontServo = nullptr;
Servo* Robot::rearServo = nullptr;

AHRS* Robot::navx = nullptr;

Solenoid* Robot::outsol = nullptr;
Solenoid* Robot::insol = nullptr;

rev::ColorSensorV3 m_colorSensor{i2cPort};
rev::ColorMatch m_colorMatcher;

static constexpr frc::Color kBlueTarget = frc::Color(0.121, 0.406, 0.472);
static constexpr frc::Color kGreenTarget = frc::Color(0.163, 0.572, 0.264);
static constexpr frc::Color kRedTarget = frc::Color(0.524, 0.339, 0.139);
static constexpr frc::Color kYellowTarget = frc::Color(0.317, 0.558, 0.124);


double Robot::xCenterOffset = 0;
double Robot::yCenterOffset = 0;


void Robot::DeviceInitialization(){
   //CameraServer::GetInstance()->StartAutomaticCapture();
   comp = new Compressor(0);

   insol = new Solenoid(0);
   outsol = new Solenoid(1);

   #if DIFFSWERVE

 /*     driveTrainFrontLeftSteer = new VelocitySparkController(&sparkmax1);
      driveTrainFrontRightSteer = new VelocitySparkController(&sparkmax2);
      driveTrainRearLeftSteer = new VelocitySparkController(&sparkmax3);
      driveTrainRearRightSteer = new VelocitySparkController(&sparkmax4);
      driveTrainFrontLeftDrive = new VelocitySparkController(&sparkmax5);
      driveTrainFrontRightDrive = new VelocitySparkController(&sparkmax6);
      driveTrainRearLeftDrive = new VelocitySparkController(&sparkmax7);
      driveTrainRearRightDrive = new VelocitySparkController(&sparkmax8); */

      driveTrainFrontLeftSteer = new VelocitySparkController(5);
      driveTrainFrontLeftDrive = new VelocitySparkController(6);
      driveTrainFrontRightSteer = new VelocitySparkController(3);
      driveTrainFrontRightDrive = new VelocitySparkController(4);
      driveTrainRearLeftSteer = new VelocitySparkController(7);
      driveTrainRearLeftDrive = new VelocitySparkController(8);
      driveTrainRearRightSteer = new VelocitySparkController(1);
      driveTrainRearRightDrive = new VelocitySparkController(2); 
   #else
   //======= Front Left Steer =======//
      driveTrainFrontLeftSteer = new SteerTalonController(FLS);
   //======= Front Right Steer =======//
      driveTrainFrontRightSteer = new SteerTalonController(FRS);
   //======= Rear Left Steer =======//
      driveTrainRearLeftSteer = new SteerTalonController(RLS);
   //======= Rear Right Steer =======//
      driveTrainRearRightSteer = new SteerTalonController(RRS);


   #if USINGSPARKMAXDRIVE
   //======= Front Left Drive =======//
      driveTrainFrontLeftDrive = new SparkMaxController(FLD);
   //======= Front Right Drive =======//
      driveTrainFrontRightDrive = new SparkMaxController(FRD);
   //======= Rear Left Drive =======//
      driveTrainRearLeftDrive = new SparkMaxController(RLD);
   //======= Rear Right Drive =======//
      driveTrainRearRightDrive = new SparkMaxController(RRD);

   #else
   #if USINGVICTORDRIVE
   //======= Front Left Drive =======//
      driveTrainFrontLeftDrive = new VictorController(FLD);
   //======= Front Right Drive =======//
      //driveTrainFrontRightDrive = new VictorController(FRD);
      driveTrainFrontRightDrive = new TalonController(FRD);
   //======= Rear Left Drive =======//
      driveTrainRearLeftDrive = new VictorController(RLD);
   //======= Rear Right Drive =======//
      driveTrainRearRightDrive = new VictorController(RRD);

   #else
   //======= Front Left Drive =======//
      driveTrainFrontLeftDrive = new TalonController(FLD);
   //======= Front Right Drive =======//
      driveTrainFrontRightDrive = new TalonController(FRD);
   //======= Rear Left Drive =======//
      driveTrainRearLeftDrive = new TalonController(RLD);
   //======= Rear Right Drive =======//
      driveTrainRearRightDrive = new TalonController(RRD);
   #endif
   #endif
   #endif

//======= Subsystem Motor Initialization =======//
   clampMotor = new TalonController(CLAMP);

   frontServo = new Servo(0);
   rearServo = new Servo(1);
   LOG("DeviceInit Navx");

//======= Sensor and Camera Initialization =======//
#if ONROBORIONAVX
   //navx = new AHRS(I2C::Port::kMXP);
#else
   //navx = new AHRS(I2C::Port::kOnboard); //kOnboard ?
#endif

//======= System Initialization =======//
   
   gyroSub = new GyroSub();
   visionBridge = new VisionBridgeSub();
   oi = new OI();

   LOG("DeviceInit Analog");

//======== Swerve Module Initialization =========//
#if DIFFSWERVE
   frontLeftPot = new AnalogInput(2);
   frontRightPot = new AnalogInput(1);
   rearLeftPot = new AnalogInput(3);
   rearRightPot = new AnalogInput(0);

   frontLeftModule = new DiffSwerveModule(driveTrainFrontLeftDrive, driveTrainFrontLeftSteer, Constants::FL_POS_NAME, frontLeftPot);
   frontRightModule = new DiffSwerveModule(driveTrainFrontRightDrive, driveTrainFrontRightSteer, Constants::FR_POS_NAME, frontRightPot);
   rearLeftModule = new DiffSwerveModule(driveTrainRearLeftDrive, driveTrainRearLeftSteer, Constants::RL_POS_NAME, rearLeftPot);
   rearRightModule = new DiffSwerveModule(driveTrainRearRightDrive, driveTrainRearRightSteer, Constants::RR_POS_NAME, rearRightPot);
#else
   frontLeftModule = new SwerveModule(driveTrainFrontLeftDrive, driveTrainFrontLeftSteer, Constants::FL_POS_NAME);
   frontRightModule = new SwerveModule(driveTrainFrontRightDrive, driveTrainFrontRightSteer, Constants::FR_POS_NAME);
   rearLeftModule = new SwerveModule(driveTrainRearLeftDrive, driveTrainRearLeftSteer, Constants::RL_POS_NAME);
   rearRightModule = new SwerveModule(driveTrainRearRightDrive, driveTrainRearRightSteer, Constants::RR_POS_NAME);
#endif
   driveTrain = new DriveTrain();
   LOG("DeviceInit DriveTrain");
   LOG("DeviceInit end");
}


void Robot::RobotInit() {
   DeviceInitialization();
   SmartDashboard::PutNumber("Yaw Offset", 0);
   driveTrain->LoadWheelOffsets();

   m_colorMatcher.AddColorMatch(kBlueTarget);
   m_colorMatcher.AddColorMatch(kGreenTarget);
   m_colorMatcher.AddColorMatch(kRedTarget);
   m_colorMatcher.AddColorMatch(kYellowTarget);

   LOG("RobotInit end");
}
   
void Robot::RobotPeriodic() {
   //LOG("robotperiodic start");
   if (navx != nullptr) {
      auto yawOff = SmartDashboard::GetNumber("Yaw Offset", 0);
      SmartDashboard::PutNumber("Yaw", Robot::navx->GetYaw() + yawOff);
   }

   frc::Color detectedColor = m_colorSensor.GetColor();

   std::string colorString;
   double confidence = 0.0;
   frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

   if (matchedColor == kBlueTarget) {
      colorString = "Blue";
   } else if (matchedColor == kRedTarget) {
      colorString = "Red";
   } else if (matchedColor == kGreenTarget) {
      colorString = "Green";
   } else if (matchedColor == kYellowTarget) {
      colorString = "Yellow";
   } else {
      colorString = "Unknown";
   }

   frc::SmartDashboard::PutNumber("Red", detectedColor.red);
   frc::SmartDashboard::PutNumber("Green", detectedColor.green);
   frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
   frc::SmartDashboard::PutNumber("Confidence", confidence);
   frc::SmartDashboard::PutString("ColorDetected", colorString);

   if(oi->GetButtonY()){
      LOG("sol out");
      insol->Set(false);
      outsol->Set(true);
   }else if(oi->GetButtonA()){
      LOG("sol in");
      outsol->Set(false);
      insol->Set(true);
   }

   if(oi->GetButtonX() || oi->GetLeftBumper())
      clampMotor->SetPercentPower(-.3);
   else if(oi->GetButtonB() || oi->GetRightBumper())
      clampMotor->SetPercentPower(.3);
   else
   {
      clampMotor->SetPercentPower(0);
   }
   


	if (frc::RobotController::GetUserButton() == 1 && counter == 0) {
		Robot::driveTrain->SetWheelOffsets();
		counter = 100;
		std::cout << "SetWheelOffsets Complete" << std::endl;
      std::cout.flush();
	}
	if (counter > 0) {
      counter -= 1;
   }

   xCenterOffset = SmartDashboard::GetNumber("X Center Offset", 0);
   yCenterOffset = SmartDashboard::GetNumber("Y Center Offset", 0);
   SmartDashboard::PutNumber("X Center Offset", xCenterOffset);
   SmartDashboard::PutNumber("Y Center Offset", yCenterOffset);

   SmartDashboard::PutNumber("fl position", frontLeftModule->GetSteerPosition());
   SmartDashboard::PutNumber("fr position", frontRightModule->GetSteerPosition());
   SmartDashboard::PutNumber("rl position", rearLeftModule->GetSteerPosition());
   SmartDashboard::PutNumber("rr position", rearRightModule->GetSteerPosition());
 
 
   SmartDashboard::PutNumber("fl setpoint", frontLeftModule->GetSetpoint());
   SmartDashboard::PutNumber("fr setpoint", frontRightModule->GetSetpoint());
   SmartDashboard::PutNumber("rl setpoint", rearLeftModule->GetSetpoint());
   SmartDashboard::PutNumber("rr setpoint", rearRightModule->GetSetpoint());

   SmartDashboard::PutNumber("fl power", frontLeftModule->GetPower());
   SmartDashboard::PutNumber("fr power", frontRightModule->GetPower());
   SmartDashboard::PutNumber("rl power", rearLeftModule->GetPower());
   SmartDashboard::PutNumber("rr power", rearRightModule->GetPower());


   Robot::driveTrain->SetWheelbase(14, 14);
}

void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {
   frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
      comp->SetClosedLoopControl(true);


}

void Robot::AutonomousPeriodic() {
   frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
      comp->SetClosedLoopControl(true);

}

void Robot::TeleopPeriodic() {
   frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
}

#ifndef RUNNING_FRC_TESTS
int main(){
   return frc::StartRobot<Robot>();
}
#endif
