/**
 * @file Pterodactyl.ixx
 * @brief Modu³ definiuj¹cy klasê Pterodactyl, reprezentuj¹c¹ przeszkodê typu pterodaktyl.
 *
 * Klasa Pterodactyl dziedziczy po Obstacle i specjalizuje zachowanie dla pterodaktyla.
 */

module;
#include "raylib.h"
export module PterodactylModule;

import ObstacleModule;
import ConfigModule;

/**
 * @class Pterodactyl
 * @brief Klasa reprezentuj¹ca przeszkodê typu pterodaktyl.
 *
 * Pterodactyl jest animowan¹ przeszkod¹, która porusza siê w lewo i pojawia siê na okreœlonej wysokoœci.
 */
export class Pterodactyl : public Obstacle {
public:
    /**
    * @brief Inicjalizuje pterodaktyla.
    * @param tex Tekstura pterodaktyla.
    * @param startX Pocz¹tkowa pozycja X.
    * @param startY Pocz¹tkowa pozycja Y (przesuniêta o 260 pikseli w górê).
    * @param scaleFactor Skala animacji.
    * @param frameCount Liczba klatek animacji.
    * @param animUpdateTime Czas miêdzy zmianami klatek.
    */
    void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime) override {
        Obstacle::init(tex, startX, startY - 260.f, scaleFactor, frameCount, animUpdateTime);
    }

    /**
     * @brief Aktualizuje stan pterodaktyla.
     * @param deltaTime Czas od ostatniej klatki (w sekundach).
     */
    void update(float deltaTime) override {
        Obstacle::update(deltaTime); // Upewniamy siê, ¿e animacja jest aktualizowana
    }

    /**
     * @brief Rysuje pterodaktyla na ekranie.
     */
    void draw() const override {
        AnimatedSprite::draw();
    }

    /**
    * @brief Zwraca prostok¹t kolizji pterodaktyla.
    * @return Prostok¹t kolizji w przestrzeni ekranu.
    */
    Rectangle getCollisionRec() const override {
        return AnimatedSprite::getCollisionRec();
    }
};