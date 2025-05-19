module;
#include "raylib.h"
export module AnimatedSpriteModule;

import ConfigModule;

export class AnimatedSprite {
protected:
    Vector2 screenPos{ 0.f, 0.f };
    float scale{ 1.f };

    Texture2D texture{};
    float width{ 0.f };
    float height{ 0.f };

    int frame{ 0 };
    float maxFrames{ 1.f };
    float updateTime{ Config::ANIMATION_UPDATE_TIME }; // Domyœlna wartoœæ z Config
    float runningTime{ 0.f };

    bool isActive{ true };

public:
    AnimatedSprite() = default;
    virtual ~AnimatedSprite() = default;

    /**
     * @brief Inicjalizuje obiekt animowanego sprite'a.
     * @param tex Tekstura sprite'a.
     * @param startX Pocz¹tkowa pozycja X sprite'a.
     * @param startY Pocz¹tkowa pozycja Y sprite'a.
     * @param scaleFactor Wspó³czynnik skali sprite'a.
     * @param frameCount Liczba klatek animacji.
     * @param animUpdateTime Czas miêdzy klatkami animacji (w sekundach).
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
        updateTime = animUpdateTime; // Mo¿liwoœæ nadpisywania czasu animacji
    }

    virtual void update(float deltaTime) {
        if (!isActive) return;
        updateAnimation(deltaTime);
    }

    virtual void draw() const {
        if (!isActive) return;
        Rectangle source{ frame * width, 0.f, width, height };
        Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
        DrawTexturePro(texture, source, dest, { 0.f, 0.f }, 0.f, WHITE);
    }

    virtual Rectangle getCollisionRec() const {
        return Rectangle{
            screenPos.x,
            screenPos.y,
            width * scale,
            height * scale
        };
    }

    Vector2 getPosition() const { return screenPos; }
    bool getIsActive() const { return isActive; }
    const Texture2D& getTexture() const { return texture; }
    int getFrame() const { return frame; }

protected:
    void updateAnimation(float deltaTime) {
        runningTime += deltaTime;
        if (runningTime >= updateTime) {
            runningTime = 0.f;
            frame++;
            if (frame >= maxFrames) frame = 0;
        }
    }

    void setActive(bool active) { isActive = active; }
};