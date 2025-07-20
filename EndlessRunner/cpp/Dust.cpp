/**
 * @file Dust.cpp
 * @brief Implementacja klasy Dust.
 */

module;
#include "raylib.h"

module DustModule;

void Dust::init(const Texture2D& dustTex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) {
	AnimatedSprite::init(dustTex, startX, startY, scaleFactor, frameCount, animUpdateTime);
}

void Dust::update(float deltaTime) {
	if (!isActive) return;
	runningTime += deltaTime;
	if (runningTime >= updateTime) {
		runningTime = 0.f;
		frame++;
		if (frame >= maxFrames) {
			isActive = false;
			frame = static_cast<int>(maxFrames) - 1;
		}
	}
}

void Dust::draw() const {
	if (!isActive) return;
	Rectangle source{ frame * width, 0.f, width, height };
	Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
	float alpha = (frame < maxFrames - 1) ? 1.f : 1.f - (runningTime / updateTime);
	Color color{ 255,255,255,static_cast<unsigned char>(255 * alpha) };
	DrawTexturePro(texture, source, dest, { 0.f, 0.f }, 0.f, color);
}