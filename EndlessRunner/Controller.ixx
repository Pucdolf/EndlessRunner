#include "raylib.h"
export module ControllerModule;

import BoardModule;
import ResourcesModule;
import <string>;

export class Controller {
private:
	Resources& resources;
	Board& board;
	int windowWidth{};
	int windowHeight{};
	float scale = 3.0f;

	float bgX{}, mgX{}, fgX{};
	bool gameOver{ false };
	int lives = 3;
	float score = 0.0f;

public:

	Controller(Resources& res, Board& b, int width, int height)
		: resources(res), board(b), windowWidth(width), windowHeight(height)
	{

	}

	void run() {

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
				DrawText("Game Over!", windowWidth / 4, windowHeight / 2, 40, RED);
			}
			else if (board.checkWin()) {
				DrawText("You Win!", windowWidth / 4, windowHeight / 2, 40, GREEN);
			}
			else {
				score += dt;
				board.draw(resources.getPlayerRun(), resources.getNebula());
			}

			drawUI();

			EndDrawing();
		}

		//resources.unloadTextures();
		CloseWindow();
	}

private:
	void scrollBackground(float dt, int windowWidth, int windowHeight) {
		Texture2D background = resources.getGameBackground();
		Texture2D midground = resources.getGameMidground();
		Texture2D foreground = resources.getGameForeground();

		float scale = static_cast<float>(windowHeight) / background.height;
		float scaledWidth = background.width * scale;

		bgX -= 20 * dt * scale;
		if (bgX <= -scaledWidth) bgX = 0.0;

		mgX -= 40 * dt * scale;
		if (mgX <= -scaledWidth) mgX = 0.0;

		fgX -= 60 * dt * scale;
		if (fgX <= -scaledWidth) fgX = 0.0;

		DrawTextureEx(background, { bgX, 0 }, 0.0, scale, WHITE);
		DrawTextureEx(background, { bgX + scaledWidth, 0 }, 0.0, scale, WHITE);
		DrawTextureEx(background, { bgX + scaledWidth * scale, 0 }, 0.0, scale, WHITE);


		DrawTextureEx(midground, { mgX, 0 }, 0.0, scale, WHITE);
		DrawTextureEx(midground, { mgX + scaledWidth, 0 }, 0.0, scale, WHITE);
		DrawTextureEx(midground, { mgX + scaledWidth * scale, 0 }, 0.0, scale, WHITE);

		DrawTextureEx(foreground, { fgX, 0 }, 0.0, scale, WHITE);
		DrawTextureEx(foreground, { fgX + scaledWidth, 0 }, 0.0, scale, WHITE);
		DrawTextureEx(foreground, { fgX + scaledWidth * scale, 0 }, 0.0, scale, WHITE);

	}


	void drawUI()
	{
		// Draw lives
		Texture2D lifeFull = resources.getHeartIcon();
		Texture2D lifeEmpty = resources.getLifeLostIcon();
		for (int i = 0; i < 3; i++) {
			Texture2D icon = (i < lives) ? lifeFull : lifeEmpty;
			float x = 10 + i * (icon.width * scale + 5);
			float y = 10;
			DrawTextureEx(icon, { x,y }, 0.f, scale, WHITE);
		}

		// Draw score
		Texture2D numbers = resources.getNumbersTexture();
		int s = static_cast<int>(score);
		std::string scoreText = std::to_string(s);

		int digitWidth = numbers.width / 10;
		int digitHeight = numbers.height;

		int scaledWidth = digitWidth * scale;
		int totalWidth = scaledWidth * scoreText.length();
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
			DrawTexturePro(numbers, src, dest, { 0,0 }, 0.0f, WHITE);
		}
	}

};
