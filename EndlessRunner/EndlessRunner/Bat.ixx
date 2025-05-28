// Bat.ixx
module;
#include "raylib.h"
export module BatModule;

import ObstacleModule;
import ConfigModule;

export class Bat : public Obstacle {
public:
    void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) override {
        Obstacle::init(tex, startX, startY - 150.f, scaleFactor, frameCount, animUpdateTime);
    }

    void update(float deltaTime) override {
        Obstacle::update(deltaTime); // Upewniamy siê, ¿e animacja jest aktualizowana
    }

    void draw() const override {
        AnimatedSprite::draw();
    }

    Rectangle getCollisionRec() const override {
        return AnimatedSprite::getCollisionRec();
    }
};