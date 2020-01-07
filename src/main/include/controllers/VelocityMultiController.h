#pragma once
#include "controllers/MultiController.h"

class VelocityMultiController : public MultiController {
public:
    virtual void SetVelocity(double value) = 0;
    virtual void ConfigPID() = 0;
};