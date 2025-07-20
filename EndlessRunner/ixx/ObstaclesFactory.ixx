/**
 * @file ObstacleFactory.ixx
 * @brief Modu³ definiuj¹cy klasê ObstacleFactory, tworz¹c¹ przeszkody.
 *
 * Klasa ObstacleFactory generuje losowe przeszkody na podstawie typu t³a gry.
 */

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


/**
 * @concept ObstacleType
 * @brief Koncept dla typów przeszkód dziedzicz¹cych po klasie Obstacle.
 *
 * Typy spe³niaj¹ce ten koncept musz¹ dziedziczyæ po Obstacle oraz implementowaæ metody `init`, `update`, `draw` i `getCollisionRec` z okreœlonymi sygnaturami.
 * @tparam T Typ obiektu do sprawdzenia.
 */
export template<typename T>
concept ObstacleType = std::derived_from<T, Obstacle>&& requires(T t, const Texture2D& tex, float x, float y, float scale, int frames, float time) {
    { t.init(tex, x, y, scale, frames, time) } -> std::same_as<void>;
    { t.update(0.0f) } -> std::same_as<void>;
    { t.draw() } -> std::same_as<void>;
    { t.getCollisionRec() } -> std::same_as<Rectangle>;
};

/**
 * @enum BackgroundType
 * @brief Typy t³a gry.
 */
export enum class BackgroundType {
    DESERT_DAY,
    DESERT_NIGHT,
    FOREST_DAY,
    FOREST_NIGHT
};

/**
 * @class ObstacleFactory
 * @brief Klasa odpowiedzialna za tworzenie przeszkód.
 *
 * Generuje losowe przeszkody (Bat, Pterodactyl, StaticObstacle) z uwzglêdnieniem typu t³a.
 */
export class ObstacleFactory {
private:
    /** @brief Referencja do zasobów gry. */
    Resources& resources;
    /** @brief Generator liczb losowych. */
    std::random_device rd;
    /** @brief Silnik losuj¹cy. */
    std::mt19937 gen{ rd() };
    /** @brief Rozk³ad losuj¹cy prawdopodobieñstwo (0-99). */
    std::uniform_int_distribution<> probabilityDis{ 0, 99 };
    /** @brief Rozk³ad losuj¹cy statyczne przeszkody (0-6). */
    std::uniform_int_distribution<> staticDis{ 0, 6 }; 

   
    template<ObstacleType T>
    std::unique_ptr<Obstacle> createSpecificObstacle(float startX, float startY, const Texture2D& tex, int frameCount) {
        auto obstacle = std::make_unique<T>();
        obstacle->init(tex, startX, startY, Config::OBSTACLE_SCALE, frameCount, Config::ANIMATION_UPDATE_TIME);
        return obstacle;
    }

public:
    /**
     * @brief Konstruktor klasy ObstacleFactory.
     * @param res Referencja do zasobów gry.
     */
    ObstacleFactory(Resources& res) : resources(res) {}

    /**
     * @brief Tworzy now¹ przeszkodê.
     * @param startX Pocz¹tkowa pozycja X.
     * @param startY Pocz¹tkowa pozycja Y.
     * @param bgType Typ t³a gry.
     * @return Unikalny wskaŸnik do stworzonej przeszkody.
     */
    std::unique_ptr<Obstacle> createObstacle(float startX, float startY, BackgroundType bgType); /*{
        int roll = probabilityDis(gen); 

        if (roll > 0 and  roll <= 20) { 
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
    }*/
};