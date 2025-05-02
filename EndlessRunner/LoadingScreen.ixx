module;
#include "raylib.h"
#include "chrono"

export module LoadingScreenModule;

import ResourcesModule;
import BoardModule;
import ShopModule;
import AuthModule;

export class LoadingScreen {
private:
	Texture2D barEmpty;
	Texture2D barFill;
	bool loadingFinished = false;

public:
	void show(int screenWidth, int screenHeight, Resources& resources, Board& board, Shop& shop) {
		

		auto startTime = std::chrono::high_resolution_clock::now();
		const int loadingDuration = 3000; //ms

		resources.loadTextures();

		barEmpty = resources.getBarEmpty();
		barFill = resources.getBarFill();

		shop.init(resources, screenWidth, screenHeight);

		while (!loadingFinished && !WindowShouldClose()) {
			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();

			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
			float loadingProgress = static_cast<float>(duration.count()) / loadingDuration;

			if (loadingProgress > 1.f) {
				loadingProgress = 1.f;
				loadingFinished = true;
			}

			BeginDrawing();
			DrawTexturePro(
				resources.getLoadingScreenBackground(),
				Rectangle{ 0,0, static_cast<float>(resources.getLoadingScreenBackground().width), static_cast<float>(resources.getLoadingScreenBackground().height) },
				Rectangle{ 0,0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
				Vector2{ 0,0 },
				0.0f,
				WHITE
			);

			int barX = screenWidth / 2 - barEmpty.width / 2;
			int barY = screenHeight / 2 + 230;

			DrawText("Loading...", screenWidth / 2 - MeasureText("Loading...", 20) / 2, barY - 30, 20, BLACK);
			DrawTexture(barEmpty, barX, barY, BLACK);

			Rectangle source = { 0,0, barFill.width * loadingProgress, static_cast<float>(barFill.height) };
			Rectangle dest = { static_cast<float>(barX), static_cast<float>(barY), barFill.width * loadingProgress, static_cast<float>(barFill.height) };
			DrawTexturePro(barFill, source, dest, { 0,0 }, 0.0f, WHITE);

			EndDrawing();
		}

		UnloadTexture(barEmpty);
		UnloadTexture(barFill);

		if (loadingFinished) {
			showAuthTiles(screenWidth, screenHeight, resources);
		}
	}

private:
	void showAuthTiles(int screenWidth, int screenHeight, Resources& resources) {


		// Wymiary przycisków
		constexpr float btnW = 200.0f;
		constexpr float btnH = 80.0f;

		// Obliczamy x-owe pozycje w 1/4 i 3/4 szerokoœci ekranu:
		float xLeft = screenWidth * 0.25f - btnW * 0.5f;
		float xRight = screenWidth * 0.75f - btnW * 0.5f;

		// Pozycja Y – ok. 60% wysokoœci ekranu, czyli poni¿ej logo
		float btnY = screenHeight * 0.85f - btnH * 0.5f;

		Rectangle signInButton = { xLeft,  btnY, btnW, btnH };
		Rectangle logInButton = { xRight, btnY, btnW, btnH };


		bool authRunning = true;

		while (authRunning && !WindowShouldClose()) {
			Vector2 mouse = GetMousePosition();

			BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawTexturePro(
				resources.getLoadingScreenBackground(),
				Rectangle{ 0,0, static_cast<float>(resources.getLoadingScreenBackground().width), static_cast<float>(resources.getLoadingScreenBackground().height) },
				Rectangle{ 0,0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
				Vector2{ 0,0 },
				0.0f,
				WHITE
			);

			DrawRectangleRec(signInButton, LIGHTGRAY);
			DrawText("Sign In", signInButton.x + (signInButton.width - MeasureText("Sign In", 20)) / 2, signInButton.y + 30, 20, BLACK);

			DrawRectangleRec(logInButton, LIGHTGRAY);
			DrawText("Log In", logInButton.x + (logInButton.width - MeasureText("Log In", 20)) / 2, logInButton.y + 30, 20, BLACK);

			if (CheckCollisionPointRec(mouse, signInButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				handleSignIn(screenWidth, screenHeight);
				authRunning = false;
			}
			if (CheckCollisionPointRec(mouse, logInButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				handleLogIn(screenWidth, screenHeight);
				authRunning = false;
			}

			EndDrawing();
		}
	}

	void handleSignIn(int screenWidth, int screenHeight) {
		AuthManager auth;
		std::string username, password;
		bool validInput = false;
		bool enteringUsername = true;
		Rectangle submitButton = { screenWidth / 2 - 100, screenHeight / 2 + 100, 200, 60 };

		while (!WindowShouldClose() && !validInput) {
			Vector2 mouse = GetMousePosition();

			// Handle keyboard input
			int key = GetCharPressed();
			while (key > 0) {
				if ((key >= 32) && (key <= 125)) { // Printable characters
					if (enteringUsername && username.length() < 20) {
						username += static_cast<char>(key);
					}
					else if (!enteringUsername && password.length() < 20) {
						password += static_cast<char>(key);
					}
				}
				key = GetCharPressed();
			}

			if (IsKeyPressed(KEY_BACKSPACE)) {
				if (enteringUsername && !username.empty()) {
					username.pop_back();
				}
				else if (!enteringUsername && !password.empty()) {
					password.pop_back();
				}
			}

			if (IsKeyPressed(KEY_TAB)) {
				enteringUsername = !enteringUsername;
			}

			if (IsKeyPressed(KEY_ENTER) || (CheckCollisionPointRec(mouse, submitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
				if (auth.signIn(username, password)) {
					validInput = true;
				}
			}

			BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawText("Enter Username (3-20 chars, alphanumeric):", screenWidth / 2 - 200, screenHeight / 2 - 100, 20, enteringUsername ? GREEN : BLACK);
			DrawText(username.c_str(), screenWidth / 2 - 200, screenHeight / 2 - 70, 20, BLACK);
			DrawRectangleLines(screenWidth / 2 - 200, screenHeight / 2 - 70, 400, 30, enteringUsername ? GREEN : BLACK);

			DrawText("Enter Password (8+ chars, letters and numbers):", screenWidth / 2 - 200, screenHeight / 2 - 30, 20, !enteringUsername ? GREEN : BLACK);
			DrawText(password.c_str(), screenWidth / 2 - 200, screenHeight / 2, 20, BLACK);
			DrawRectangleLines(screenWidth / 2 - 200, screenHeight / 2, 400, 30, !enteringUsername ? GREEN : BLACK);

			DrawRectangleRec(submitButton, LIGHTGRAY);
			DrawText("Submit", submitButton.x + (submitButton.width - MeasureText("Submit", 20)) / 2, submitButton.y + 20, 20, BLACK);

			EndDrawing();
		}
	}

	void handleLogIn(int screenWidth, int screenHeight) {
		AuthManager auth;
		std::string username, password;
		bool loggedIn = false;
		bool enteringUsername = true;
		Rectangle submitButton = { screenWidth / 2 - 100, screenHeight / 2 + 100, 200, 60 };

		while (!WindowShouldClose() && !loggedIn) {
			Vector2 mouse = GetMousePosition();

			// Handle keyboard input
			int key = GetCharPressed();
			while (key > 0) {
				if ((key >= 32) && (key <= 125)) {
					if (enteringUsername && username.length() < 20) {
						username += static_cast<char>(key);
					}
					else if (!enteringUsername && password.length() < 20) {
						password += static_cast<char>(key);
					}
				}
				key = GetCharPressed();
			}

			if (IsKeyPressed(KEY_BACKSPACE)) {
				if (enteringUsername && !username.empty()) {
					username.pop_back();
				}
				else if (!enteringUsername && !password.empty()) {
					password.pop_back();
				}
			}

			if (IsKeyPressed(KEY_TAB)) {
				enteringUsername = !enteringUsername;
			}

			if (IsKeyPressed(KEY_ENTER) || (CheckCollisionPointRec(mouse, submitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
				if (auth.logIn(username, password)) {
					loggedIn = true;
				}
			}

			BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawText("Enter Username:", screenWidth / 2 - 100, screenHeight / 2 - 100, 20, enteringUsername ? GREEN : BLACK);
			DrawText(username.c_str(), screenWidth / 2 - 100, screenHeight / 2 - 70, 20, BLACK);
			DrawRectangleLines(screenWidth / 2 - 100, screenHeight / 2 - 70, 200, 30, enteringUsername ? GREEN : BLACK);

			DrawText("Enter Password:", screenWidth / 2 - 100, screenHeight / 2 - 30, 20, !enteringUsername ? GREEN : BLACK);
			DrawText(password.c_str(), screenWidth / 2 - 100, screenHeight / 2, 20, BLACK);
			DrawRectangleLines(screenWidth / 2 - 100, screenHeight / 2, 200, 30, !enteringUsername ? GREEN : BLACK);

			DrawRectangleRec(submitButton, LIGHTGRAY);
			DrawText("Submit", submitButton.x + (submitButton.width - MeasureText("Submit", 20)) / 2, submitButton.y + 20, 20, BLACK);

			EndDrawing();
		}
	}
};