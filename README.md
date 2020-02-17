# Pacman

A Pac-Man clone based on SDL.
The project is made as practice in writing C++ code and is created for the 
Capstone project of [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 

The implementation is not (yet) a clone of the original Pac-Man. It misses important functionality.
As example the 4 ghosts now have random movement while they should follow pacman in different ways,
see also [Ghost Movement](https://en.wikipedia.org/wiki/Ghosts_(Pac-Man)).

The game while running should look as follows:

<img src="pacman.gif"/>

Once all the dots & pellets are collected the game closes and prints your score to the console.
If the pacman collides with a ghost it is game over and the window closes. Your score is printed to
the console. Good luck with your new try!

## Repoistory Structure
* All the source & header files can be found in src/
* The levels can be found in levels/

## Code Structure & Objects
* Movement base class for moving entities. The crucial insight is that for continous movement there
  should be two variables: (1) wanted direction and (2) direction (current). The wanted direction is
  checked if possible otherwise entity keeps on moving in direction if possible.
  * Ghost base class for the 4 Ghosts  that inherets from Movement & SDL_FRect
    * Blinky, Clyde, Inky & Pinky inherets from Ghost, overrides moveMethod() for unique behaviour 
      per character. Currently the difference in behaviour is the random generator used.
  * Pacman inherets from Movement & SDL_FRect. Additionaly carries a boolean to state if pacman is
    alive
* Level is responsible from loading in levels from the directory levels/ uses std::filesystem
  (C++17) for this. Currently only default.txt can be read in. But user can modify default.txt.
  The conversion from character to game entities is: 
  1. o = Dot
  2. p = Pellet
  3. P = pacman
  4. = = wall
  5. b = blinky
  6. c = clyde
  7. i = inky
  8. p = pinky
* Game manages the game loop: controller input -> game state update -> render.
  The game state updates handles game logic, it moves the entities, handles collisions & changes
  game state (running).
* Dot a rectangle (could be a SDL_Rect) but for future extensibility it is not yet. I would like it
  to be round, which is not yet implemented.
* Pellet (is a dot) but inside a separate vector from the dots vector such that game state can be updated accordingly.
  Once a pellet is eaten the ghosts become scared & edible.
* Renderer  uses SDL to draw with specified color in code the entities to the screen.
* Controller currently only supports arrow keys on keyboard only. Controls the wanted direction of
  Pacman for moving. Also handles the case the user closes the window.

## Udacity Rubric Points Specifications Met
* The project demonstrates an understanding of C++ functions and control structures.
  Can be seen in all the sources.
* The project reads data from a file and process the data, or the program writes data to a file.
  The program reads data from a file for setting the level entities: see Level::load in level.cpp
* The project accepts user input and processes the input.
  Handled in Controller::handleInput in controller.cpp

* The project uses Object Oriented Programming techniques.
  Can be seen in almost all the sources, e.g. pacman.cpp
* Classes use appropriate access specifiers for class members.
  Can be seen in almost all the sources, e.g. pacman.cpp
* Class constructors utilize member initialization lists.
  Can be seen in multiple places, e.g. pacman.cpp & Ghost.h
* Classes abstract implementation details from their interfaces.
  Achieved by clear naming, see ghost.h members
* Classes encapsulate behavior.
  For example see movement.h
* Classes follow an appropriate inheritance hierarchy.
  For example see blinky.h, pacman.h, ghost.h
* Derived class functions override virtual base class functions.
  See:
  Blinky::moveMethod in blinky.h
  Inky::moveMethod in inky.h
  Pinky::moveMethod in pinky.h
  Clyde::moveMethod in clyde.h
* Templates generalize functions in the project.
  See Game::moveCharacter in game.cpp

* The project makes use of references in function declarations.
  Can be seen in multiple places e.g. 
  Game::moveCharacter in game.cpp
  Game::update in game.cpp
  Level::load in level.cpp
* The project uses destructors appropriately.
  See Renderer::~Renderer in renderer.cpp 
  However there are no other implemented destructors even though we have objects on the heap. 
  unique_ptrs are used for these objects.
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
  See Level::convertCharacterToGameObjects line: 50, 57, 64, 71 i.e. when creating Ghosts in level.cpp
  Scope is managed by the Level object first but are soon moved to Game where Game manages it
* The project uses move semantics to move data, instead of copying it, where possible.
  See Game::Game line: 16-20 in game.cpp. Moving the Level ownership of entities to Game
* The project uses smart pointers instead of raw pointers.
  See Level::convertCharacterToGameObjects line: 50, 57, 64, 71 i.e. when creating Ghosts in level.cpp
  Which is put into a vector that will be moved to Game.
  There is a raw ptr, see Game::handlePacmanGhostCollisions lineve 139 in game.cpp but it is
  non-owning and hence follows core guidelines R.3.


## Notes
* SDL is packaged with the repo so no system SDL should be necessary! (only tested on arch linux)

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./PacmanGame`.
