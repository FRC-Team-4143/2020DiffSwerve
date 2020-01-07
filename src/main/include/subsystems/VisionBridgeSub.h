#pragma once

#include <frc/commands/subsystem.h>
#include <mutex>
#include <thread>

// ==========================================================================

class VisionBridgeSub : public frc::Subsystem {
public:
	// Initialize the subsystem with the default UDP port.
	VisionBridgeSub();

	// Initialize the subsystem, specifying the UDP port.
	VisionBridgeSub(uint16_t listeningPort);

	void InitDefaultCommand();

	// Enable/disable debug mode. When debug is enabled,
	// received packets are written to standard output.
	void EnableDebug(bool debug);

	// Get the latest vision data.
	double GetGearPosition();
	double GetGearDistance();
	double GetBoilerPosition();
	double GetBoilerDistance();

private:
	std::recursive_mutex _mutex;
	uint16_t _listeningPort;

	//Vision Values
	double _gearRightX1;
	double _gearRightY1;
	double _gearRightX2;
	double _gearRightY2;

	double _gearLeftX1;
	double _gearLeftY1;
	double _gearLeftX2;
	double _gearLeftY2;

	double _boilerX1;
	double _boilerX2;
	double _boilerX3;

	bool _debug;
	std::thread _listeningThread;

	void DebugOutput(std::string packet);
	void Listen();
	void ParsePacket(char packet[]);
	void SetValues(int cam, double x1, double y1, double x2, double y2);
	void SetGearRight(double x1, double y1, double x2, double y2);
	void SetGearLeft(double x1, double y1, double x2, double y2);
	void SetBoiler(double x1, double x2, double x3);
};

// ==========================================================================
