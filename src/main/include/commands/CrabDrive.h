#pragma once

#include <frc/commands/Command.h>

class CrabDrive : public frc::Command {
 public:


  CrabDrive();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
