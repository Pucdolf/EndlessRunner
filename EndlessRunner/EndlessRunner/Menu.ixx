module;
#include "raylib.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

export module MenuModule;

import ResourcesModule;
import BoardModule;
import ControllerModule;
import ShopModule;

import <array>;

export class Menu {
private:
	static constexpr int buttonCount = 5;
	std::array<const char*, buttonCount> labels = { "Start Game", "LeaderBoard", "Shop", "Log Out", "Exit" };
	std::array<Rectangle, buttonCount> buttons;
	int selected = -1;
	std::string username;

	Resources* resources{ nullptr };
	Board* board{ nullptr };
	Shop* shop{ nullptr };

public:
	void setContext(Resources& res, Board& b, Shop& s) {
		resources = &res;
		board = &b;
		shop = &s;
	}

	void setUsername(const std::string& user) {
		username = user;
	}

	void showMenu(int screenWidth, int screenHeight) {
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
				Rectangle{ 0,0, static_cast<float>(resources->getMenuBackground().width), static_cast<float>(resources->getMenuBackground().height) },
				Rectangle{ 0,0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
				Vector2{ 0,0 },
				0.0f,
				WHITE
			);

			std::string welcomeText = username.empty() ? "Welcome Guest" : "Welcome " + username;
			DrawText(welcomeText.c_str(), screenWidth / 2 - MeasureText(welcomeText.c_str(), 40) / 2, 50, 40, BLACK);

			int fontSize = 20;
			for (int i = 0; i < buttonCount; ++i) {
				// Pobieramy teksturê przycisku
				Texture2D buttonTex = resources->getButtonTexture();
				// Okreœlamy kolor w zale¿noœci od tego, czy przycisk jest wybrany
				Color color = (i == selected) ? GRAY : WHITE;

				// Rysujemy teksturê przycisku
				DrawTexturePro(
					buttonTex,
					Rectangle{ 0, 0, static_cast<float>(buttonTex.width), static_cast<float>(buttonTex.height) },
					buttons[i], // Prostok¹t docelowy (rozmiar przycisku)
					Vector2{ 0, 0 },
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

private:
	void newGame() {
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

	struct ScoreEntry {
		std::string username;
		int score;
	};

	void showLeaderboard(int screenWidth, int screenHeight) {
		// Mapa przechowuj¹ca najlepszy wynik dla ka¿dego u¿ytkownika
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

		// Przekszta³camy mapê na wektor wyników
		std::vector<ScoreEntry> scores;
		for (const auto& entry : bestScores) {
			scores.push_back({ entry.first, entry.second });
		}

		// Sortujemy malej¹co wed³ug wyniku
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

			// Rysowanie tekstury ramki leaderboarda
			Texture2D leaderboardFrame = resources->getLeaderboard();
			float frameScale = std::min(
				static_cast<float>(screenWidth) / leaderboardFrame.width,
				static_cast<float>(screenHeight) / leaderboardFrame.height
			) * 0.8f; // Skalowanie do 80% ekranu
			float frameWidth = leaderboardFrame.width * frameScale;
			float frameHeight = leaderboardFrame.height * frameScale;
			float frameX = (screenWidth - frameWidth) / 2;
			float frameY = (screenHeight - frameHeight) / 2;

			DrawTextureEx(leaderboardFrame, { frameX, frameY }, 0.0f, frameScale, WHITE);

			// Rysowanie tytu³u "Leaderboard" na górze ramki
			DrawText("Leaderboard", static_cast<int>(frameX + (frameWidth - MeasureText("Leaderboard", 40)) / 2),
				static_cast<int>(frameY + 70), 40, BLACK);

			// Rysowanie wyników wewn¹trz ramki
			size_t maxScores = std::min(static_cast<size_t>(10), scores.size());
			float textY = frameY + 120; // Pocz¹tek tekstu pod tytu³em
			for (size_t i = 0; i < maxScores; i++) {
				std::string entry = std::to_string(i + 1) + ". " + scores[i].username + ": " + std::to_string(scores[i].score);
				DrawText(entry.c_str(), static_cast<int>(frameX + (frameWidth - MeasureText(entry.c_str(), 30)) / 2),
					static_cast<int>(textY + i * 40), 30, BLACK);
			}

			// Rysowanie tekstu "Press ESC to return" pod ramk¹
			DrawText("Press ESC to return", screenWidth / 2 - MeasureText("Press ESC to return", 20) / 2,
				screenHeight - 30, 20, BLACK);

			EndDrawing();
		}
	}

	void openShop() {
		if (shop && resources) {
			shop->show(GetScreenWidth(), GetScreenHeight());
		}
	}

	void LogOut(bool& menuRunning) const {
		CloseWindow();
		menuRunning = false;
	}

	void exitGame(bool& menuRunning) {
		resources->unloadTextures();
		menuRunning = false;
		CloseWindow();
		exit(0);

	}

	void handleClick(int index, bool& menuRunning) {
		switch (index) {
		case 0: newGame(); break;
		case 1: showLeaderboard(GetScreenWidth(), GetScreenHeight()); break;
		case 2: openShop(); break;
		case 3: LogOut(menuRunning); break;
		case 4: exitGame(menuRunning); break;
		}
	}
};