module;
#include "raylib.h"
#include <concepts> // Dodane dla wsparcia C++20 Concepts
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

// Importujemy definicjê ObstacleType z ObstacleFactoryModule
import ObstacleFactoryModule;

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
    ObstacleFactory obstacleFactory;
    BackgroundType currentBgType;

    // Generyczna metoda do aktualizacji przeszkód
    template<ObstacleType T>
    void updateObstacles(float deltaTime) {
        for (auto& obstacle : obstacles) {
            if constexpr (std::is_base_of_v<Obstacle, T>) {
                obstacle->update(deltaTime);
            }
        }
    }

    // Generyczna metoda do rysowania przeszkód
    template<ObstacleType T>
    void drawObstacles() const {
        for (const auto& obstacle : obstacles) {
            if constexpr (std::is_base_of_v<Obstacle, T>) {
                obstacle->draw();
            }
        }
    }

public:
    Board(Resources& res) : resources(res), obstacleFactory(res) {}

    void setDinoTex(const Texture2D& dinoTex) {
        selectedDinoTex = dinoTex;
    }
    void setDinoFrameCount(int frameCount) {
        selectedDinoFrameCount = frameCount;
    }
    void setBackgroundType(BackgroundType bgType) {
        currentBgType = bgType;
    }

    void init(const Texture2D& dinoTex, int windowWidth, int windowHeight) {
        if (selectedDinoTex.id == 0) {
            selectedDinoTex = dinoTex;
            selectedDinoFrameCount = 6;
        }

        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;

        float playerWidth = (static_cast<float>(selectedDinoTex.width) / selectedDinoFrameCount) * Config::PLAYER_SCALE;
        float startX = (windowWidth - playerWidth) / 2.f;
        player.init(selectedDinoTex, startX, static_cast<float>(windowHeight), Config::PLAYER_SCALE, selectedDinoFrameCount, Config::ANIMATION_UPDATE_TIME);

        dust.init(resources.getDustRun(), 0, 0, Config::OBSTACLE_SCALE, Config::DUST_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);

        lastObstacleX = static_cast<float>(windowWidth);
        obstacles.clear();
        spawnObstacle(windowWidth, windowHeight);
    }

    void update(float deltaTime, int windowHeight) {
        this->windowHeight = windowHeight;
        player.update(deltaTime, windowHeight);
        updateObstacles<Obstacle>(deltaTime); 

        obstacles.erase(
            std::remove_if(obstacles.begin(), obstacles.end(),
                [](const auto& obs) { return obs->getPositionX() < -200.f; }),
            obstacles.end()
        );

        if (obstacles.empty() || obstacles.back()->getPositionX() < lastObstacleX - getRandomDistance()) {
            spawnObstacle(windowWidth, windowHeight);
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
        drawObstacles<Obstacle>(); // Jawne podanie typu
        dust.draw();
        player.draw();
    }

    bool checkLoss() const {
        for (const auto& obstacle : obstacles) {
            if (obstacleCollision(*obstacle, player)) {
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
            float dustY = (windowHeight - 65.f) - (dust.getTexture().height * Config::OBSTACLE_SCALE);
            dust.init(dust.getTexture(), dustX, dustY, Config::OBSTACLE_SCALE, Config::DUST_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);
        }
    }

    void spawnObstacle(int windowWidth, int windowHeight) {
        float startX = lastObstacleX + getRandomDistance();
        float startY = static_cast<float>(windowHeight - 65);
        obstacles.push_back(obstacleFactory.createObstacle(startX, startY, currentBgType));
        lastObstacleX = startX;
    }

    float getRandomDistance() {
        std::uniform_real_distribution<float> dis(minObstacleDistance, maxObstacleDistance);
        return dis(gen);
    }
};