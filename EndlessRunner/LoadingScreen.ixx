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
		const int loadingDuration = 1000; //ms

		//NIE DZIALA
		/*std::thread loader([&]() {*/
		resources.loadTextures();
		//progress = 50;
		board.init(resources.getDino(), resources.getNebula(), screenWidth, screenHeight);
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
			ClearBackground(RAYWHITE);
			DrawText("Loading...", screenWidth / 2 - 50, screenHeight / 2 + 40, 20, DARKGRAY);

			int barX = screenWidth / 2 - barEmpty.width / 2;
			int barY = screenHeight / 2 - barEmpty.height / 2;
			DrawTexture(barEmpty, barX, barY, WHITE);

			Rectangle source = { 0,0, barFill.width * loadingProgress, static_cast<float>(barFill.height) };
			Rectangle dest = { static_cast<float>(barX), static_cast<float>(barY), barFill.width * loadingProgress, static_cast<float>(barFill.height) };
			DrawTexturePro(barFill, source, dest, { 0,0 }, 0.0f, WHITE);

			EndDrawing();
		}

		UnloadTexture(barEmpty);
		UnloadTexture(barFill);

	}
};
