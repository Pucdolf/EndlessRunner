module;
#include "raylib.h"
#include <string>

export module MenuModule;

import ResourcesModule;
import BoardModule;
import ControllerModule;
import ShopModule;

import <array>;

export class Menu {
private:
    static constexpr int buttonCount = 5;
    std::array<const char*, buttonCount> labels = { "Start Game", "Leaderboard", "Shop", "Options", "Exit" };
    std::array<Rectangle, buttonCount> buttons;
    int selected = -1;
    std::string username;

    Resources* resources{ nullptr };
    Board* board{ nullptr };
    Shop* shop{ nullptr };

public:
    void setContext(Resources& res, Board& b, Shop& s) {
        resources = &res;
        board = &b;
        shop = &s;
    }

    void setUsername(const std::string& user) {
        username = user;
    }

    void showMenu(int screenWidth, int screenHeight) {
        bool menuRunning = true;

        while (!WindowShouldClose() && menuRunning) {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();

            for (int i = 0; i < buttonCount; ++i) {
                buttons[i] = {
                    static_cast<float>(screenWidth / 2 - 100),
                    static_cast<float>(screenHeight / 2 - ((buttonCount * 80) / 2) + i * 80),
                    200.0f,
                    60.0f
                };
            }

            Vector2 mouse = GetMousePosition();
            selected = -1;
            for (int i = 0; i < buttonCount; ++i) {
                if (CheckCollisionPointRec(mouse, buttons[i])) {
                    selected = i;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        handleClick(i, menuRunning);
                    }
                }
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexturePro(
                resources->getMenuBackground(),
                Rectangle{ 0,0, static_cast<float>(resources->getMenuBackground().width), static_cast<float>(resources->getMenuBackground().height) },
                Rectangle{ 0,0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
                Vector2{ 0,0 },
                0.0f,
                WHITE
            );

            std::string welcomeText = username.empty() ? "Welcome Guest" : "Welcome " + username;
            DrawText(welcomeText.c_str(), screenWidth / 2 - MeasureText(welcomeText.c_str(), 40) / 2, 50, 40, BLACK);

            int fontSize = 20;
            for (int i = 0; i < buttonCount; ++i) {
                Color color = (i == selected) ? GRAY : LIGHTGRAY;
                DrawRectangleRec(buttons[i], color);
                int textWidth = MeasureText(labels[i], fontSize);
                int textX = static_cast<int>(buttons[i].x + (buttons[i].width - textWidth) / 2);
                int textY = static_cast<int>(buttons[i].y + (buttons[i].height - fontSize) / 2);
                DrawText(labels[i], textX, textY, fontSize, BLACK);
            }

            EndDrawing();
        }
    }

private:
    void newGame() {
        if (resources && board) {
            int selectedDino = shop->getSelectedDino();
            int frameCount = shop->getSelectedDinoFrameCount();

            Texture2D selectedDinoTex;
            switch (selectedDino)
            {
            case 0:
                selectedDinoTex = resources->getGreenDinoRun();  break;
            case 1:
                selectedDinoTex = resources->getBlueDinoRun(); break;
            case 2:
                selectedDinoTex = resources->getYellowDinoRun(); break;
            case 3:
                selectedDinoTex = resources->getRedDinoRun(); break;
            default:
                selectedDinoTex = resources->getGreenDinoRun();  break;
            }

            board->setDinoTex(selectedDinoTex);
            board->setDinoFrameCount(frameCount);
            Controller controller(*resources, *board, GetScreenWidth(), GetScreenHeight());
            controller.run();
        }
    }

    void showOptions() {
        // to do
    }

    void openShop() {
        if (shop && resources) {
            shop->show(GetScreenWidth(), GetScreenHeight());
        }
    }

    void exitGame(bool& menuRunning) const {
        resources->unloadTextures(); // Najpierw zwalniamy zasoby
        CloseWindow();              // Potem zamykamy okno
        menuRunning = false;        // Ustawiamy flagê, aby przerwaæ pêtlê
    }

    void handleClick(int index, bool& menuRunning) {
        switch (index) {
        case 0: newGame(); break;
        case 1: showOptions(); break;
        case 2: openShop(); break;
        case 3: showOptions(); break; // placeholder
        case 4: exitGame(menuRunning); break;
        }
    }
};