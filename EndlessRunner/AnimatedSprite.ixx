module;
#include "raylib.h"
#include <iostream>
export module AnimatedSpriteModule;

import ConfigModule;

export class AnimatedSprite {
protected:
    Vector2 screenPos{ 0.f, 0.f };
    float scale{ 1.f };

    Texture2D texture{};
    float width{ 0.f };
    float height{ 0.f };

    int frame{ 0 };
    float maxFrames{ 1.f };
    float updateTime{ Config::ANIMATION_UPDATE_TIME };
    float runningTime{ 0.f };

    bool isActive{ true };

public:
    AnimatedSprite() = default;
    virtual ~AnimatedSprite() = default;

    virtual void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime = Config::ANIMATION_UPDATE_TIME) {
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
        std::cout << "AnimatedSprite initialized: Width per frame: " << width << ", Height: " << height
            << ", Frame count: " << maxFrames << "\n";
    }

    virtual void update(float deltaTime) {
        if (!isActive) return;
        updateAnimation(deltaTime);
    }

    virtual void draw() const {
        if (!isActive) return;
        Rectangle source{ frame * width, 0.f, width, height };
        Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
        std::cout << "Drawing frame: " << frame << " of " << maxFrames
            << ", Source X: " << frame * width << ", Source Width: " << width
            << ", Dest X: " << screenPos.x << ", Dest Y: " << screenPos.y << "\n";
        DrawTexturePro(texture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    }

    virtual Rectangle getCollisionRec() const {
        return Rectangle{
            screenPos.x,
            screenPos.y,
            width * scale,
            height * scale
        };
    }

    Vector2 getPosition() const { return screenPos; }
    bool getIsActive() const { return isActive; }
    const Texture2D& getTexture() const { return texture; }
    int getFrame() const { return frame; }

protected:
    void updateAnimation(float deltaTime) {
        runningTime += deltaTime;
        if (runningTime >= updateTime) {
            runningTime = 0.f;
            frame++;
            if (frame >= maxFrames) frame = 0;
            std::cout << "Updated animation: Frame: " << frame << " of " << maxFrames << "\n";
        }
    }

    void setActive(bool active) { isActive = active; }
};