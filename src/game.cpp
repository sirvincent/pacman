#include "game.h"

#include "SDL.h"

#include <iostream>
#include <cassert>


Game::Game(std::size_t screenWidth, std::size_t screenHeight, std::size_t gridWidth, std::size_t gridHeight, std::filesystem::path executablePath) : screenWidth_(screenWidth), screenHeight_(screenHeight), gridWidth_(gridWidth), gridHeight_(gridHeight),
                                                                                                                                                     pacman_(gridWidth, gridHeight, Pacman::pacman_speed), executablePath_(executablePath)
{
  Level level(screenWidth, screenHeight, gridWidth, gridHeight);
  level.load();
  // TODO: hmm is this a code smell?
  dots_     = std::move(level.dots_);
  pellets_  = std::move(level.pellets_);
  walls_    = std::move(level.walls_);
  ghosts_   = std::move(level.ghosts_);
  pacman_.x = level.player_.x;
  pacman_.y = level.player_.y;
}

void Game::run(Controller const &controller, Renderer &renderer, uint32_t const targetFrameDuration)
{
  uint32_t titleTimestamp = SDL_GetTicks();
  int frameCount          = 0;
  bool running            = true;

  // TODO: initialize here?
  renderer.initialize(pacman_, ghosts_, executablePath_);


  while (running)
  {
    uint32_t frameStart = SDL_GetTicks();

    controller.handleInput(running, pacman_);

    update(running);

    renderer.render(pacman_, dots_, pellets_, walls_, ghosts_);


    // TODO: enforce frame duration, move into separate function
    uint32_t frameEnd = SDL_GetTicks();

    frameCount++;
    uint32_t frameDuration = frameEnd - frameStart;

    if (frameEnd - titleTimestamp >= timeBetweenTitleUpdate_)
    {
      renderer.updateWindowTitle(score_, frameCount);
      frameCount     = 0;
      titleTimestamp = frameEnd;
    }

    if (frameDuration < targetFrameDuration)
    {
      SDL_Delay(targetFrameDuration - frameDuration);
    }
  }
}


bool Game::checkRectangleCollisions(SDL_FRect const &rectangle, std::vector<SDL_Rect> &other)
{
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    if (checkRectangleCollision<SDL_FRect, SDL_Rect>(rectangle, *it))
    {
      return true;
    }
  }
  return false;
}


// TODO: come up with a better short name than other for other rectangle
template<typename RECTANGLE, typename OTHER>
bool Game::checkRectangleCollision(RECTANGLE const &rectangle, OTHER const &other)
{
  // TODO: I picked the largest type of SDL_FRect and SDL_Rect but is there a way to deduce
  //       this type from the object?
  float const leftRectangle   = rectangle.x;
  float const rightRectangle  = rectangle.x + rectangle.w;
  float const topRectangle    = rectangle.y;
  float const bottomRectangle = rectangle.y + rectangle.h;

  float const leftOther   = other.x;
  float const rightOther  = other.x + other.w;
  float const topOther    = other.y;
  float const bottomOther = other.y + other.h;

  // check if not colliding based on separating axis
  if (bottomRectangle <= topOther)
  {
    return false;
  }
  if (topRectangle >= bottomOther)
  {
    return false;
  }
  if (rightRectangle <= leftOther)
  {
    return false;
  }
  if (leftRectangle >= rightOther)
  {
    return false;
  }

  return true;
}

bool Game::handlePacmanDotCollisions(Pacman const &pacman, std::vector<Dot> &dots)
{
  for (auto it = dots.begin(); it != dots.end(); ++it)
  {
    // TODO: give Dot a member to rectanlge? Or simply do not have circular dots?
    SDL_Rect dotRectangle;
    dotRectangle.x = it->x();
    dotRectangle.y = it->y();
    dotRectangle.w = it->radius();
    dotRectangle.h = it->radius();

    if (checkRectangleCollision<SDL_FRect, SDL_Rect>(pacman, dotRectangle))
    {
      score_ += it->score();
      dots.erase(it);
      return true;
    }
  }

  return false;
}

