module;
#include "raylib.h"
export module ObstacleFactoryModule;

import BatModule;
import PterodactylModule;
import StaticObstacleModule;
import ObstacleModule;
import ConfigModule;
import ResourcesModule;
import <memory>;
import <random>;
import <vector>;

// Concept dla typów dziedzicz¹cych po Obstacle
export template<typename T>
concept ObstacleType = std::derived_from<T, Obstacle>&& requires(T t, const Texture2D& tex, float x, float y, float scale, int frames, float time) {
    { t.init(tex, x, y, scale, frames, time) } -> std::same_as<void>;
    { t.update(0.0f) } -> std::same_as<void>;
    { t.draw() } -> std::same_as<void>;
    { t.getCollisionRec() } -> std::same_as<Rectangle>;
};

export enum class BackgroundType {
    DESERT_DAY,
    DESERT_NIGHT,
    FOREST_DAY,
    FOREST_NIGHT
};

export class ObstacleFactory {
private:
    Resources& resources;
    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution<> probabilityDis{ 0, 99 }; // Losowanie z zakresu 0-99 dla procentów
    std::uniform_int_distribution<> staticDis{ 0, 6 }; // Do losowania statycznych przeszkód (maks. 7 opcji)

    // Szablonowa metoda do tworzenia przeszkód
    template<ObstacleType T>
    std::unique_ptr<Obstacle> createSpecificObstacle(float startX, float startY, const Texture2D& tex, int frameCount) {
        auto obstacle = std::make_unique<T>();
        obstacle->init(tex, startX, startY, Config::OBSTACLE_SCALE, frameCount, Config::ANIMATION_UPDATE_TIME);
        return obstacle;
    }

public:
    ObstacleFactory(Resources& res) : resources(res) {}

    std::unique_ptr<Obstacle> createObstacle(float startX, float startY, BackgroundType bgType) {
        int roll = probabilityDis(gen); // Losowanie liczby z zakresu 0-99

        if (roll > 0 and  roll <= 20) { // 0-19: 20% szansy na Bat
            return createSpecificObstacle<Bat>(startX, startY, resources.getBat(), Config::BAT_FRAME_COUNT);
        }
        else if (roll > 20 && roll <= 40) { // 20-39: 20% szansy na Pterodactyl
            return createSpecificObstacle<Pterodactyl>(startX, startY, resources.getPtero(), Config::PTERODACTYL_FRAME_COUNT);
        }
        else { // 40-99: 60% szansy na StaticObstacle
            std::vector<Texture2D*> staticObstacles;
            switch (bgType) {
            case BackgroundType::DESERT_DAY:
                staticObstacles = {
                    &resources.getSmallCactus(),
                    &resources.getBigCactus(),
                    &resources.getSkulls(),
                    &resources.getSkulls2(),
                    &resources.getRockDust(),
                    &resources.getBigRockDust()
                };
                break;
            case BackgroundType::DESERT_NIGHT:
                staticObstacles = {
                    &resources.getSmallCactus(),
                    &resources.getBigCactus(),
                    &resources.getSkulls2(),
                    &resources.getRockDustNight(),
                    &resources.getBigRockDustNight()
                };
                break;
            case BackgroundType::FOREST_DAY:
                staticObstacles = {
                    &resources.getRockForest(),
                    &resources.getBigRockForest(),
                    &resources.getSmallTree(),
                    &resources.getBigTree(),
                    &resources.getLog(),
                    &resources.getSpikes()
                };
                break;
            case BackgroundType::FOREST_NIGHT:
                staticObstacles = {
                    &resources.getRockForest(),
                    &resources.getBigRockForest(),
                    &resources.getSmallTreeNight(),
                    &resources.getBigTreeNight(),
                    &resources.getLogNight(),
                    &resources.getSpikesNight()
                };
                break;
            }

            std::uniform_int_distribution<> dis(0, static_cast<int>(staticObstacles.size() - 1));
            Texture2D* selectedTex = staticObstacles[dis(gen)];

            return createSpecificObstacle<StaticObstacle>(startX, startY, *selectedTex, 1);
        }
    }
};