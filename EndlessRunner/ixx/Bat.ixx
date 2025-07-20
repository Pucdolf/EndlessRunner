/**
 * @file Bat.ixx
 * @brief Modu³ definiuj¹cy klasê Bat, reprezentuj¹c¹ animowan¹ przeszkodê typu nietoperz.
 *
 * Klasa Bat dziedziczy po Obstacle i specjalizuje zachowanie dla nietoperza.
 */

module;
#include "raylib.h"
export module BatModule;

import ObstacleModule;
import ConfigModule;

/**
 * @class Bat
 * @brief Klasa reprezentuj¹ca przeszkodê typu nietoperz.
 *
 * Nietoperz jest animowan¹ przeszkod¹, która porusza siê w lewo i pojawia siê na okreœlonej wysokoœci.
 */
export class Bat : public Obstacle {
public:

    /**
     * @brief Inicjalizuje nietoperza z podan¹ tekstur¹ i parametrami.
     * @param tex Tekstura nietoperza.
     * @param startX Pocz¹tkowa pozycja X.
     * @param startY Pocz¹tkowa pozycja Y (przesuniêta o 150 pikseli w górê).
     * @param scaleFactor Skala nietoperza.
     * @param frameCount Liczba klatek animacji.
     * @param animUpdateTime Czas miêdzy zmianami klatek.
     */
    void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime = Config::ANIMATION_UPDATE_TIME) override; /*{
        Obstacle::init(tex, startX, startY - 150.f, scaleFactor, frameCount, animUpdateTime);
    }*/


    /**
    * @brief Aktualizuje stan nietoperza.
    * @param deltaTime Czas od ostatniej klatki (w sekundach).
    */
    void update(float deltaTime) override; /*{
        Obstacle::update(deltaTime); 
    }*/


    /**
    * @brief Rysuje nietoperza na ekranie.
    */
    void draw() const override; /*{
        AnimatedSprite::draw();
    }*/

    /**
    * @brief Zwraca prostok¹t kolizji nietoperza.
    * @return Prostok¹t kolizji w przestrzeni ekranu.
    */
    Rectangle getCollisionRec() const override; /*{
        return AnimatedSprite::getCollisionRec();
    }*/
};