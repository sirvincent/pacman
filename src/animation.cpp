#include "animation.h"

namespace Implementation {

Animation::Animation(std::string const &relativePathSpriteSheetToAssetsDirectory,
  uint32_t currentMsSinceStart,
  std::map<std::string, AnimationProperty> const &animations,
  std::string nameActiveSprite)
  : Implementation::SpriteGraphics(relativePathSpriteSheetToAssetsDirectory)
  , currentMsSinceStart_(currentMsSinceStart)
  , animations_(animations)
  , index_(0)
{
  currentAnimation_ = &animations_.at(nameActiveSprite);
}


void Animation::update(std::string name, uint32_t timeSinceStart)
{
  auto current = &animations_.at(name);
  // TODO: handle std::out_of_range exception
  if (currentAnimation_ != current)
  {
    currentAnimation_ = current;
    index_            = 0;
  }

  determineAnimateIndex(timeSinceStart);
}


std::pair<SDL_Texture *, SDL_Rect> Animation::activeSprite(uint32_t timeSinceStartMilliseconds)
{
  std::string name = onActiveSprite();
  update(name, timeSinceStartMilliseconds);

  return std::make_pair(spriteSheet_, currentAnimation_->rectangles.at(index_));
}

void Animation::determineAnimateIndex(uint32_t timeSinceStart)
{
  if ((timeSinceStart - currentMsSinceStart_) > currentAnimation_->periodMilliseconds)
  {
    index_++;
    if (index_ >= currentAnimation_->rectangles.size())
    {
      index_ = 0;
    }

    currentMsSinceStart_ = timeSinceStart;
  }
}

}  // namespace Implementation
