/**
 * @file AnimatedSprite.ixx
 * @brief Modu³ definiuj¹cy klasê bazow¹ dla animowanych sprite'ów w grze.
 *
 * Zawiera klasê AnimatedSprite, która zarz¹dza animacj¹, pozycj¹ i renderowaniem sprite'ów.
 * Jest klas¹ bazow¹ dla gracza, przeszkód i efektów wizualnych (np. py³u).
 */

module;
#include "raylib.h"
#include <iostream>
export module AnimatedSpriteModule;

import ConfigModule;

/**
 * @class AnimatedSprite
 * @brief Klasa bazowa dla animowanych sprite'ów w grze.
 *
 * Odpowiada za zarz¹dzanie pozycj¹, skal¹, animacj¹ i renderowaniem sprite'ów.
 * Klasa jest abstrakcyjna i wymaga nadpisywania metod wirtualnych w klasach pochodnych.
 */
export class AnimatedSprite {
protected:
    /** @brief Pozycja sprite'a na ekranie (w pikselach). */
    Vector2 screenPos{ 0.f, 0.f };
    /** @brief Skala sprite'a (mno¿nik rozmiaru). */
    float scale{ 1.f };

    /** @brief Tekstura sprite'a. */
    Texture2D texture{};
    /** @brief Szerokoœæ pojedynczej klatki animacji (w pikselach). */
    float width{ 0.f };
    /** @brief Wysokoœæ sprite'a (w pikselach). */
    float height{ 0.f };

    /** @brief Aktualna klatka animacji (indeks). */
    int frame{ 0 };
    /** @brief Maksymalna liczba klatek w animacji. */
    float maxFrames{ 1.f };
    /** @brief Czas miêdzy zmianami klatek animacji (w sekundach). */
    float updateTime{ Config::ANIMATION_UPDATE_TIME };
    /** @brief Czas od ostatniej zmiany klatki (w sekundach). */
    float runningTime{ 0.f };

    /** @brief Flaga okreœlaj¹ca, czy sprite jest aktywny (widoczny i aktualizowany). */
    bool isActive{ true };

public:
    AnimatedSprite() = default;
    virtual ~AnimatedSprite() = default;

    /**
    * @brief Inicjalizuje sprite'a z podan¹ tekstur¹ i parametrami.
    * @param tex Tekstura sprite'a.
    * @param startX Pocz¹tkowa pozycja X na ekranie.
    * @param startY Pocz¹tkowa pozycja Y na ekranie.
    * @param scaleFactor Skala sprite'a.
    * @param frameCount Liczba klatek w animacji.
    * @param animUpdateTime Czas miêdzy zmianami klatek (domyœlnie Config::ANIMATION_UPDATE_TIME).
    */
    virtual void init(const Texture2D& tex, float startX, float startY, float scaleFactor, int frameCount, float animUpdateTime = Config::ANIMATION_UPDATE_TIME) {
        texture = tex;
        maxFrames = static_cast<float>(frameCount);
        width = static_cast<float>(tex.width) / maxFrames;
        height = static_cast<float>(tex.height);
        screenPos = { startX, startY };
        scale = scaleFactor;
        frame = 0;
        runningTime = 0.f;
        isActive = true;
        updateTime = animUpdateTime;
    
    }

    /**
     * @brief Aktualizuje stan sprite'a (np. animacjê).
     * @param deltaTime Czas od ostatniej klatki (w sekundach).
     */
    virtual void update(float deltaTime) {
        if (!isActive) return;
        updateAnimation(deltaTime);
    }

    /**
    * @brief Rysuje sprite'a na ekranie.
    */
    virtual void draw() const {
        if (!isActive) return;
        Rectangle source{ frame * width, 0.f, width, height };
        Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
        DrawTexturePro(texture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    }

    /**
     * @brief Zwraca prostok¹t kolizji sprite'a.
     * @return Prostok¹t kolizji w przestrzeni ekranu.
     */
    virtual Rectangle getCollisionRec() const {
        return Rectangle{
            screenPos.x,
            screenPos.y,
            width * scale,
            height * scale
        };
    }

    /**
    * @brief Zwraca aktualn¹ pozycjê sprite'a.
    * @return Wektor z wspó³rzêdnymi X i Y.
    */
    Vector2 getPosition() const { return screenPos; }

    /**
     * @brief Sprawdza, czy sprite jest aktywny.
     * @return True, jeœli sprite jest aktywny.
     */
    bool getIsActive() const { return isActive; }

    /**
    * @brief Zwraca teksturê sprite'a.
    * @return Referencja do tekstury.
    */
    const Texture2D& getTexture() const { return texture; }

    /**
    * @brief Zwraca aktualn¹ klatkê animacji.
    * @return Indeks aktualnej klatki.
    */
    int getFrame() const { return frame; }

protected:
    /**
     * @brief Aktualizuje animacjê sprite'a.
     * @param deltaTime Czas od ostatniej klatki (w sekundach).
     */
    void updateAnimation(float deltaTime) {
        runningTime += deltaTime;
        if (runningTime >= updateTime) {
            runningTime = 0.f;
            frame++;
            if (frame >= maxFrames) frame = 0;
        }
    }

    /**
    * @brief Ustawia aktywnoœæ sprite'a.
    * @param active True, aby aktywowaæ sprite; false, aby dezaktywowaæ.
    */
    void setActive(bool active) { isActive = active; }
};