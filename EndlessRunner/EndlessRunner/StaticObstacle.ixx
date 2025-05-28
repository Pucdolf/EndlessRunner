module;
#include "raylib.h"
export module StaticObstacleModule;

import ObstacleModule;
import ConfigModule;

export class StaticObstacle : public Obstacle {
public:
    void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) override {
        Obstacle::init(tex, startX, startY - tex.height * scaleFactor, scaleFactor, 1, animUpdateTime); // Odejmujemy wysokoœæ tekstury
    }

    void update(float deltaTime) override {
        screenPos.x += velocity * deltaTime; // Przesuwanie w lewo
    }

    void draw() const override {
        Rectangle source{ 0.f, 0.f, width, height };
        Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
        DrawTexturePro(texture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    }

    Rectangle getCollisionRec() const override {
        return Rectangle{
            screenPos.x,
            screenPos.y, // Nowa pozycja uwzglêdnia przesuniêcie
            width * scale,
            height * scale
        };
    }
};