#include "raylib.h"
export module MenuModule;

import LoadingScreenModule;
import ResourcesModule;
import BoardModule;
import ControllerModule;
import ShopModule;

import <array>;
import <string>;

export class Menu {
private:

	static constexpr int buttonCount = 5;
	std::array<const char*, buttonCount> labels = { "Start Game", "Leaderboard","Shop", "Options", "Exit" };
	std::array<Rectangle, buttonCount> buttons;
	int selected = -1;

	Resources* resources{ nullptr };
	Board* board{ nullptr };
	Shop* shop{ nullptr };
	Texture2D menuBackground;

public:

	void setContext(Resources& res, Board& b, Shop& s) {
		resources = &res;
		board = &b;
		shop = &s;
	}

	void showMenu(int screenWidth, int screenHeight) {
		menuBackground = LoadTexture("textures/main_menu_background.png");
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
						handleClick(i);
					}
				}
			}

			BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawTexturePro(
				menuBackground,
				Rectangle{ 0,0, static_cast<float> (menuBackground.width), static_cast<float>(menuBackground.height) },
				Rectangle{ 0,0, static_cast<float>(screenWidth), static_cast<float> (screenHeight) },
				Vector2{ 0,0 },
				0.0f,
				WHITE
			);

			DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 40) / 2, 50, 40, BLACK);

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

	void newGame() {
		if (resources && board) {
			Controller controller(*resources, *board, GetScreenWidth(), GetScreenHeight());
			controller.run();
		}
	}

	void showOptions() {
		//to do
	}

	void openShop() {
		if (shop && resources) {
			//TraceLog(LOG_INFO, ">>> OPENING SHOP <<<");
			shop->show(GetScreenWidth(), GetScreenHeight());
		}
	}

	void exitGame() const {
		CloseWindow();
	}

	void handleClick(int index) {
		switch (index) {
		case 0: newGame(); break;
		case 1: showOptions(); break;
		case 2: openShop(); break;
		case 3: showOptions(); break; // placeholder
		case 4: exitGame(); break;
		}
	}
};