/**
 * @file StaticObstacle.ixx
 * @brief Modu³ definiuj¹cy klasê StaticObstacle, reprezentuj¹c¹ statyczne przeszkody.
 *
 * Klasa StaticObstacle dziedziczy po Obstacle i obs³uguje przeszkody bez animacji.
 */
module;
#include "raylib.h"
export module StaticObstacleModule;

import ObstacleModule;
import ConfigModule;

/**
 * @class StaticObstacle
 * @brief Klasa reprezentuj¹ca statyczn¹ przeszkodê w grze.
 *
 * Przeszkody statyczne (np. kaktusy, drzewa) poruszaj¹ siê w lewo bez animacji.
 */
export class StaticObstacle : public Obstacle {
public:

    /**
     * @brief Inicjalizuje statyczn¹ przeszkodê.
     * @param tex Tekstura przeszkody.
     * @param startX Pocz¹tkowa pozycja X.
     * @param startY Pocz¹tkowa pozycja Y (przesuniêta w górê o wysokoœæ tekstury).
     * @param scaleFactor Skala przeszkody.
     * @param frameCount Liczba klatek (zawsze 1 dla statycznych).
     * @param animUpdateTime Czas miêdzy zmianami klatek (nieu¿ywany).
     */
    void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime = Config::ANIMATION_UPDATE_TIME) override;/* {
        Obstacle::init(tex, startX, startY - tex.height * scaleFactor, scaleFactor, 1, animUpdateTime); 
    }*/

    /**
     * @brief Aktualizuje pozycjê przeszkody.
     * @param deltaTime Czas od ostatniej klatki (w sekundach).
     */
    void update(float deltaTime) override; /*{
        screenPos.x += velocity * deltaTime; 
    }*/


    /**
    * @brief Rysuje przeszkodê na ekranie.
    */
    void draw() const override;/* {
        Rectangle source{ 0.f, 0.f, width, height };
        Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
        DrawTexturePro(texture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    }*/


    /**
    * @brief Zwraca prostok¹t kolizji przeszkody.
    * @return Prostok¹t kolizji w przestrzeni ekranu.
    */
    Rectangle getCollisionRec() const override;/* {
        return Rectangle{
            screenPos.x,
            screenPos.y,
            width * scale,
            height * scale
        };
    }*/
};