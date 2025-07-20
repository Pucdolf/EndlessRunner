/**
 * @file Player.cpp
 * @brief Implementacja klasy Player.
 */

module;
#include "raylib.h"
#include <iostream>

module PlayerModule;

void Player::init(const Texture2D& dinoTex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) {
	AnimatedSprite::init(dinoTex, startX, startY, scaleFactor, frameCount, animUpdateTime);
	groundLevel = startY - 65.f;
	screenPos.y = groundLevel - height * scale;
	if (texture.id == 0 || texture.width == 0 || texture.height == 0) {
		std::cout << "Error: Invalid texture dimensions!\n";
	}
}

void Player::update(float deltaTime, int windowHeight) {
	groundLevel = windowHeight - 65.f;

	if (isOnGround(windowHeight)) {
		velocity = 0.f;
		isInAir = false;
		jumpCount = 0;
	}
	else {
		velocity += gravity * deltaTime;
		isInAir = true;
	}

	if (IsKeyPressed(KEY_SPACE) && jumpCount < maxJumps) {
		velocity += jumpVelocity;
		jumpCount++;
	}

	screenPos.y += velocity * deltaTime;
	if (screenPos.y > groundLevel - height * scale) {
		screenPos.y = groundLevel - height * scale;
		velocity = 0.f;
		isInAir = false;
		jumpCount = 0;
	}

	if (!isInAir) {
		updateAnimation(deltaTime);
	}

}

bool Player::isOnGround(int windowHeight) const {
	return screenPos.y >= groundLevel - height * scale;
}