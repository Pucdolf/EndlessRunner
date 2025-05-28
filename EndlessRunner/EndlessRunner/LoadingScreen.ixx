module;
#include "raylib.h"
#include "chrono"
#include <string>

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
	// Modified to return the authenticated username
	std::string show(int screenWidth, int screenHeight, Resources& resources, Board& board, Shop& shop) {
		auto startTime = std::chrono::high_resolution_clock::now();
		const int loadingDuration = 2000; //ms

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
			return showAuthTiles(screenWidth, screenHeight, resources, board, shop);
		}
		return "";
	}

private:
	std::string showAuthTiles(int screenWidth, int screenHeight, Resources& resources, Board& board, Shop& shop) {
		constexpr float btnW = 200.0f;
		constexpr float btnH = 80.0f;

		float xLeft = screenWidth * 0.25f - btnW * 0.5f;
		float xRight = screenWidth * 0.75f - btnW * 0.5f;

		float btnY = screenHeight * 0.85f - btnH * 0.5f;

		Rectangle signInButton = { xLeft, btnY, btnW, btnH };
		Rectangle logInButton = { xRight, btnY, btnW, btnH };

		while (!WindowShouldClose()) {
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

			// Rysowanie przycisku "Sign In"
			Texture2D buttonTex = resources.getButtonTexture();
			Color signInColor = CheckCollisionPointRec(mouse, signInButton) ? GRAY : WHITE;
			DrawTexturePro(
				buttonTex,
				Rectangle{ 0, 0, static_cast<float>(buttonTex.width), static_cast<float>(buttonTex.height) },
				signInButton,
				Vector2{ 0, 0 },
				0.0f,
				signInColor
			);
			DrawText("Sign In", signInButton.x + (signInButton.width - MeasureText("Sign In", 20)) / 2, signInButton.y + 30, 20, BLACK);

			// Rysowanie przycisku "Log In"
			Color logInColor = CheckCollisionPointRec(mouse, logInButton) ? GRAY : WHITE;
			DrawTexturePro(
				buttonTex,
				Rectangle{ 0, 0, static_cast<float>(buttonTex.width), static_cast<float>(buttonTex.height) },
				logInButton,
				Vector2{ 0, 0 },
				0.0f,
				logInColor
			);
			DrawText("Log In", logInButton.x + (logInButton.width - MeasureText("Log In", 20)) / 2, logInButton.y + 30, 20, BLACK);

			if (CheckCollisionPointRec(mouse, signInButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				std::string username = handleSignIn(screenWidth, screenHeight, resources);
				if (!username.empty()) {
					return username;
				}
			}
			if (CheckCollisionPointRec(mouse, logInButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				std::string username = handleLogIn(screenWidth, screenHeight, resources);
				if (!username.empty()) {
					return username;
				}
			}

			EndDrawing();
		}
		return "";
	}

	std::string handleSignIn(int screenWidth, int screenHeight, Resources& resources) {
		Authorization auth;
		std::string username, password;
		std::string errorMessage;
		bool usernameError = false;
		bool passwordError = false;
		bool validInput = false;
		bool enteringUsername = true;
		Rectangle submitButton = { static_cast<float>(screenWidth / 2 - 100), static_cast<float>(screenHeight / 2 + 100), 200, 60 };

		while (!WindowShouldClose() && !validInput) {
			BeginDrawing();
			DrawTexturePro(
				resources.getRegistrationBackground(),
				Rectangle{ 0, 0, static_cast<float>(resources.getRegistrationBackground().width), static_cast<float>(resources.getRegistrationBackground().height) },
				Rectangle{ 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
				Vector2{ 0, 0 },
				0.0f,
				WHITE
			);

			Color usernameBorder = usernameError ? YELLOW : (enteringUsername ? GREEN : BLACK);
			DrawText("Enter Username (3-20 chars, alphanumeric):", screenWidth / 2 - 200, screenHeight / 2 - 100, 20, usernameBorder);
			DrawText(username.c_str(), screenWidth / 2 - 200, screenHeight / 2 - 70, 20, BLACK);
			DrawRectangleLines(screenWidth / 2 - 200, screenHeight / 2 - 70, 400, 30, usernameBorder);

			Color passwordBorder = passwordError ? YELLOW : (!enteringUsername ? GREEN : BLACK);
			DrawText("Enter Password (8+ chars, letters and numbers):", screenWidth / 2 - 200, screenHeight / 2 - 30, 20, passwordBorder);
			std::string maskedPassword(password.length(), '*');
			DrawText(maskedPassword.c_str(), screenWidth / 2 - 200, screenHeight / 2, 20, BLACK);
			DrawRectangleLines(screenWidth / 2 - 200, screenHeight / 2, 400, 30, passwordBorder);

			// Rysowanie przycisku "Submit"
			Texture2D buttonTex = resources.getButtonTexture();
			Vector2 mouse = GetMousePosition();
			Color submitColor = CheckCollisionPointRec(mouse, submitButton) ? GRAY : WHITE;
			DrawTexturePro(
				buttonTex,
				Rectangle{ 0, 0, static_cast<float>(buttonTex.width), static_cast<float>(buttonTex.height) },
				submitButton,
				Vector2{ 0, 0 },
				0.0f,
				submitColor
			);
			DrawText("Submit", submitButton.x + (submitButton.width - MeasureText("Submit", 20)) / 2, submitButton.y + 20, 20, BLACK);

			if (!errorMessage.empty()) {
				DrawText(errorMessage.c_str(), screenWidth / 2 - MeasureText(errorMessage.c_str(), 20) / 2, screenHeight / 2 + 50, 20, YELLOW);
			}

			// Reszta kodu bez zmian...
			Vector2 mousePos = GetMousePosition();

			int key = GetCharPressed();
			while (key > 0) {
				if ((key >= 32) && (key <= 125)) {
					if (enteringUsername && username.length() < 20) {
						username += static_cast<char>(key);
						usernameError = false;
						errorMessage = "";
					}
					else if (!enteringUsername && password.length() < 20) {
						password += static_cast<char>(key);
						passwordError = false;
						errorMessage = "";
					}
				}
				key = GetCharPressed();
			}

			if (IsKeyPressed(KEY_BACKSPACE)) {
				if (enteringUsername && !username.empty()) {
					username.pop_back();
					usernameError = false;
					errorMessage = "";
				}
				else if (!enteringUsername && !password.empty()) {
					password.pop_back();
					passwordError = false;
					errorMessage = "";
				}
			}

			if (IsKeyPressed(KEY_TAB)) {
				enteringUsername = !enteringUsername;
			}

			if (IsKeyPressed(KEY_ENTER) || (CheckCollisionPointRec(mousePos, submitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
				SignInResult result = auth.signIn(username, password);
				if (result == SignInResult::SUCCESS) {
					validInput = true;
				}
				else {
					usernameError = false;
					passwordError = false;
					switch (result) {
					case SignInResult::USERNAME_TAKEN:
						errorMessage = "Nazwa uzytkownika zajeta";
						usernameError = true;
						break;
					case SignInResult::INVALID_USERNAME:
						errorMessage = "Niepoprawna nazwa uzytkownika";
						usernameError = true;
						break;
					case SignInResult::INVALID_PASSWORD:
						errorMessage = "Niepoprawne haslo";
						passwordError = true;
						break;
					}
				}
			}

			EndDrawing();
		}
		return validInput ? username : "";
	}

	std::string handleLogIn(int screenWidth, int screenHeight, Resources& resources) {
		Authorization auth;
		std::string username, password;
		std::string errorMessage;
		bool usernameError = false;
		bool passwordError = false;
		bool loggedIn = false;
		bool enteringUsername = true;
		Rectangle submitButton = { static_cast<float>(screenWidth / 2 - 100), static_cast<float>(screenHeight / 2 + 100), 200, 60 };

		while (!WindowShouldClose() && !loggedIn) {
			BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawTexturePro(
				resources.getRegistrationBackground(),
				Rectangle{ 0, 0, static_cast<float>(resources.getRegistrationBackground().width), static_cast<float>(resources.getRegistrationBackground().height) },
				Rectangle{ 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
				Vector2{ 0, 0 },
				0.0f,
				WHITE
			);

			Color usernameBorder = usernameError ? YELLOW : (enteringUsername ? GREEN : BLACK);
			DrawText("Enter Username:", screenWidth / 2 - 100, screenHeight / 2 - 100, 20, usernameBorder);
			DrawText(username.c_str(), screenWidth / 2 - 100, screenHeight / 2 - 70, 20, BLACK);
			DrawRectangleLines(screenWidth / 2 - 100, screenHeight / 2 - 70, 200, 30, usernameBorder);

			Color passwordBorder = passwordError ? YELLOW : (!enteringUsername ? GREEN : BLACK);
			DrawText("Enter Password:", screenWidth / 2 - 100, screenHeight / 2 - 30, 20, passwordBorder);
			std::string maskedPassword(password.length(), '*');
			DrawText(maskedPassword.c_str(), screenWidth / 2 - 100, screenHeight / 2, 20, BLACK);
			DrawRectangleLines(screenWidth / 2 - 100, screenHeight / 2, 200, 30, passwordBorder);

			// Rysowanie przycisku "Submit"
			Texture2D buttonTex = resources.getButtonTexture();
			Vector2 mouse = GetMousePosition();
			Color submitColor = CheckCollisionPointRec(mouse, submitButton) ? GRAY : WHITE;
			DrawTexturePro(
				buttonTex,
				Rectangle{ 0, 0, static_cast<float>(buttonTex.width), static_cast<float>(buttonTex.height) },
				submitButton,
				Vector2{ 0, 0 },
				0.0f,
				submitColor
			);
			DrawText("Submit", submitButton.x + (submitButton.width - MeasureText("Submit", 20)) / 2, submitButton.y + 20, 20, BLACK);

			if (!errorMessage.empty()) {
				DrawText(errorMessage.c_str(), screenWidth / 2 - MeasureText(errorMessage.c_str(), 20) / 2, screenHeight / 2 + 50, 20, YELLOW);
			}

			// Reszta kodu bez zmian...
			Vector2 mousePos = GetMousePosition();

			int key = GetCharPressed();
			while (key > 0) {
				if ((key >= 32) && (key <= 125)) {
					if (enteringUsername && username.length() < 20) {
						username += static_cast<char>(key);
						usernameError = false;
						errorMessage = "";
					}
					else if (!enteringUsername && password.length() < 20) {
						password += static_cast<char>(key);
						passwordError = false;
						errorMessage = "";
					}
				}
				key = GetCharPressed();
			}

			if (IsKeyPressed(KEY_BACKSPACE)) {
				if (enteringUsername && !username.empty()) {
					username.pop_back();
					usernameError = false;
					errorMessage = "";
				}
				else if (!enteringUsername && !password.empty()) {
					password.pop_back();
					passwordError = false;
					errorMessage = "";
				}
			}

			if (IsKeyPressed(KEY_TAB)) {
				enteringUsername = !enteringUsername;
			}

			if (IsKeyPressed(KEY_ENTER) || (CheckCollisionPointRec(mousePos, submitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
				LogInResult result = auth.logIn(username, password);
				if (result == LogInResult::SUCCESS) {
					loggedIn = true;
				}
				else {
					usernameError = false;
					passwordError = false;
					switch (result) {
					case LogInResult::USER_NOT_FOUND:
						errorMessage = "Uzytkownik nieznaleziony";
						usernameError = true;
						break;
					case LogInResult::INCORRECT_PASSWORD:
						errorMessage = "Niepoprawne haslo";
						passwordError = true;
						break;
					}
				}
			}

			EndDrawing();
		}
		return loggedIn ? username : "";
	}
};