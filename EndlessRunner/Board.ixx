module;
#include "raylib.h"
export module BoardModule;

import <array>;
import <vector>;
import <memory>;
import <random>;
import PlayerModule;
import DustModule;
import BatModule;
import PterodactylModule;
import ResourcesModule;
import CollisionHandlingModule;
import ObstacleModule;
import ObstacleFactoryModule;
import ConfigModule;

export class Board {
private:
    Player player{};
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    float lastObstacleX{ 0.f };
    float minObstacleDistance{ Config::MIN_OBSTACLE_DISTANCE };
    float maxObstacleDistance{ Config::MAX_OBSTACLE_DISTANCE };

    Texture2D selectedDinoTex{};
    int selectedDinoFrameCount{ 6 };

    Dust dust{};
    float dustSpawnTimer{ 0.0f };
    float dustSpawnInterval{ Config::DUST_SPAWN_INTERVAL };

    std::random_device rd;
    std::mt19937 gen{ rd() };

    int windowWidth{};
    int windowHeight{};

    Resources& resources;
    ObstacleFactory obstacleFactory{};

public:
    Board(Resources& res) : resources(res) {}

    void setDinoTex(const Texture2D& dinoTex) {
        selectedDinoTex = dinoTex;
    }
    void setDinoFrameCount(int frameCount) {
        selectedDinoFrameCount = frameCount;
    }

    void init(const Texture2D& dinoTex, const Texture2D& batTex, const Texture2D& pteroTex, const Texture2D& dustTex, int windowWidth, int windowHeight) {
        if (selectedDinoTex.id == 0) {
            selectedDinoTex = dinoTex;
            selectedDinoFrameCount = 6;
        }

        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;

        float playerWidth = (static_cast<float>(selectedDinoTex.width) / selectedDinoFrameCount) * Config::PLAYER_SCALE;
        float startX = (windowWidth - playerWidth) / 2.f;
        player.init(selectedDinoTex, startX, windowHeight, Config::PLAYER_SCALE, selectedDinoFrameCount, Config::ANIMATION_UPDATE_TIME);

        dust.init(dustTex, 0, 0, Config::OBSTACLE_SCALE, Config::DUST_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);

        lastObstacleX = static_cast<float>(windowWidth);
        obstacles.clear();
        spawnObstacle(batTex, pteroTex, windowWidth, windowHeight);
    }

    void update(float deltaTime, int windowHeight) {
        player.update(deltaTime, windowHeight);
        for (auto& obstacle : obstacles) {
            obstacle->update(deltaTime);
        }

        obstacles.erase(
            std::remove_if(obstacles.begin(), obstacles.end(),
                [](const auto& obs) { return obs->getPositionX() < -100.f; }),
            obstacles.end()
        );

        if (obstacles.empty() || obstacles.back()->getPositionX() < lastObstacleX - getRandomDistance()) {
            spawnObstacle(resources.getBat(), resources.getPtero(), windowWidth, windowHeight);
        }

        dust.update(deltaTime);

        if (player.isOnGround(windowHeight)) {
            dustSpawnTimer += deltaTime;
            if (dustSpawnTimer >= dustSpawnInterval) {
                spawnDust();
                dustSpawnTimer = 0.f;
            }
        }
    }

    void draw() const {
        for (const auto& obstacle : obstacles) {
            obstacle->draw();
        }
        dust.draw();
        player.draw();
    }

    bool checkLoss() const {
        for (const auto& obstacle : obstacles) {
            if (obstacleCollision(obstacle->getCollisionRec(), player.getCollisionRec())) {
                return true;
            }
        }
        return false;
    }

    const Player& getPlayer() const { return player; }

private:
    void spawnDust() {
        if (!dust.getIsActive()) {
            Vector2 playerPos = player.getPosition();
            float dustX = playerPos.x - 20;
            float dustY = playerPos.y + player.getCollisionRec().height - 50;
            dust.init(dust.getTexture(), dustX, dustY, Config::OBSTACLE_SCALE, Config::DUST_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);
        }
    }

    void spawnObstacle(const Texture2D& batTex, const Texture2D& pteroTex, int windowWidth, int windowHeight) {
        float startX = lastObstacleX + getRandomDistance();
        float startY = static_cast<float>(windowHeight);
        obstacles.push_back(obstacleFactory.createObstacle(batTex, pteroTex, startX, startY));
        lastObstacleX = startX;
    }

    float getRandomDistance() {
        std::uniform_real_distribution<float> dis(minObstacleDistance, maxObstacleDistance);
        return dis(gen);
    }
};