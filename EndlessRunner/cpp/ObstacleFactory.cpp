/**
 * @file ObstacleFactory.cpp
 * @brief Implementacja klasy ObstacleFactory.
 */

module;
#include "raylib.h"

module ObstacleFactoryModule;
import BatModule;
import PterodactylModule;
import StaticObstacleModule;
import ObstacleModule;
import ConfigModule;
import ResourcesModule;
import <memory>;
import <random>;
import <vector>;


std::unique_ptr<Obstacle> ObstacleFactory::createObstacle(float startX, float startY, BackgroundType bgType) {
    int roll = probabilityDis(gen);

    if (roll > 0 and roll <= 20) {
        return createSpecificObstacle<Bat>(startX, startY, resources.getBat(), Config::BAT_FRAME_COUNT);
    }
    else if (roll > 20 && roll <= 40) {
        return createSpecificObstacle<Pterodactyl>(startX, startY, resources.getPtero(), Config::PTERODACTYL_FRAME_COUNT);
    }
    else {
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
                &resources.getSkulls(),
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