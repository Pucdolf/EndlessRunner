/**
 * @file Bat.cpp
 * @brief Implementacja klasy Bat.
 */

module;
#include "raylib.h"

module BatModule;

void Bat::init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) {
	Obstacle::init(tex, startX, startY - 150, scaleFactor, frameCount, animUpdateTime);
}

void Bat::update(float deltaTime) {
	Obstacle::update(deltaTime);
}

void Bat::draw() const{
	AnimatedSprite::draw();
}

Rectangle Bat::getCollisionRec() const{
	return AnimatedSprite::getCollisionRec();
}