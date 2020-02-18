#include "controllers/VelocityTalonFXController.h"
#include "Modules/Logger.h"

// ================================================================

struct Gains {
	double kP;
	double kI;
	double kD;
	double kF;
	double kIzone;
	double kPeakOutput;
};

// ================================================================

const static int PID_PRIMARY = 0;
const static int SLOT_2 = 2;

// Number of sensor units per rotation for the motor sensor.
// @link https://github.com/CrossTheRoadElec/Phoenix-Documentation#what-are-the-units-of-my-sensor
const static int kSensorUnitsPerRotation = 2048;

// Set to zero to skip waiting for confirmation.
// Set to nonzero to wait and report to DS if action fails.
const static int kTimeoutMs = 30;

// Motor neutral dead-band, set to the minimum 0.1%.
constexpr static double kNeutralDeadband = 0.001;

// PID constants                           kP   kI   kD    kF   Iz  PeakOut
constexpr static Gains kGains_Velocit = { 0.2, 0.0, 0.0, 0.05, 300, 0.70 };

const static int kSlot_Velocit = SLOT_2;

// ================================================================

VelocityTalonFXController::VelocityTalonFXController(int canId)
:	_motor{std::make_unique<WPI_TalonFX>(canId)} {
	ConfigPID();
}

// ================================================================

void VelocityTalonFXController::SetPercentPower(double value) {
	_motor->Set(ControlMode::PercentOutput, value);
}

// ================================================================

double VelocityTalonFXController::GetEncoderPosition() {
	return _motor->GetSelectedSensorVelocity();
}

// ================================================================

void VelocityTalonFXController::SetVelocity(double value) {
	_motor->Set(ControlMode::Velocity, value);
}

// ================================================================

void VelocityTalonFXController::ConfigPID() {
	_motor->ConfigFactoryDefault();

	constexpr double MAX_CURRENT = 30.0;

	SupplyCurrentLimitConfiguration supply(true, MAX_CURRENT, MAX_CURRENT, kTimeoutMs);
	_motor->ConfigSupplyCurrentLimit(supply);

	StatorCurrentLimitConfiguration stator(true, MAX_CURRENT, MAX_CURRENT, kTimeoutMs);
	_motor->ConfigStatorCurrentLimit(stator);

	_motor->SetInverted(false);
	_motor->SetSensorPhase(true);

	_motor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, PID_PRIMARY, kTimeoutMs);

	_motor->ConfigNeutralDeadband(kNeutralDeadband, kTimeoutMs);

	// Set the max output for all modes. You can also limit the
	// output of a given PID object with ConfigClosedLoopPeakOutput().
	_motor->ConfigPeakOutputForward(+1.0, kTimeoutMs);
	_motor->ConfigPeakOutputReverse(-1.0, kTimeoutMs);

	// Configure the velocity PID.
	_motor->Config_kP(kSlot_Velocit, kGains_Velocit.kP, kTimeoutMs);
	_motor->Config_kI(kSlot_Velocit, kGains_Velocit.kI, kTimeoutMs);
	_motor->Config_kD(kSlot_Velocit, kGains_Velocit.kD, kTimeoutMs);
	_motor->Config_kF(kSlot_Velocit, kGains_Velocit.kF, kTimeoutMs);
	_motor->Config_IntegralZone(kSlot_Velocit, kGains_Velocit.kIzone, kTimeoutMs);
	_motor->ConfigClosedLoopPeakOutput(kSlot_Velocit, kGains_Velocit.kPeakOutput, kTimeoutMs);

	_motor->SetNeutralMode(NeutralMode::Coast);

	_motor->SelectProfileSlot(kSlot_Velocit, PID_PRIMARY);
}

// ================================================================
