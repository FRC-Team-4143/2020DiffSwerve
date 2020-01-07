#include "subsystems/VisionBridgeSub.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "modules/CastUtil.h"
#include "modules/Logger.h"
#include "Robot.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <condition_variable>
#include <iostream>

const uint16_t DEFAULT_LISTENING_PORT = 4143; // TODO - Change to allowed port range

#define MAX_PACKET_SIZE 2048

// ==========================================================================

VisionBridgeSub::VisionBridgeSub()
:	VisionBridgeSub(DEFAULT_LISTENING_PORT) {
}

// ==========================================================================

VisionBridgeSub::VisionBridgeSub(uint16_t listeningPort)
:	frc::Subsystem("VisionBridgeSub"),
	_mutex(),
	_listeningPort(listeningPort),
	_gearRightX1(0),
	_gearRightY1(0),
	_gearRightX2(0),
	_gearRightY2(0),
	_gearLeftX1(0),
	_gearLeftY1(0),
	_gearLeftX2(0),
	_gearLeftY2(0),
	_boilerX1(0),
	_boilerX2(0),
	_boilerX3(0),
	_debug(false),
	_listeningThread(&VisionBridgeSub::Listen, this) {
}

// ==========================================================================

void VisionBridgeSub::InitDefaultCommand() {
	//SetDefaultCommand(new MySpecialCommand());
}

// ==========================================================================

void VisionBridgeSub::EnableDebug(bool debug) {
	_debug = debug;
}

// ==========================================================================
// Side 0 is left
// Side 1 is right

double VisionBridgeSub::GetGearPosition() {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	return (_gearRightX1 + _gearRightX2 + _gearLeftX1 + _gearLeftX2)/4;
}

// ==========================================================================

double VisionBridgeSub::GetGearDistance() {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	return (_gearRightY1 + _gearRightY2 + _gearLeftY1 + _gearLeftY2)/4;
}

// ==========================================================================

double VisionBridgeSub::GetBoilerPosition() {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	float lowestNum = _boilerX1;
	if(_boilerX2 != 0 && fabs(_boilerX2) < fabs(lowestNum))
		lowestNum = _boilerX2;
	if(_boilerX3 != 0 && fabs(_boilerX3) < fabs(lowestNum))
		lowestNum = _boilerX3;
	
	return lowestNum;
}

/* ==========================================================================

double VisionBridgeSub::GetBoilerDistance() {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	return _boilerY1;
	return 0;
}

*/ // ==========================================================================

void VisionBridgeSub::DebugOutput(std::string packet) {
	LOG("VisionPacket=" + packet);
}

// ==========================================================================

void VisionBridgeSub::Listen() {
	sockaddr_in serverAddr; // server's socket address
	sockaddr_in clientAddr; // client's socket address
	socklen_t sockAddrSize; // size of socket address structure
	int sockListener;       // socket file descriptor
	char buf[MAX_PACKET_SIZE + 1];

	// Set up the local address.
	sockAddrSize = sizeof(sockaddr_in);
	bzero(&serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_listeningPort);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	std::cout << GetName() << " Starting UDP listener on port " << _listeningPort << std::endl;

	// Create a UDP socket.
	sockListener = socket(AF_INET, SOCK_DGRAM, 0);
	//if ((sockListener = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR) {
	//    perror("socket");
	//    return;
	//}
	std::cout << GetName() << " Created socket" << std::endl;

	// Bind socket to local address.
	bind(sockListener, S_CAST(sockaddr *, S_CAST(void *, &serverAddr)), sockAddrSize);
	//if (bind(sockListener, S_CAST(sockaddr*, S_CAST(void*, &serverAddr)), sockAddrSize) == ERROR) {
	//    perror("bind");
	//    close(sockListener);
	//    return;
	//}
	std::cout << GetName() << " Bound socket" << std::endl;

	for (;;) {
		//if (_debug) std::cout << "[DEBUG] " << GetName() << " Waiting on port" << std::endl;
		int recvlen = recvfrom(sockListener, buf, sizeof(buf) - 1, 0,
				S_CAST(sockaddr *, S_CAST(void *, &clientAddr)),
				&sockAddrSize);
		//if (_debug) std::cout << "[DEBUG] " << GetName() << " Received " << recvlen << " bytes" << std::endl;
		if (recvlen > 0) {
			buf[recvlen] = 0;
			ParsePacket(buf);
		}
	}

	close(sockListener);
}

// ==========================================================================

void VisionBridgeSub::ParsePacket(char packet[]) {
	if (_debug) {
		DebugOutput(packet);
	}
	try {
		char* pch = std::strtok(packet, " ");
		auto x1 = std::stod(pch);
		pch = std::strtok(nullptr, " ");
		auto x2 = std::stod(pch);
		pch = std::strtok(nullptr, " ");
		auto x3 = std::stod(pch);
		pch = std::strtok(nullptr, " ");
		int cam = std::stod(pch);

		switch (cam){
		case 0:
			SetBoiler(x1, x2, x3);
			break;
		case 1:
			//SetGearLeft(x1, y1, x2, y2);
			break;
		case 2:
			//SetGearRight(x1, y1, x2, y2);
			break;
		}
	}
	catch (...) {
	}
}

// ==========================================================================

void VisionBridgeSub::SetGearRight(double x1, double y1, double x2, double y2) {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	if (x1 != 0.0) _gearRightX1 = x1;
	if (y1 != 0.0) _gearRightY1 = y1;
	if (x2 != 0.0) _gearRightX2 = x2;
	if (y2 != 0.0) _gearRightY2 = y2;

	SmartDashboard::PutNumber("gearRightX1", x1);
	SmartDashboard::PutNumber("gearRightY1", y1);
	SmartDashboard::PutNumber("gearRightX2", x2);
	SmartDashboard::PutNumber("gearRightY2", y2);
}

// ==========================================================================

void VisionBridgeSub::SetGearLeft(double x1, double y1, double x2, double y2) {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	if (x1 != 0.0) _gearLeftX1 = x1;
	if (y1 != 0.0) _gearLeftY1 = y1;
	if (x2 != 0.0) _gearLeftX2 = x2;
	if (y2 != 0.0) _gearLeftY2 = y2;

	SmartDashboard::PutNumber("gearLeftX1", x1);
	SmartDashboard::PutNumber("gearLeftY1", y1);
	SmartDashboard::PutNumber("gearLeftX2", x2);
	SmartDashboard::PutNumber("gearLeftY2", y2);
}

// ==========================================================================
void VisionBridgeSub::SetBoiler(double x1, double x2, double x3) {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	if (x1 != 0.0) _boilerX1 = x1;
	if (x2 != 0.0) _boilerX2 = x2;
	if (x3 != 0.0) _boilerX3 = x3;

	SmartDashboard::PutNumber("BoilerX1", x1);
	SmartDashboard::PutNumber("BoilerX2", x2);
	SmartDashboard::PutNumber("BoilerX3", x3);
	

}

// ==========================================================================
