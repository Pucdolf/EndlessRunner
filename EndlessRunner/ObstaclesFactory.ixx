module;
#include "raylib.h"
export module ObstacleFactoryModule;

import BatModule;
import PterodactylModule;
import ObstacleModule;
import ConfigModule;
import <memory>;
import <random>;

export class ObstacleFactory {
private:
    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution<> dis{ 0, 1 };

public:
    std::unique_ptr<Obstacle> createObstacle(const Texture2D& batTex, const Texture2D& pteroTex, float startX, float startY) {
        if (dis(gen) == 0) {
            auto bat = std::make_unique<Bat>();
            bat->init(batTex, startX, startY, Config::OBSTACLE_SCALE, Config::BAT_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);
            return bat;
        }
        else {
            auto ptero = std::make_unique<Pterodactyl>();
            ptero->init(pteroTex, startX, startY, Config::OBSTACLE_SCALE, Config::PTERODACTYL_FRAME_COUNT, Config::ANIMATION_UPDATE_TIME);
            return ptero;
        }
    }
};