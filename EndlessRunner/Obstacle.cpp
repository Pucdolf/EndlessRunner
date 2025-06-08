/**
 * @file Obstacle.cpp
 * @brief Implementacja klasy Obstacle.
 */


module;
#include "raylib.h"

module ObstacleModule;
import AnimatedSpriteModule;

void Obstacle::init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) {
	AnimatedSprite::init(tex, startX, startY, scaleFactor, frameCount, animUpdateTime);
}

void Obstacle::update(float deltaTime){
	AnimatedSprite::update(deltaTime);
	screenPos.x += velocity * deltaTime;
}

float Obstacle::getPositionX() const{
	return screenPos.x;
}