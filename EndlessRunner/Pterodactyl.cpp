/**
 * @file Pterodactyl.cpp
 * @brief Implementacja klasy Pterodacyl.
 */

module;
#include "raylib.h"

module PterodactylModule;

void Pterodactyl::init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) {
	Obstacle::init(tex, startX, startY - 260.f, scaleFactor, frameCount, animUpdateTime);
}

void Pterodactyl::update(float deltaTime) {
	Obstacle::update(deltaTime);
}

void Pterodactyl::draw() const {
	AnimatedSprite::draw();
}

Rectangle Pterodactyl::getCollisionRec() const {
	return AnimatedSprite::getCollisionRec();
}