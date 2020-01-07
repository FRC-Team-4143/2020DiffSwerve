#pragma once
#include "controllers/MultiController.h"

class PositionMultiController : public MultiController {
public:
    virtual void SetPosition(double value) = 0;
    virtual void ConfigPID() = 0;
};