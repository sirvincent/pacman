#include "level.h"

#include <fstream>


Level::Level(std::size_t const screenWidth, std::size_t const screenHeight, std::size_t const gridWidth, std::size_t const gridHeight) : screenWidth_(screenWidth), screenHeight_(screenHeight), gridWidth_(gridWidth), gridHeight_(gridHeight) {}


void Level::convertCharacterToGameObject(char const character, unsigned int x, unsigned int y)
{
  if (character == 'o')
  {
    unsigned int radius = gridWidth_ / 4;
    Dot dot(x * gridWidth_ + gridWidth_ / 2 - radius / 2,
      y * gridHeight_ + gridHeight_ / 2 - radius / 2,
      radius);
    dots_.push_back(std::move(dot));
  }
  else if (character == 'p')
  {
    // TODO: should be twice as large as dot, so use dot radius
    unsigned int radius = gridWidth_ / 2;
    Dot pellet(x * gridWidth_ + gridWidth_ / 2 - radius / 2,
      y * gridHeight_ + gridHeight_ / 2 - radius / 2,
      radius,
      Dots::pellet_score);
    pellets_.push_back(std::move(pellet));
  }
  else if (character == '=')
  {
    SDL_Rect wall;
    wall.x = x * gridWidth_;
    wall.y = y * gridHeight_;
    wall.w = gridWidth_;
    wall.h = gridHeight_;
    walls_.push_back((std::move(wall)));
  }
  else if (character == 'P')
  {
    // TODO: circumvents that only a single p is in playing field, but it seems to me that this should
    //       be the job of the level loader to check if there is only ONE p
    if (player_.x == -1 && player_.y == -1)
    {
      player_.x = x * gridWidth_;
      player_.y = y * gridHeight_;
    }
  }
  else if (character == 'b')
  {
    std::unique_ptr<Ghosts::Ghost> blinky = std::make_unique<Ghosts::Blinky>(gridWidth_, gridHeight_, Blinky::speed);
    blinky->x                             = x * gridWidth_;
    blinky->y                             = y * gridHeight_;
    ghosts_.push_back(std::move(blinky));
  }
  else if (character == 'c')
  {
    std::unique_ptr<Ghosts::Ghost> clyde = std::make_unique<Ghosts::Clyde>(gridWidth_, gridHeight_, Clyde::speed);
    clyde->x                             = x * gridWidth_;
    clyde->y                             = y * gridHeight_;
    ghosts_.push_back(std::move(clyde));
  }
  else if (character == 'i')
  {
    std::unique_ptr<Ghosts::Ghost> inky = std::make_unique<Ghosts::Inky>(gridWidth_, gridHeight_, Inky::speed);
    inky->x                             = x * gridWidth_;
    inky->y                             = y * gridHeight_;
    ghosts_.push_back(std::move(inky));
  }
  else if (character == 'y')
  {
    std::unique_ptr<Ghosts::Ghost> pinky = std::make_unique<Ghosts::Pinky>(gridWidth_, gridHeight_, Pinky::speed);
    pinky->x                             = x * gridWidth_;
    pinky->y                             = y * gridHeight_;
    ghosts_.push_back(std::move(pinky));
  }
}


void Level::load(std::string const &directory, std::string const &filename)
{
  std::filesystem::path path = std::filesystem::current_path();
  path                       = path.parent_path();
  path /= directory;
  path /= filename;
  path.replace_extension("txt");

  std::ifstream filestream(path);
  if (filestream.is_open())
  {
    std::string line;
    unsigned int row{0};
    while (std::getline(filestream, line))
    {
      char character;
      std::istringstream stream(line);
      unsigned int column{0};
      while (stream.get(character))
      {
        convertCharacterToGameObject(character, column, row);
        ++column;
      }
      ++row;
    }
  }
  else
  {
    throw std::invalid_argument("user path could not be opened");
  }
}
