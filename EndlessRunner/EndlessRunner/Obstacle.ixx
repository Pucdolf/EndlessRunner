module;
#include "raylib.h"
export module ObstacleModule;

import AnimatedSpriteModule;
import ConfigModule;

export class Obstacle : public AnimatedSprite {
protected:
    float velocity{ -200.f }; // Prêdkoœæ przesuwania w lewo

public:
    Obstacle() = default;
    virtual ~Obstacle() = default;

    virtual void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) override {
        AnimatedSprite::init(tex, startX, startY, scaleFactor, frameCount, animUpdateTime);
    }

    virtual void update(float deltaTime) override {
        AnimatedSprite::update(deltaTime);
        screenPos.x += velocity * deltaTime;
    }

    virtual void draw() const override = 0;
    virtual Rectangle getCollisionRec() const override = 0;
    virtual float getPositionX() const { return screenPos.x; }
};