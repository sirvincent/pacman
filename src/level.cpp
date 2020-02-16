#include "level.h"

#include <fstream>


Level::Level(std::size_t const screen_width, std::size_t const screen_height, std::size_t const grid_width, std::size_t const grid_height) :
  screen_width_(screen_width), screen_height_(screen_height), grid_width_(grid_width), grid_height_(grid_height) {}


void Level::convertCharacterToGameObject(char const character, unsigned int x, unsigned int y)
{
  if (character == 'o')
  {
    // TODO: Is it the job of level do the markup of Dot? or only to state hey look in this cell there is a dot!
    //       Than the draw function uses the dot style when drawing?
    unsigned int radius = grid_width_ / 4;
    Dot dot(x * grid_width_  + grid_width_  / 2 - radius / 2,
            y * grid_height_ + grid_height_ / 2 - radius / 2,
            radius);
    dots_.push_back(std::move(dot));
  }
  else if (character == 'p')
  {
    // TODO: should be twice as large as dot, so use dot radius
    unsigned int radius = grid_width_ / 2;
    Dot pellet(x * grid_width_  + grid_width_  / 2 - radius / 2,
               y * grid_height_ + grid_height_ / 2 - radius / 2,
               radius, pellet_score);
    pellets_.push_back(std::move(pellet));
  }
  else if (character == '=')
  {
    SDL_Rect wall;
    wall.x = x * grid_width_;
    wall.y = y * grid_height_;
    wall.w = grid_width_;
    wall.h = grid_height_;
    walls_.push_back((std::move(wall)));
  }
  else if (character == 'P')
  {
    // TODO: circumvents that only a single p is in playing field, but it seems to me that this should
    //       be the job of the level loader to check if there is only ONE p
    if (player_.x == -1 && player_.y == -1)
    {
      player_.x = x * grid_width_;
      player_.y = y * grid_height_;
    }
  }

}


void Level::load(std::string directory, std::string filename)
{
  std::filesystem::path path = std::filesystem::current_path();
  path = path.parent_path();
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
