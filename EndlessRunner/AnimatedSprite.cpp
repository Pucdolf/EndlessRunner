/**
 * @file AnimatedSprite.cpp
 * @brief Implementacja klasy AnimatedSprite.
 */

module;
#include "raylib.h"

module AnimatedSpriteModule;

void AnimatedSprite::init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) {
	texture = tex;
	maxFrames = static_cast<float>(frameCount);
	width = static_cast<float>(tex.width) / maxFrames;
	height = static_cast<float>(tex.height);
	screenPos = { startX, startY };
	scale = scaleFactor;
	frame = 0;
	runningTime = 0.f;
	isActive = true;
	updateTime = animUpdateTime;
}

void AnimatedSprite::update(float deltaTime) {
	if (!isActive) return;
	updateAnimation(deltaTime);
}

void AnimatedSprite::draw() const {
	if (!isActive) return;
	Rectangle source{ frame * width, 0.f, width, height };
	Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
	DrawTexturePro(texture, source, dest, { 0.f, 0.f }, 0.f, WHITE);

}

Rectangle AnimatedSprite::getCollisionRec() const {
	return Rectangle{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale
	};
}

Vector2 AnimatedSprite::getPosition() const {
	return screenPos; 
}

bool AnimatedSprite::getIsActive() const { 
	return isActive; 
}

const Texture2D& AnimatedSprite::getTexture() const { 
	return texture; 
}

int AnimatedSprite::getFrame() const { 
	return frame; 
}

void AnimatedSprite::updateAnimation(float deltaTime) {
	runningTime += deltaTime;
	if (runningTime >= updateTime) {
		runningTime = 0.f;
		frame++;
		if (frame >= maxFrames) frame = 0;
	}
}

void AnimatedSprite::setActive(bool active) { 
	isActive = active; 
}

