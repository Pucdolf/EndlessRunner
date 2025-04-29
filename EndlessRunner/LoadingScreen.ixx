#include "raylib.h"
#include "chrono"

export module LoadingScreenModule;

import ResourcesModule;
import BoardModule;
import ShopModule;
import <thread>;
import <atomic>;

export class LoadingScreen {
private:

	Texture2D barEmpty;
	Texture2D barFill;
	bool loadingFinished = false;

public:
	void show(int screenWidth, int screenHeight, Resources& resources, Board& board, Shop& shop) {

		barEmpty = LoadTexture("textures/barempty.png");
		barFill = LoadTexture("textures/barfill.png");

		//std::atomic<int> progress = 0;

		auto startTime = std::chrono::high_resolution_clock::now();
		const int loadingDuration = 1500; //ms

		//NIE DZIALA
		/*std::thread loader([&]() {*/
		resources.loadTextures();
		//progress = 50;
		//board.init(resources.getPlayerRun(), resources.getNebula(), screenWidth, screenHeight);
		shop.init(resources, screenWidth, screenHeight);
		//progress = 100;
		//loadingFinished = true;
		//});
	//loader.detach();

		while (!loadingFinished && !WindowShouldClose()) {

			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();

			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
			float loadingProgress = static_cast<float>(duration.count()) / loadingDuration;

			//float percent = static_cast<float>(progress) / 100.f;

			if (loadingProgress > 1.f) {
				loadingProgress = 1.f;
				loadingFinished = true;
			}

			BeginDrawing();
			//ClearBackground(RAYWHITE);

			DrawTexturePro(
				resources.getLoadingScreenBackground(),
				Rectangle{ 0,0, static_cast<float>(resources.getLoadingScreenBackground().width), static_cast<float>(resources.getLoadingScreenBackground().height) },
				Rectangle{ 0,0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
				Vector2{ 0,0 },
				0.0f,
				WHITE
			);
			

			int barX = screenWidth / 2 - barEmpty.width / 2;
			int barY = screenHeight / 2 + 230;

			DrawText("Loading...", screenWidth / 2 - MeasureText("Loading...", 20) / 2, barY - 30, 20, DARKGRAY);

			DrawTexture(barEmpty, barX, barY, BLACK);

			Rectangle source = { 0,0, barFill.width * loadingProgress, static_cast<float>(barFill.height) };
			Rectangle dest = { static_cast<float>(barX), static_cast<float>(barY), barFill.width * loadingProgress, static_cast<float>(barFill.height) };
			DrawTexturePro(barFill, source, dest, { 0,0 }, 0.0f, WHITE);

			EndDrawing();
		}

		UnloadTexture(barEmpty);
		UnloadTexture(barFill);

	}
};
