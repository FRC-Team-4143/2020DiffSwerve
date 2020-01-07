#pragma once

#include <frc/commands/Command.h>

class SetWheelOffsets : public frc::Command {
 public:


  SetWheelOffsets();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
