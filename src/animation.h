#pragma once

#include "sprite_graphics.h"

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <array>
#include <map>


// TODO: animation properties

/*
template <std::size_t arraySize>
struct AnimationProperty
{
  constexpr AnimationProperty(std::array<SDL_Rect, arraySize> r, float f, char const *n) :
    rectangles(r), frequencyHz(f), name(n) {}
  std::array<SDL_Rect, arraySize> const rectangles;
  float const frequencyHz; // in Hz
  char const *name;
};

constexpr AnimationProperty<2> property({SDL_Rect{1, 0, 2, 3}, SDL_Rect{0, 2, 3, 4}}, 5.0, "animation_property");
constexpr AnimationProperty<2> property2({SDL_Rect{2, 4, 5, 6}, SDL_Rect{7, 8, 9, 1}}, 6.0, "animation_property_2");
*/
struct AnimationProperty
{
  AnimationProperty(std::vector<SDL_Rect> const &r, float const period)
    : rectangles(r)
    , periodMilliseconds(period)
  {}
  std::vector<SDL_Rect> rectangles;
  float const periodMilliseconds;
};


class Animation : public virtual SpriteGraphics
{
public:
  virtual ~Animation() = default;

  virtual std::string onActiveSprite()                                       = 0;
  virtual void update(std::string name, uint32_t timeSinceStartMilliseconds) = 0;
  // TODO: in place of using SDL_GetTicks should we use Chrono?
  virtual void determineAnimateIndex(uint32_t timeSinceStartMilliseconds) = 0;


private:
};


namespace Implementation {

class Animation : public virtual ::Animation
  , public Implementation::SpriteGraphics
{
public:
  Animation(std::string const &relativePathSpriteSheetToAssetsDirectory,
    uint32_t currentMsSinceStart,
    std::map<std::string, AnimationProperty> const &animations,
    std::string nameActiveSprite);

  std::pair<SDL_Texture *, SDL_Rect> activeSprite(uint32_t timeSinceStartMilliseconds) override;
  void determineAnimateIndex(uint32_t timeSinceStartMilliseconds) override;

protected:
  void update(std::string name, uint32_t timeSinceStart) override;

private:
  uint32_t currentMsSinceStart_;

  std::map<std::string, AnimationProperty> const animations_;
  AnimationProperty const *currentAnimation_;

  // to cycle through animation
  unsigned int index_;
};

}  // namespace Implementation
