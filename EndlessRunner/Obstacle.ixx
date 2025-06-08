/**
 * @file Obstacle.ixx
 * @brief Modu³ definiuj¹cy klasê bazow¹ dla przeszkód w grze.
 *
 * Klasa Obstacle dziedziczy po AnimatedSprite i definiuje wspólne zachowanie dla przeszkód.
 */


module;
#include "raylib.h"
export module ObstacleModule;

import AnimatedSpriteModule;
import ConfigModule;


/**
 * @class Obstacle
 * @brief Klasa bazowa dla przeszkód w grze.
 *
 * Odpowiada za ruch w lewo i jest klas¹ abstrakcyjn¹ dla konkretnych przeszkód (np. Bat, Pterodactyl).
 */
export class Obstacle : public AnimatedSprite {
protected:
    /** @brief Prêdkoœæ przesuwania przeszkody w lewo (piksele/s). */
    float velocity{ -200.f }; // Prêdkoœæ przesuwania w lewo

public:
    Obstacle() = default;
    virtual ~Obstacle() = default;

    /**
     * @brief Inicjalizuje przeszkodê.
     * @param tex Tekstura przeszkody.
     * @param startX Pocz¹tkowa pozycja X.
     * @param startY Pocz¹tkowa pozycja Y.
     * @param scaleFactor Skala przeszkody.
     * @param frameCount Liczba klatek animacji.
     * @param animUpdateTime Czas miêdzy zmianami klatek.
     */
    virtual void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) override {
        AnimatedSprite::init(tex, startX, startY, scaleFactor, frameCount, animUpdateTime);
    }

    /**
    * @brief Aktualizuje stan przeszkody (ruch i animacjê).
    * @param deltaTime Czas od ostatniej klatki (w sekundach).
    */
    virtual void update(float deltaTime) override {
        AnimatedSprite::update(deltaTime);
        screenPos.x += velocity * deltaTime;
    }

    /**
    * @brief Rysuje przeszkodê na ekranie.
    */
    virtual void draw() const override = 0;

    /**
     * @brief Zwraca prostok¹t kolizji przeszkody.
     * @return Prostok¹t kolizji w przestrzeni ekranu.
     */
    virtual Rectangle getCollisionRec() const override = 0;

    /**
     * @brief Zwraca pozycjê X przeszkody.
     * @return Wspó³rzêdna X przeszkody.
     */
    virtual float getPositionX() const { return screenPos.x; }
};