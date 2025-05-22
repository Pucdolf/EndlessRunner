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

public:
    ObstacleFactory(Resources& res) : resources(res) {}

    std::unique_ptr<Obstacle> createObstacle(float startX, float startY, BackgroundType bgType) {
        int roll = probabilityDis(gen); // Losowanie liczby z zakresu 0-99

        if (roll < 20) { // 0-19: 20% szansy na Bat
            auto bat = std::make_unique<Bat>();
            bat->init(resources.getBat(), startX, startY, Config::OBSTACLE_SCALE, Config::BAT_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);
            return bat;
        }
        else if (roll < 40) { // 20-39: 20% szansy na Pterodactyl
            auto ptero = std::make_unique<Pterodactyl>();
            ptero->init(resources.getPtero(), startX, startY, Config::OBSTACLE_SCALE, Config::PTERODACTYL_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);
            return ptero;
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

            std::uniform_int_distribution<> dis(0, staticObstacles.size() - 1);
            Texture2D* selectedTex = staticObstacles[dis(gen)];

            auto staticObstacle = std::make_unique<StaticObstacle>();
            staticObstacle->init(*selectedTex, startX, startY, Config::OBSTACLE_SCALE, 1, Config::ANIMATION_UPDATE_TIME);
            return staticObstacle;
        }
    }
};