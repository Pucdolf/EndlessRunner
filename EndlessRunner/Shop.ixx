/**
 * @file Shop.ixx
 * @brief Modu³ definiuj¹cy klasê Shop, obs³uguj¹c¹ wybór dinozaurów.
 *
 * Klasa Shop pozwala graczowi wybraæ dinozaura do gry.
 */

module;
#include "raylib.h"
#include <array>
#include <string>
export module ShopModule;

import ResourcesModule;
import ConfigModule;


/**
 * @class Shop
 * @brief Klasa obs³uguj¹ca interfejs sklepu w grze.
 *
 * Wyœwietla dostêpne dinozaury i pozwala na ich wybór.
 */
export class Shop
{
private:
    /** @brief Liczba dinozaurów w sklepie. */
    static constexpr int DinoCount{ Config::SHOP_DINO_COUNT }; 
    /** @brief Tekstury dinozaurów. */
    Texture2D dinos[DinoCount];
    /** @brief Prostok¹ty klikalnych obszarów dinozaurów. */
    Rectangle dinoRecs[DinoCount];
    /** @brief Tekstura t³a sklepu. */
    Texture2D background;
    /** @brief Obiekt zasobów gry. */
    Resources resources;
    /** @brief Bazowe skale dla ka¿dego dinozaura. */
    std::array<float, DinoCount> baseScales{ 6.0f, 7.5f, 8.5f, 7.0f };
    /** @brief Szerokoœci klatek animacji dinozaurów. */
    std::array<float, DinoCount> frameWidths;
    /** @brief Wysokoœci klatek animacji dinozaurów. */
    std::array<float, DinoCount> frameHeights;
    /** @brief Liczby klatek animacji dla ka¿dego dinozaura. */
    std::array<int, DinoCount> frameCounts{ 6, 4, 4, 6 };

    /** @brief Aktualna klatka animacji. */
    int frame{ 0 };
    /** @brief Czas od ostatniej zmiany klatki. */
    float runningTime{ 0 };
    /** @brief Czas miêdzy zmianami klatek. */
    float updateTime{ Config::SHOP_ANIMATION_UPDATE_TIME }; 
    /** @brief Indeks wybranego dinozaura. */
    int selectedDinoIndex{ 0 };

    /** @brief Pocz¹tkowa szerokoœæ ekranu (dla skalowania). */
    int initialScreenWidth{ 0 };
    /** @brief Pocz¹tkowa wysokoœæ ekranu (dla skalowania). */
    int initialScreenHeight{ 0 };

public:
    /**
    * @brief Inicjalizuje sklep.
    * @param res Referencja do zasobów gry.
    * @param screenWidth Szerokoœæ ekranu.
    * @param screenHeight Wysokoœæ ekranu.
    */
    void init(Resources& res, int screenWidth, int screenHeight)
    {
        resources = res;
        dinos[0] = resources.getGreenIdle();
        dinos[1] = resources.getBlueIdle();
        dinos[2] = resources.getYellowIdle();
        dinos[3] = resources.getRedIdle();

        initialScreenWidth = screenWidth;
        initialScreenHeight = screenHeight;

        for (int i{ 0 }; i < DinoCount; i++) {
            frameWidths[i] = static_cast<float>(dinos[i].width / 4);
            frameHeights[i] = static_cast<float>(dinos[i].height);
        }
    }

    /**
     * @brief Wyœwietla interfejs sklepu.
     * @param screenWidth Szerokoœæ ekranu.
     * @param screenHeight Wysokoœæ ekranu.
     */
    void show(int screenWidth, int screenHeight) {
        runningTime = 0;
        frame = 0;

        while (!WindowShouldClose()) {
            float deltaTime = GetFrameTime();
            runningTime += deltaTime;
            if (runningTime >= updateTime) {
                runningTime = 0;
                frame++;
                if (frame > 3) frame = 0;
            }

            if (IsKeyPressed(KEY_ESCAPE)) return;
          
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();

            float widthScale = static_cast<float>(screenWidth) / initialScreenWidth;
            float heightScale = static_cast<float>(screenHeight) / initialScreenHeight;

           
            for (int i{ 0 }; i < DinoCount; i++) {
                dinoRecs[i] = Rectangle{
                    static_cast<float>(i * screenWidth / DinoCount),
                    static_cast<float>(screenHeight * 0.65f - 110.f * heightScale),
                    static_cast<float>(screenWidth / DinoCount),
                    220.f * heightScale
                };
            }

            Vector2 mouse = GetMousePosition();
            for (int i{ 0 }; i < DinoCount; i++) {
                if (CheckCollisionPointRec(mouse, dinoRecs[i])) {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        selectedDinoIndex = i;
                    }
                }
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexturePro(
                resources.getShopBackground(),
                Rectangle{ 0, 0, static_cast<float>(resources.getShopBackground().width), static_cast<float>(resources.getShopBackground().height) },
                Rectangle{ 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
                Vector2{ 0, 0 },
                0.0f,
                WHITE
            );

            for (int i = 0; i < DinoCount; i++) {
                float currentScale = baseScales[i] * (widthScale + heightScale) / 2.0f;

                Rectangle dest = {
                    dinoRecs[i].x + (dinoRecs[i].width - frameWidths[i] * currentScale) / 2,
                    screenHeight * 0.85f - frameHeights[i] * currentScale,
                    frameWidths[i] * currentScale,
                    frameHeights[i] * currentScale
                };

                Rectangle source = { frame * frameWidths[i], 0.0f, frameWidths[i], frameHeights[i] };

                DrawTexturePro(dinos[i], source, dest, Vector2{ 0, 0 }, 0.0f, WHITE);

                if (i == selectedDinoIndex) {
                    Rectangle selectionFrame = dinoRecs[i];
                    selectionFrame.y += 50.f * heightScale; // Przesuniêcie w dó³, skalowane
                    DrawRectangleLinesEx(selectionFrame, 4.f * widthScale, GREEN);
                }
            }

            DrawText("Press ESC to return", screenWidth / 2 - MeasureText("Press ESC to return", 20) / 2, screenHeight - 30, 20, BLACK);
            EndDrawing();
        }
    }

    /**
     * @brief Zwraca indeks wybranego dinozaura.
     * @return Indeks wybranego dinozaura.
     */
    int getSelectedDino() const {
        return selectedDinoIndex;
    }


    /**
     * @brief Zwraca liczbê klatek animacji wybranego dinozaura.
     * @return Liczba klatek animacji.
     */
    int getSelectedDinoFrameCount() const {
        return frameCounts[selectedDinoIndex];
    }
};