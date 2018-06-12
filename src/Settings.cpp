#include "Settings.h"

bool Settings::runGame = true;
bool Settings::smartPaint = true;
bool Settings::useGrainShader = true;
bool Settings::drawCameraPanRegion = false;
bool Settings::drawEntityOrigins = false;
bool Settings::drawEntityCollisionBounds = false;
bool Settings::drawUI = false;
float Settings::cameraPanRadius = 40;
sf::Vector2f Settings::cameraPanOffset = sf::Vector2f(0,0);
float Settings::gravity = -750;
float Settings::jumpSpeed = 250;
float Settings::walkSpeed = 80;
float Settings::timeScale = 1;