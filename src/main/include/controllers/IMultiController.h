#pragma once

class IMultiController {
public:

	virtual void SetPercentPower(double value) = 0;
	virtual double GetEncoderPosition() = 0;
};