void Game::handlePacmanGhostCollisions(Pacman const &pacman, std::vector<std::unique_ptr<Ghosts::Ghost>> &ghosts)
{
  for (auto it = ghosts.begin(); it != ghosts.end(); ++it)
  {
    // TODO: to be representative of pacman once the ghost completely or almost completely overlaps pacman
    //       should pacman die not when they start to touch
    if (checkRectangleCollision<SDL_FRect, SDL_FRect>(pacman, *(*it)))
    {
      if ((*it)->edible)
      {
        score_ += (*it)->score();
        // TODO: not representative of pacman, ghost should remain alive but go back to its cage in the center
        ghosts.erase(it);
        return;
      }
      else
      {
        pacman_.alive(false);
      }
    }
  }
}


// require CHARACTER is pacman or Ghost
template<typename CHARACTER>
void Game::moveCharacter(CHARACTER &character)
{
  character.adjustXYVelocityOnDirection(character.wantedDirection);
  SDL_FRect wantedPacmanLocation = character;
  wantedPacmanLocation.x         = character.x + character.velocityX();
  wantedPacmanLocation.y         = character.y + character.velocityY();

  bool validDirection = checkMoveInBounds(wantedPacmanLocation);

  if (!validDirection)
  {
    character.adjustXYVelocityOnDirection(character.direction);
    SDL_FRect wantedPacmanOldLocation = character;
    wantedPacmanOldLocation.x         = character.x + character.velocityX();
    wantedPacmanOldLocation.y         = character.y + character.velocityY();

    bool validOldDirection = checkMoveInBounds(wantedPacmanOldLocation);
    if (validOldDirection)
    {
      character.move();
    }
  }
  else
  {
    character.direction = character.wantedDirection;
    character.move();
  }
}


bool Game::checkMoveInBounds(SDL_FRect rectangle)
{
  // TODO: should allow the player to fold from left of screen to right if there is no wall at the edges!
  if (rectangle.x < 0 || rectangle.x > (screenWidth_ - rectangle.w) || checkRectangleCollisions(rectangle, walls_))
  {
    return false;
  }
  if (rectangle.y < 0 || rectangle.y > (screenHeight_ - rectangle.h) || checkRectangleCollisions(rectangle, walls_))
  {
    return false;
  }

  return true;
}

void Game::update(bool &running)
{
  if (!pacman_.alive())
  {
    // TODO: go to game over screen
    std::cout << "pacman is dead" << std::endl;
    running = false;
    return;
  }


  moveCharacter<Pacman>(pacman_);

  // TODO: We might parallize this once the move methods become complicated.
  //       However the game loop should complete in 16.67 ms for 60 FPS so the cost of starting a thread
  //       should be worth it, currently I do not think it is necessary to add this complexity
  for (auto &ghost : ghosts_)
  {
    ghost->moveMethod();
    moveCharacter<Ghosts::Ghost>(*ghost);
  }

  handlePacmanDotCollisions(pacman_, dots_);
  if (handlePacmanDotCollisions(pacman_, pellets_))
  {
    if (!scaredGhosts_)
    {
      scaredGhosts_     = true;
      startScaredGhosts = std::chrono::system_clock::now();
    }
  }

  if (scaredGhosts_)
  {
    long timePassedSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startScaredGhosts).count();
    if (timePassedSinceLastUpdate > durationScaredGhosts_)
    {
      scaredGhosts_     = false;
      startScaredGhosts = std::chrono::system_clock::now();
    }
  }

  for (auto &ghost : ghosts_)
  {
    ghost->edible = scaredGhosts_;
    ghost->scared = scaredGhosts_;
  }

  handlePacmanGhostCollisions(pacman_, ghosts_);

  if (dots_.size() == 0 && pellets_.size() == 0)
  {
    // TODO: go to victory screen
    std::cout << "you won! Congratulations" << std::endl;
    running = false;
    return;
  }
}

int Game::score() const
{
  return score_;
}
