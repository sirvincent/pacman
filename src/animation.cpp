#include "animation.h"

namespace Implementation {

Animation::Animation(std::string const &relativePathSpriteSheetToAssetsDirectory,
  std::chrono::time_point<std::chrono::system_clock> lastUpdate,
  std::map<std::string, AnimationProperty> const &animations,
  std::string nameActiveSprite)
  : Implementation::SpriteGraphics(relativePathSpriteSheetToAssetsDirectory)
  , lastUpdate_(lastUpdate)
  , animations_(animations)
  , index_(0)
{
  currentAnimation_ = &animations_.at(nameActiveSprite);
}


{
  // TODO: use C++20 .contains()
  auto search  = animations_.find(name);
  if (search == animations_.end())
  {
    std::cerr << name << " is not in animations_ keys" << std::endl;
    assert(false);
  }

  auto current = &search->second;

  if (currentAnimation_ != current)
  {
    currentAnimation_ = current;
    index_            = 0;
  }

  determineAnimateIndex();
}


std::pair<SDL_Texture *, SDL_Rect> Animation::activeSprite()
{
  std::string name = onActiveSprite();
  update(name);

  return std::make_pair(spriteSheet_, currentAnimation_->rectangles.at(index_));
}

void Animation::determineAnimateIndex()
{
  std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastUpdate_).count() > currentAnimation_->periodMilliseconds)
  {
    index_++;
    if (index_ >= currentAnimation_->rectangles.size())
    {
      index_ = 0;
    }

    lastUpdate_ = currentTime;
  }
}

}  // namespace Implementation
