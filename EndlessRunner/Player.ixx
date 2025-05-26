module;
#include "raylib.h"
#include <iostream>
export module PlayerModule;

import AnimatedSpriteModule;
import ConfigModule;

export class Player : public AnimatedSprite {
private:
    float velocity{ 0.f };
    float gravity{ Config::GRAVITY };
    float jumpVelocity{ Config::JUMP_VELOCITY };
    bool isInAir{ false };
    int jumpCount{ 0 };
    const int maxJumps{ Config::MAX_JUMPS };
    float groundLevel{ 0.f }; // Nowe pole do przechowywania poziomu ziemi

public:
    void init(const Texture2D& dinoTex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) override {
        AnimatedSprite::init(dinoTex, startX, startY, scaleFactor, frameCount, animUpdateTime);
        // Poziom ziemi to startY (czyli windowHeight) minus 65 pikseli
        groundLevel = startY - 65.f;
        // Ustawiamy pozycjê Y tak, aby podstawa dinozaura by³a na poziomie groundLevel
        screenPos.y = groundLevel - height * scale;
        if (texture.id == 0 || texture.width == 0 || texture.height == 0) {
            std::cout << "Error: Invalid texture dimensions!\n";
        }
    }

    void update(float deltaTime, int windowHeight) {
        // Uaktualniamy groundLevel na wypadek zmiany wysokoœci okna
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

    bool isOnGround(int windowHeight) const {
        return screenPos.y >= groundLevel - height * scale;
    }
};