#pragma once

#include "pacman.h"

struct Controller
{
  void handleInput(bool &running, Pacman &pacman) const;
};
