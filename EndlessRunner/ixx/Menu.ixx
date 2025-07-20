/**
 * @file Menu.ixx
 * @brief Modu³ definiuj¹cy klasê Menu, obs³uguj¹c¹ menu g³ówne gry.
 *
 * Klasa Menu zarz¹dza interfejsem menu, w tym opcjami gry, leaderboardem i sklepem.
 */

module;
#include "raylib.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
export module MenuModule;

import ResourcesModule;
import BoardModule;
import ControllerModule;
import ShopModule;
import ConfigModule;


/**
 * @class Menu
 * @brief Klasa obs³uguj¹ca menu g³ówne gry.
 *
 * Wyœwietla przyciski menu, obs³uguje leaderboard, sklep i rozpoczêcie gry.
 */
export class Menu {
	/** @brief Liczba przycisków w menu. */
	static constexpr int buttonCount = Config::MENU_BUTTON_COUNT; 
	/** @brief Etykiety przycisków menu. */
	std::array<const char*, buttonCount> labels = { "Start Game", "LeaderBoard", "Shop", "Log Out", "Exit" };
	/** @brief Prostok¹ty przycisków menu. */
	std::array<Rectangle, buttonCount> buttons;
	/** @brief Indeks wybranego przycisku (-1, jeœli brak). */
	int selected = -1;
	/** @brief Nazwa u¿ytkownika. */
	std::string username;

	/** @brief WskaŸnik do zasobów gry. */
	Resources* resources{ nullptr };
	/** @brief WskaŸnik do planszy gry. */
	Board* board{ nullptr };
	/** @brief WskaŸnik do sklepu. */
	Shop* shop{ nullptr };

public:
	/**
	* @brief Ustawia kontekst menu (zasoby, plansza, sklep).
	* @param res Referencja do zasobów gry.
	* @param b Referencja do planszy gry.
	* @param s Referencja do sklepu.
	*/
	void setContext(Resources& res, Board& b, Shop& s);/* {
		resources = &res;
		board = &b;
		shop = &s;
	}*/

	/**
	* @brief Ustawia nazwê u¿ytkownika.
	* @param user Nazwa u¿ytkownika.
	*/
	void setUsername(const std::string& user); /*{
		username = user;
	}*/

	/**
	 * @brief Wyœwietla menu g³ówne.
	 * @param screenWidth Szerokoœæ ekranu.
	 * @param screenHeight Wysokoœæ ekranu.
	 */
	void showMenu(int screenWidth, int screenHeight); /*{
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
	}*/

private:
	/**
	 * @brief Rozpoczyna now¹ grê.
	 */
	void newGame(); //{
	//	if (resources && board && shop) {
	//		int selectedDino = shop->getSelectedDino();
	//		int frameCount = shop->getSelectedDinoFrameCount();

	//		Texture2D selectedDinoTex;
	//		switch (selectedDino) {
	//		case 0: selectedDinoTex = resources->getGreenDinoRun(); break;
	//		case 1: selectedDinoTex = resources->getBlueDinoRun(); break;
	//		case 2: selectedDinoTex = resources->getYellowDinoRun(); break;
	//		case 3: selectedDinoTex = resources->getRedDinoRun(); break;
	//		default: selectedDinoTex = resources->getGreenDinoRun(); break;
	//		}

	//		board->setDinoTex(selectedDinoTex);
	//		board->setDinoFrameCount(frameCount);
	//		//board->init(selectedDinoTex, GetScreenWidth(), GetScreenHeight());
	//		Controller controller(*resources, *board, username, GetScreenWidth(), GetScreenHeight());
	//		controller.run();
	//	}
	//}

	/**
	 * @struct ScoreEntry
	 * @brief Struktura przechowuj¹ca dane wyniku (nazwa u¿ytkownika i punkty).
	 */
	struct ScoreEntry {
		/** @brief Nazwa u¿ytkownika. */
		std::string username;
		/** @brief Wynik u¿ytkownika. */
		int score;
	};

	/**
	* @brief Wyœwietla tablicê wyników.
	* @param screenWidth Szerokoœæ ekranu.
	* @param screenHeight Wysokoœæ ekranu.
	*/
	void showLeaderboard(int screenWidth, int screenHeight);/* {
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
	}*/

	/**
	 * @brief Otwiera sklep.
	 */
	void openShop() {
		if (shop && resources) {
			shop->show(GetScreenWidth(), GetScreenHeight());
		}
	}

	/**
	 * @brief Wylogowuje u¿ytkownika.
	 * @param menuRunning Flaga wskazuj¹ca, czy menu powinno byæ nadal aktywne.
	 */
	void LogOut(bool& menuRunning) const {
		CloseWindow();
		menuRunning = false;
	}

	/**
	* @brief Zamyka grê.
	* @param menuRunning Flaga wskazuj¹ca, czy menu powinno byæ nadal aktywne.
	*/
	void exitGame(bool& menuRunning) {
		resources->unloadTextures();
		menuRunning = false;
		CloseWindow();
		exit(0);

	}

	/**
	 * @brief Obs³uguje klikniêcie przycisku menu.
	 * @param index Indeks klikniêtego przycisku.
	 * @param menuRunning Flaga wskazuj¹ca, czy menu powinno byæ nadal aktywne.
	 */
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