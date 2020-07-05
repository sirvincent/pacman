#include "ghost.h"


namespace Ghosts
{
  std::string Ghost::onActiveSprite()
  {
    std::string activeSpriteName{""};
    switch (direction)
    {
      // TODO: it feels as if these magic numbers belong into some sort of configuration file
      //       which contains a connection to the specific sprite sheet in use
      case Movement::Direction::up:
        activeSpriteName = "up";
        break;
      case Movement::Direction::down:
        activeSpriteName = "down";
        break;
      case Movement::Direction::left:
        activeSpriteName = "left";
        break;
      case Movement::Direction::right:
        activeSpriteName = "right";
        break;
      default:
        std::cout << "An unhandled direction is found" << std::endl;
        throw;
    }
    if (scared_)
    {
      activeSpriteName += "_scared";
    }

    return activeSpriteName;
  }

  void Ghost::setScaredAndEdible()
  {
    if (!scared_)
    {
      scared_ = true;
      edible_ = true;
      startScaredTime_ = std::chrono::system_clock::now();
    }
  }

  void Ghost::handleScaredAndEdible()
  {
    if (scared_)
    {
      long timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startScaredTime_).count();
      if (timePassed > scaredDuration_)
      {
        scared_ = false;
        edible_ = false;
      }
    }
  }


}
