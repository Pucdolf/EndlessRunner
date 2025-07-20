/**
 * @file StaticObstacle.cpp
 * @brief Implementacja klasy StaticObstacle.
 */

module;
#include "raylib.h"

module StaticObstacleModule;

void StaticObstacle::init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) {
	Obstacle::init(tex, startX, startY - tex.height * scaleFactor, scaleFactor, 1, animUpdateTime);
}

void StaticObstacle::update(float deltaTime) {
	screenPos.x += velocity * deltaTime;
}

void StaticObstacle::draw() const {
	Rectangle soucre{ 0.f, 0.f, width, height };
	Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
	DrawTexturePro(texture, soucre, dest, { 0.f,0.f }, 0.f, WHITE);
}

Rectangle StaticObstacle::getCollisionRec() const
{
	return Rectangle{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale
	};
}