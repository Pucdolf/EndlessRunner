/**
 * @file Menu.cpp
 * @brief Implementacja klasy Menu.
 */
module;
#include "raylib.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <array>
#include <vector>

module MenuModule;

void Menu::setContext(Resources& res, Board& b, Shop& s) {
	resources = &res;
	board = &b;
	shop = &s;
}

void Menu::setUsername(const std::string& user) {
	username = user;
}

void Menu::showMenu(int screenWidth, int screenHeight) {
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
			Rectangle{ 0, 0, static_cast<float>(resources->getMenuBackground().width), static_cast<float>(resources->getMenuBackground().height) },
			Rectangle{ 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
			Vector2{ 0, 0 },
			0.0f,
			WHITE
		);


		Texture2D banner = resources->getBanner();
		float bannerScale = Config::BANNER_SCALE;
		float bannerHeight = banner.height * bannerScale;
		float bannerX = screenWidth / 2 - ((banner.width * bannerScale) / 2);
		float bannerY = Config::BANNER_Y;
		DrawTextureEx(banner, { bannerX, bannerY }, 0.0f, bannerScale, WHITE);

		std::string welcomeText = username.empty() ? "Welcome Guest" : "Welcome " + username;
		int textWidth = MeasureText(welcomeText.c_str(), 30);
		float textX = (screenWidth - textWidth) / 2.0f;
		DrawText(welcomeText.c_str(), static_cast<int>(textX), static_cast<int>(bannerY + (bannerHeight - 45) / 2), 30, BLACK);

		int fontSize = 20;
		for (int i = 0; i < buttonCount; ++i) {
			Texture2D buttonTex = resources->getButtonTexture();
			Color color = (i == selected) ? GRAY : WHITE;

			DrawTexturePro(
				buttonTex,
				Rectangle{ 0, 0, static_cast<float>(buttonTex.width), static_cast<float>(buttonTex.height) },
				buttons[i],
				Vector2{ 0,0 },
				0.0f,
				color
			);

			int textWidth = MeasureText(labels[i], fontSize);
			int textX = static_cast<int>(buttons[i].x + (buttons[i].width - textWidth) / 2);
			int textY = static_cast<int>(buttons[i].y + (buttons[i].height - fontSize) / 2);
			DrawText(labels[i], textX, textY, fontSize, BLACK);
		}

		EndDrawing();
	}
}

void Menu::newGame() {
	if (resources && board && shop) {
		int selectedDino = shop->getSelectedDino();
		int frameCount = shop->getSelectedDinoFrameCount();

		Texture2D selectedDinoTex;
		switch (selectedDino) {
		case 0: selectedDinoTex = resources->getGreenDinoRun(); break;
		case 1: selectedDinoTex = resources->getBlueDinoRun(); break;
		case 2: selectedDinoTex = resources->getYellowDinoRun(); break;
		case 3: selectedDinoTex = resources->getRedDinoRun(); break;
		default: selectedDinoTex = resources->getGreenDinoRun(); break;
		}

		board->setDinoTex(selectedDinoTex);
		board->setDinoFrameCount(frameCount);
		//board->init(selectedDinoTex, GetScreenWidth(), GetScreenHeight());
		Controller controller(*resources, *board, username, GetScreenWidth(), GetScreenHeight());
		controller.run();
	}
}



void Menu::showLeaderboard(int screenWidth, int screenHeight) {
	std::map<std::string, int> bestScores;
	std::ifstream file("scores.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string user;
			int score;
			if (std::getline(iss, user, ':') && (iss >> score)) {
				if (bestScores.find(user) == bestScores.end() || score > bestScores[user]) {
					bestScores[user] = score;
				}
			}
		}
		file.close();
	}

	std::vector<ScoreEntry> scores;
	for (const auto& entry : bestScores) {
		scores.push_back({ entry.first, entry.second });
	}

	std::sort(scores.begin(), scores.end(),
		[](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });

	bool leaderboardRunning = true;
	while (!WindowShouldClose() && leaderboardRunning) {
		screenWidth = GetScreenWidth();
		screenHeight = GetScreenHeight();

		if (IsKeyPressed(KEY_ESCAPE)) {
			leaderboardRunning = false;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawTexturePro(
			resources->getMenuBackground(),
			Rectangle{ 0, 0, static_cast<float>(resources->getMenuBackground().width), static_cast<float>(resources->getMenuBackground().height) },
			Rectangle{ 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
			Vector2{ 0, 0 },
			0.0f,
			WHITE
		);


		Texture2D leaderboardFrame = resources->getLeaderboard();
		float frameScale = std::min(
			static_cast<float>(screenWidth) / leaderboardFrame.width,
			static_cast<float>(screenHeight) / leaderboardFrame.height
		) * 0.8f;
		float frameWidth = leaderboardFrame.width * frameScale;
		float frameHeight = leaderboardFrame.height * frameScale;
		float frameX = (screenWidth - frameWidth) / 2;
		float frameY = (screenHeight - frameHeight) / 2;

		DrawTextureEx(leaderboardFrame, { frameX, frameY }, 0.0f, frameScale, WHITE);

		DrawText("Leaderboard", static_cast<int>(frameX + (frameWidth - MeasureText("Leaderboard", 40)) / 2),
			static_cast<int>(frameY + 70), 40, BLACK);

		size_t maxScores = std::min(static_cast<size_t>(10), scores.size());
		float textY = frameY + 120;
		for (size_t i = 0; i < maxScores; i++) {
			std::string entry = std::to_string(i + 1) + ". " + scores[i].username + ": " + std::to_string(scores[i].score);
			DrawText(entry.c_str(), static_cast<int>(frameX + (frameWidth - MeasureText(entry.c_str(), 30)) / 2),
				static_cast<int>(textY + i * 40), 30, BLACK);
		}

		DrawText("Press ESC to return", screenWidth / 2 - MeasureText("Press ESC to return", 20) / 2,
			screenHeight - 30, 20, BLACK);

		EndDrawing();
	}
}