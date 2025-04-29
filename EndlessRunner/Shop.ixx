#include "raylib.h"
#include <array>
#include <string>
export module ShopModule;

import ResourcesModule;

export class Shop
{
private:
	static constexpr int DinoCount{ 4 };
	Texture2D dinos[DinoCount];
	Rectangle dinoRecs[DinoCount];
	Texture2D background;
	Resources resources;
	std::array<float, DinoCount> scales{ 6.0f, 7.5f, 8.5f, 7.0f };
	std::array<float, DinoCount> frameWidths;
	std::array<float, DinoCount> frameHeights;
	std::array<int, DinoCount> frameCounts{ 6, 4, 4, 6 };

	int frame{ 0 };
	float runningTime{ 0 };
	float updateTime{ 1.0f / 12.0f };

	int selectedDinoIndex{ 0 };

public:
	void init(Resources& res, int screenWidth, int screenHeight)
	{
		resources = res;
		dinos[0] = resources.getGreenIdle();
		dinos[1] = resources.getBlueIdle();
		dinos[2] = resources.getYellowIdle();
		dinos[3] = resources.getRedIdle();


		for (int i{ 0 }; i < DinoCount; i++) {
			frameWidths[i] = static_cast<float>(dinos[i].width / 4);
			frameHeights[i] = static_cast<float>(dinos[i].height);
			dinoRecs[i] = Rectangle{
				static_cast<float>(i * screenWidth / DinoCount),
				static_cast<float>(screenHeight * 0.65f - 110.f),
				static_cast<float>(screenWidth / DinoCount),
				220.f
			};
		}
	}

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
				Rectangle dest = {
					dinoRecs[i].x + (dinoRecs[i].width - frameWidths[i] * scales[i]) / 2,
					screenHeight * 0.85f - frameHeights[i] * scales[i],
					frameWidths[i] * scales[i],
					frameHeights[i] * scales[i]
				};

				Rectangle source = { frame * frameWidths[i], 0.0f, frameWidths[i], frameHeights[i] };

				DrawTexturePro(dinos[i], source, dest, Vector2{ 0, 0 }, 0.0f, WHITE);

				if (i == selectedDinoIndex) {
					Rectangle selectionFrame = dinoRecs[i];
					selectionFrame.y += 50.f; // Przesuniêcie w dó³
					DrawRectangleLinesEx(selectionFrame, 4.f, GREEN);
				}

				DrawTexturePro(dinos[i], source, dest, Vector2{ 0,0 }, 0.f, WHITE);
			}

			EndDrawing();
		}
	}

	int getSelectedDino() const {
		return selectedDinoIndex;
	}

	int getSelectedDinoFrameCount() const {
		return frameCounts[selectedDinoIndex];
	}
};
