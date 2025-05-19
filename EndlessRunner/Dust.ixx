module;
#include "raylib.h"
export module DustModule;

import AnimatedSpriteModule;
import ConfigModule;

export class Dust : public AnimatedSprite {
public:
    void init(const Texture2D& dustTex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) override {
        AnimatedSprite::init(dustTex, startX, startY, scaleFactor, frameCount, animUpdateTime);
    }

    void update(float deltaTime) override {
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

    void draw() const override {
        if (!isActive) return;
        Rectangle source{ frame * width, 0.f, width, height };
        Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
        float alpha = (frame < maxFrames - 1) ? 1.f : 1.f - (runningTime / updateTime);
        Color color{ 255, 255, 255, static_cast<unsigned char>(255 * alpha) };
        DrawTexturePro(texture, source, dest, { 0.f, 0.f }, 0.f, color);
    }
};