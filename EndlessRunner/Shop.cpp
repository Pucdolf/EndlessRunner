/**
 * @file Shop.cpp
 * @brief Implementacja klasy Shop.
 */

module;
#include "raylib.h"

module ShopModule;

void Shop::init(Resources& res, int screenWidth, int screenHeight) {
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

void Shop::show(int screenWidth, int screenHeight) {
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
				selectionFrame.y += 50.f * heightScale;
				DrawRectangleLinesEx(selectionFrame, 4.f * widthScale, GREEN);
			}
		}

		DrawText("Press ESC to return", screenWidth / 2 - MeasureText("Press ESC to return", 20) / 2, screenHeight - 30, 20, BLACK);
		EndDrawing();
	}
}

int Shop::getSelectedDino() const {
	return selectedDinoIndex;
}

int Shop::getSelectedDinoFrameCount() const {
	return frameCounts[selectedDinoIndex];
}