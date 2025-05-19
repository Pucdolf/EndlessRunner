module;
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <random>
export module ControllerModule;

import BoardModule;
import ResourcesModule;
import <string>;

export class Controller {
private:
	Resources& resources;
	Board& board;
	std::string username;
	int windowWidth{};
	int windowHeight{};
	float scale = 3.0f;

	float bgX{}, mgX{}, fgX{};
	bool gameOver{ false };
	int lives = 3;
	float score = 0.0f;
	bool savedScore{ false };

	// Zmienne dla losowych t³a
	Texture2D bgTexture{};
	Texture2D mgTexture{};
	Texture2D fgTexture{};

	void saveScore() {
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

public:
	Controller(Resources& res, Board& b, const std::string& user, int width, int height)
		: resources(res), board(b), username(user), windowWidth(width), windowHeight(height) {
	}

	void run() {
		// Losowy wybór t³a
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 4);
		int backgroundChoice = dis(gen);

		switch (backgroundChoice) {
		case 0: // Pustynia dzienna
			bgTexture = resources.getDesertBackground();
			mgTexture = resources.getDesertMidground();
			fgTexture = resources.getDesertForeground();
			std::cout << "Desert Day - BG: " << bgTexture.width << "x" << bgTexture.height
				<< ", MG: " << mgTexture.width << "x" << mgTexture.height
				<< ", FG: " << fgTexture.width << "x" << fgTexture.height << "\n";
			break;
		case 1: // Pustynia noc¹
			bgTexture = resources.getDesertNightBackground();
			mgTexture = resources.getDesertNightMidground();
			fgTexture = resources.getDesertNightForeground();
			std::cout << "Desert Night - BG: " << bgTexture.width << "x" << bgTexture.height
				<< ", MG: " << mgTexture.width << "x" << mgTexture.height
				<< ", FG: " << fgTexture.width << "x" << fgTexture.height << "\n";
			break;

		case 2:
			bgTexture = resources.getForestBackground();
			mgTexture = resources.getForestMidground();
			fgTexture = resources.getForestForeground();
			std::cout << "Forest - BG: " << bgTexture.width << "x" << bgTexture.height
				<< ", MG: " << mgTexture.width << "x" << mgTexture.height
				<< ", FG: " << fgTexture.width << "x" << fgTexture.height << "\n";
			break;

		case 3: // Las noc¹
			bgTexture = resources.getForestNightBackground();
			mgTexture = resources.getForestNightMidground();
			fgTexture = resources.getForestNightForeground();
			std::cout << "Forest Night - BG: " << bgTexture.width << "x" << bgTexture.height
				<< ", MG: " << mgTexture.width << "x" << mgTexture.height
				<< ", FG: " << fgTexture.width << "x" << fgTexture.height << "\n";
			break;

		case 4:	// Miasto
			bgTexture = resources.getGameBackground();
			mgTexture = resources.getGameMidground();
			fgTexture = resources.getGameForeground();
			break;
		}

		board.init(resources.getGreenDinoRun(), resources.getBat(), resources.getPtero(), resources.getDustRun(), windowWidth, windowHeight);
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

private:
	void scrollBackground(float dt, int windowWidth, int windowHeight) {
		// Ustalamy wspóln¹ skalê na podstawie wysokoœci ekranu i œredniej wysokoœci tekstur
		float avgHeight = (bgTexture.height + mgTexture.height + fgTexture.height) / 3.0f;
		float universalScale = static_cast<float>(windowHeight) / avgHeight;

		// Skalowanie szerokoœci ka¿dej warstwy
		float bgScaledWidth = bgTexture.width * universalScale;
		float mgScaledWidth = mgTexture.width * universalScale;
		float fgScaledWidth = fgTexture.width * universalScale;
		float fgEffectiveWidth = fgScaledWidth * 0.75f;

		// Przewijanie z ró¿nymi prêdkoœciami
		bgX -= 20 * dt;
		mgX -= 40 * dt;
		fgX -= 60 * dt;

		if (bgX <= -bgScaledWidth) bgX += bgScaledWidth;
		if (mgX <= -mgScaledWidth) mgX += mgScaledWidth;
		if (fgX <= -fgEffectiveWidth) fgX += fgEffectiveWidth;

		auto drawTileableLayer = [&](Texture2D texture, float xPos, float scaledWidth) {
			int numInstances = static_cast<int>(windowWidth / scaledWidth) + 2;
			for (int i = 0; i < numInstances; ++i) {
				float drawX = xPos + i * scaledWidth;
				if (drawX < -scaledWidth || drawX > windowWidth) continue;
				DrawTextureEx(texture, { drawX, 0 }, 0.0f, universalScale, WHITE);
			}
			};

		auto drawForegroundLayer = [&](Texture2D texture, float xPos, float scaledWidth, float effectiveWidth) {
			int numInstances = static_cast<int>(windowWidth / effectiveWidth) + 2;
			for (int i = 0; i < numInstances; ++i) {
				float drawX = xPos + i * effectiveWidth;
				if (drawX < -scaledWidth || drawX > windowWidth) continue;
				// Dopasowanie pozycji Y, aby foreground zawsze zakrywa³ doln¹ czêœæ ekranu
				float textureHeight = texture.height * universalScale;
				float drawY = windowHeight - textureHeight;
				DrawTextureEx(texture, { drawX, drawY }, 0.0f, universalScale, WHITE);
			}
			};

		// Rysowanie warstw od ty³u do przodu
		drawTileableLayer(bgTexture, bgX, bgScaledWidth);
		drawTileableLayer(mgTexture, mgX, mgScaledWidth);
		drawForegroundLayer(fgTexture, fgX, fgScaledWidth, fgEffectiveWidth);
	}

	void drawUI() {
		Texture2D lifeFull = resources.getHeartIcon();
		Texture2D lifeEmpty = resources.getLifeLostIcon();
		for (int i = 0; i < 3; i++) {
			Texture2D icon = (i < lives) ? lifeFull : lifeEmpty;
			float x = 10 + i * (icon.width * scale + 5);
			float y = 10;
			DrawTextureEx(icon, { x, y }, 0.f, scale, WHITE);
		}

		Texture2D numbers = resources.getNumbersTexture();
		int s = static_cast<int>(score);
		std::string scoreText = std::to_string(s);

		int digitWidth = numbers.width / 10;
		int digitHeight = numbers.height;

		float scaledWidth = digitWidth * scale;
		float totalWidth = scaledWidth * scoreText.length();
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
			DrawTexturePro(numbers, src, dest, { 0, 0 }, 0.0f, WHITE);
		}
	}
};