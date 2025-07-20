/**
 * @file Controller.cpp
 * @brief Implementacja klasy Controller.
 */

module;
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

module ControllerModule;

void Controller::saveScore() {
	if (username.empty() || savedScore) return;
	std::ofstream file("scores.txt", std::ios::app);
	if (file.is_open()) {
		file << username << ":" << static_cast<int>(score) << "\n";
		file.close();
		savedScore = true;
	}
	else {
		std::cout << "Failed to open scores.txt for writing\n";
	}
}


void Controller::run() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 3);
	int backgroundChoice = dis(gen);

	BackgroundType bgType;
	switch (backgroundChoice) {
	case 0: // Pustynia dzienna
		bgTexture = resources.getDesertBackground();
		mgTexture = resources.getDesertMidground();
		fgTexture = resources.getDesertForeground();
		groundTexture = resources.getDesertGround();
		bgType = BackgroundType::DESERT_DAY;
		break;
	case 1: // Pustynia noc¹
		bgTexture = resources.getDesertNightBackground();
		mgTexture = resources.getDesertNightMidground();
		fgTexture = resources.getDesertNightForeground();
		groundTexture = resources.getDesertNightGround();
		bgType = BackgroundType::DESERT_NIGHT;
		break;
	case 2: // Las za dnia
		bgTexture = resources.getForestBackground();
		mgTexture = resources.getForestMidground();
		fgTexture = resources.getForestForeground();
		groundTexture = resources.getForestGround();
		bgType = BackgroundType::FOREST_DAY;
		break;
	case 3: // Las noc¹
		bgTexture = resources.getForestNightBackground();
		mgTexture = resources.getForestNightMidground();
		fgTexture = resources.getForestNightForeground();
		groundTexture = resources.getForestNightGround();
		bgType = BackgroundType::FOREST_NIGHT;
		break;
	default:
		bgTexture = resources.getDesertBackground();
		mgTexture = resources.getDesertMidground();
		fgTexture = resources.getDesertForeground();
		bgType = BackgroundType::DESERT_DAY;
		break;
	}

	board.setBackgroundType(bgType);
	board.init(resources.getGreenDinoRun(), GetScreenWidth(), GetScreenHeight());
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();

		BeginDrawing();
		ClearBackground(BLACK);

		scrollBackground(dt, GetScreenWidth(), GetScreenHeight());

		if (!gameOver) {
			board.update(dt, windowHeight);
			gameOver = board.checkLoss();
			score += dt;
		}

		if (gameOver) {
			std::string gameOverText = "Game Over! Score: " + std::to_string(static_cast<int>(score));
			DrawText(gameOverText.c_str(), windowWidth / 2 - MeasureText(gameOverText.c_str(), 40) / 2, windowHeight / 2, 40, RED);
			if (!savedScore) {
				saveScore();
			}
			DrawText("Press ENTER to return to menu", windowWidth / 2 - MeasureText("Press ENTER to return to menu", 20) / 2, windowHeight / 2 + 50, 20, WHITE);
			if (IsKeyPressed(KEY_ENTER)) {
				gameOver = false;
				break;
			}
		}
		else {
			board.draw();
		}

		drawUI();

		EndDrawing();
	}
}

void Controller::scrollBackground(float dt, int windowWidth, int widnowHeight) {
	float avgHeight = (bgTexture.height + mgTexture.height + fgTexture.height) / 3.0f;
	float universalScale = static_cast<float>(windowHeight) / avgHeight;

	float bgScaledWidth = bgTexture.width * universalScale;
	float mgScaledWidth = mgTexture.width * universalScale;
	float fgScaledWidth = fgTexture.width * universalScale;
	float groundScaledWidth = groundTexture.width * universalScale;

	bgX -= 20 * dt;
	mgX -= 40 * dt;
	fgX -= 60 * dt;
	groundX -= 200 * dt;

	bgX = fmod(bgX, bgScaledWidth);
	if (bgX > 0) bgX -= bgScaledWidth;
	mgX = fmod(mgX, mgScaledWidth);
	if (mgX > 0) mgX -= mgScaledWidth;
	fgX = fmod(fgX, fgScaledWidth);
	if (fgX > 0) fgX -= fgScaledWidth;
	groundX = fmod(groundX, groundScaledWidth);
	if (groundX > 0) groundX -= groundScaledWidth;

	auto drawTileableLayer = [&](Texture2D texture, float xPos, float scaledWidth) {
		int numInstances = static_cast<int>(windowWidth / scaledWidth) + 2;
		float startX = xPos;
		for (int i = 0; i < numInstances; ++i) {
			float drawX = startX + i * scaledWidth;
			DrawTextureEx(texture, { drawX, 0.f }, 0.0f, universalScale, WHITE);
		}
		};

	auto drawForegroundLayer = [&](Texture2D texture, float xPos, float scaledWidth) {
		int numInstances = static_cast<int>(windowWidth / scaledWidth) + 2;
		float startX = xPos;
		for (int i = 0; i < numInstances; ++i) {
			float drawX = startX + i * scaledWidth;
			float textureHeight = texture.height * universalScale;
			float drawY = windowHeight - textureHeight;
			DrawTextureEx(texture, { drawX, drawY }, 0.0f, universalScale, WHITE);
		}
		};

	drawTileableLayer(bgTexture, bgX, bgScaledWidth);
	drawTileableLayer(mgTexture, mgX, mgScaledWidth);
	drawForegroundLayer(fgTexture, fgX, fgScaledWidth);
	drawTileableLayer(groundTexture, groundX, groundScaledWidth);
}

void Controller::drawUI() {
	Texture2D lifeFull = resources.getHeartIcon();
	Texture2D lifeEmpty = resources.getLifeLostIcon();

	Texture2D icon = (!gameOver) ? lifeFull : lifeEmpty;
	float x = 10;
	float y = 10;
	DrawTextureEx(icon, { x, y }, 0.f, numbScale, WHITE);


	Texture2D numbers = resources.getNumbersTexture();
	int s = static_cast<int>(score);
	std::string scoreText = std::to_string(s);

	int digitWidth = numbers.width / 10;
	int digitHeight = numbers.height;

	float scaledWidth = digitWidth * numbScale;
	float totalWidth = scaledWidth * scoreText.length();
	windowWidth = GetScreenWidth();

	for (int i = 0; i < scoreText.length(); ++i) {
		int digit = scoreText[i] - '0';
		Rectangle src = { static_cast<float>(digit * digitWidth), 0, static_cast<float>(digitWidth), static_cast<float>(digitHeight) };
		Rectangle dest = {
			static_cast<float>(windowWidth - totalWidth - 10 + i * scaledWidth),
			10.0f,
			static_cast<float>(scaledWidth),
			static_cast<float>(digitHeight * numbScale)
		};
		DrawTexturePro(numbers, src, dest, { 0, 0 }, 0.0f, WHITE);
	}
}
