/**
 * @file Player.ixx
 * @brief Moduł definiujący klasę Player, reprezentującą gracza.
 *
 * Klasa Player dziedziczy po AnimatedSprite i obsługuje ruch, skakanie i grawitację gracza.
 */

module;
#include "raylib.h"
#include <iostream>
export module PlayerModule;

import AnimatedSpriteModule;
import ConfigModule;


/**
 * @class Player
 * @brief Klasa reprezentująca gracza w grze.
 *
 * Odpowiada za obsługę skakania, graw i animacji dinozaura.
 */
export class Player : public AnimatedSprite {
private:
    /** @brief Prędkość pionowa gracza (piksele/s). */
    float velocity{ 0.f };
    /** @brief Przyspieszenie grawitacyjne (piksele/s²). */
    float gravity{ Config::GRAVITY };
    /** @brief Początkowa prędkość skoku (piksele/s). */
    float jumpVelocity{ Config::JUMP_VELOCITY };
    /** @brief Flaga, czy gracz jest w powietrzu. */
    bool isInAir{ false };
    /** @brief Liczba wykonanych skoków. */
    int jumpCount{ 0 };
    /** @brief Maksymalna liczba skoków (podwójny skok). */
    const int maxJumps{ Config::MAX_JUMPS };
    /** @brief Poziom ziemi (pozycja Y podstawy). */
    float groundLevel{ 0.f };

public:
    /**
    * @brief Inicjalizuje gracza.
    * @param dinoTex Tekstura dinozaura.
    * @param startX Początkowa pozycja X.
    * @param startY Początkowa pozycja Y (wysokość okna).
    * @param scaleFactor Skala animacji.
    * @param frameCount Liczba klatek animacji.
    * @param animUpdateTime Czas między zmianami klatek.
    */
    void init(const Texture2D& dinoTex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime = Config::ANIMATION_UPDATE_TIME) override; /*{
        AnimatedSprite::init(dinoTex, startX, startY, scaleFactor, frameCount, animUpdateTime);
        groundLevel = startY - 65.f;
        screenPos.y = groundLevel - height * scale;
        if (texture.id == 0 || texture.width == 0 || texture.height == 0) {
            std::cout << "Error: Invalid texture dimensions!\n";
        }
    }*/

    /**
     * @brief Aktualizuje stan gracza (ruch, skakanie, animacja).
     * @param deltaTime Czas od ostatniej klatki (w sekundach).
     * @param windowHeight Wysokość okna gry.
     */
    void update(float deltaTime, int windowHeight); /*{
        groundLevel = windowHeight - 65.f;

        if (isOnGround(windowHeight)) {
            velocity = 0.f;
            isInAir = false;
            jumpCount = 0;
        }
        else {
            velocity += gravity * deltaTime;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && jumpCount < maxJumps) {
            velocity += jumpVelocity;
            jumpCount++;
        }

        screenPos.y += velocity * deltaTime;
        if (screenPos.y > groundLevel - height * scale) {
            screenPos.y = groundLevel - height * scale;
            velocity = 0.f;
            isInAir = false;
            jumpCount = 0;
        }

        if (!isInAir) {
            updateAnimation(deltaTime);
        }
    }*/

    /**
    * @brief Sprawdza, czy gracz jest na ziemi.
    * @param windowHeight Wysokość okna gry.
    * @return True, jeśli gracz znajduje się na ziemi.
    */
    bool isOnGround(int windowHeight) const; /*{
        return screenPos.y >= groundLevel - height * scale;
    }*/
};