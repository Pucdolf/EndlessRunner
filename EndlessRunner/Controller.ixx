module;
#include "raylib.h"
export module ControllerModule;

import BoardModule;
import ResourcesModule;
import <string>;
import <fstream>;

export class Controller {
private:
    Resources& resources;
    Board& board;
    std::string username;
    int windowWidth{};
    int windowHeight{};
    float scale = 3.0f;

    float bgX{}, mgX{}, fgX{};
    bool gameOver{ false };
    int lives = 3;
    float score = 0.0f;
    bool savedScore{ false };

    void saveScore() {
        if (username.empty() || savedScore) return;
        std::ofstream file("scores.txt", std::ios::app);
        if (file.is_open()) {
            file << username << ":" << static_cast<int>(score) << "\n";
            file.close();
            savedScore = true;
        }
    }

public:
    Controller(Resources& res, Board& b, const std::string& user, int width, int height)
        : resources(res), board(b), username(user), windowWidth(width), windowHeight(height) {
    }

    void run() {
        board.init(resources.getGreenDinoRun(), resources.getNebula(), resources.getDustRun(), windowWidth, windowHeight);

        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            float dt = GetFrameTime();

            BeginDrawing();
            ClearBackground(WHITE);

            scrollBackground(dt, GetScreenWidth(), GetScreenHeight());

            if (!gameOver) {
                board.update(dt, windowHeight);
                gameOver = board.checkLoss();
            }
            if (gameOver) {
                DrawText("Game Over!", windowWidth / 2 - MeasureText("Game Over!", 40)/2, windowHeight / 2, 40, RED);
                if (!savedScore)
                    saveScore();
                if (IsKeyPressed(KEY_ENTER))
                    break;
            }
            else if (board.checkWin()) {
                DrawText("You Win!", windowWidth / 2 - MeasureText("You Win!", 40) / 2, windowHeight / 2, 40, GREEN);
                if (!savedScore)
                    saveScore();
                if (IsKeyPressed(KEY_ENTER))
                    break;
            }
            else {
                score += dt;
                board.draw(resources.getNebula());
            }

            drawUI();

            EndDrawing();
        }
    }

private:
    void scrollBackground(float dt, int windowWidth, int windowHeight) {
        Texture2D background = resources.getGameBackground();
        Texture2D midground = resources.getGameMidground();
        Texture2D foreground = resources.getGameForeground();

        float scale = static_cast<float>(windowHeight) / background.height;
        float scaledWidth = background.width * scale;

        // Foreground texture requires special handling due to transparency and content width
        float fgScaledWidth = foreground.width * scale;
        // Estimate the effective content width of foreground (street portion)
        // Based on visual inspection, the street content is roughly 75% of the texture width
        float fgEffectiveWidth = fgScaledWidth * 0.75f;

        // Update positions for scrolling
        bgX -= 20 * dt;  // Background scrolls at 20 units/sec
        mgX -= 40 * dt;  // Midground scrolls at 40 units/sec
        fgX -= 60 * dt;  // Foreground scrolls at 60 units/sec

        // Reset positions when they go off-screen
        if (bgX <= -scaledWidth) bgX += scaledWidth;
        if (mgX <= -scaledWidth) mgX += scaledWidth;
        if (fgX <= -fgEffectiveWidth) fgX += fgEffectiveWidth;

        // Draw background and midground layers (tileable)
        auto drawTileableLayer = [&](Texture2D texture, float xPos) {
            int numInstances = static_cast<int>(windowWidth / scaledWidth) + 2;
            for (int i = 0; i < numInstances; ++i) {
                float drawX = xPos + i * scaledWidth;
                if (drawX < -scaledWidth || drawX > windowWidth) continue;
                DrawTextureEx(texture, { drawX, 0 }, 0.0f, scale, WHITE);
            }
            };

        // Draw foreground layer with adjusted tiling to minimize gaps
        auto drawForegroundLayer = [&](Texture2D texture, float xPos) {
            int numInstances = static_cast<int>(windowWidth / fgEffectiveWidth) + 2;
            for (int i = 0; i < numInstances; ++i) {
                float drawX = xPos + i * fgEffectiveWidth;
                if (drawX < -fgScaledWidth || drawX > windowWidth) continue;
                DrawTextureEx(texture, { drawX, 0 }, 0.0f, scale, WHITE);
            }
            };

        drawTileableLayer(background, bgX);
        drawTileableLayer(midground, mgX);
        drawForegroundLayer(foreground, fgX);
    }

    void drawUI() {
        Texture2D lifeFull = resources.getHeartIcon();
        Texture2D lifeEmpty = resources.getLifeLostIcon();
        for (int i = 0; i < 3; i++) {
            Texture2D icon = (i < lives) ? lifeFull : lifeEmpty;
            float x = 10 + i * (icon.width * scale + 5);
            float y = 10;
            DrawTextureEx(icon, { x, y }, 0.f, scale, WHITE);
        }

        Texture2D numbers = resources.getNumbersTexture();
        int s = static_cast<int>(score);
        std::string scoreText = std::to_string(s);

        int digitWidth = numbers.width / 10;
        int digitHeight = numbers.height;

        float scaledWidth = digitWidth * scale;
        float totalWidth = scaledWidth * scoreText.length();
        windowWidth = GetScreenWidth();

        for (int i = 0; i < scoreText.length(); ++i) {
            int digit = scoreText[i] - '0';
            Rectangle src = { static_cast<float>(digit * digitWidth), 0, static_cast<float>(digitWidth), static_cast<float>(digitHeight) };
            Rectangle dest = {
                static_cast<float>(windowWidth - totalWidth - 10 + i * scaledWidth),
                10.0f,
                static_cast<float>(scaledWidth),
                static_cast<float>(digitHeight * scale)
            };
            DrawTexturePro(numbers, src, dest, { 0, 0 }, 0.0f, WHITE);
        }
    }
};