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

	std::array<float, DinoCount> scales{ 6.0f, 7.5f, 8.5f, 7.0f };
	std::array<float, DinoCount> frameWidths;
	std::array<float, DinoCount> frameHeights;

	int frame = 0;
	float runningTime = 0;
	float updateTime = 1.0f / 12.0f;

public:
	void init(Resources& res, int screenWidth, int screenHeight)
	{
		dinos[0] = res.getGreenIdle();
		dinos[1] = res.getBlueIdle();
		dinos[2] = res.getYellowIdle();
		dinos[3] = res.getRedIdle();
		background = LoadTexture("textures/shop_background.png");

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

			BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawTexturePro(
				background,
				Rectangle{ 0, 0, static_cast<float>(background.width), static_cast<float>(background.height) },
				Rectangle{ 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
				Vector2{ 0, 0 },
				0.0f,
				WHITE
			);

			DrawText("SHOP", screenWidth / 2 - MeasureText("SHOP", 40) / 2, 40, 40, BLACK);

			for (int i = 0; i < DinoCount; i++) {
				Rectangle dest = {
					dinoRecs[i].x + (dinoRecs[i].width - frameWidths[i] * scales[i]) / 2,
					screenHeight * 0.75f - frameHeights[i] * scales[i],
					frameWidths[i] * scales[i],
					frameHeights[i] * scales[i]
				};

				Rectangle source = { frame * frameWidths[i], 0.0f, frameWidths[i], frameHeights[i] };

				DrawTexturePro(dinos[i], source, dest, Vector2{ 0, 0 }, 0.0f, WHITE);
			}

			EndDrawing();
		}
	}
};
