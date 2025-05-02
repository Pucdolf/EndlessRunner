module;
#include "raylib.h"
#include "chrono"

export module LoadingScreenModule;

import ResourcesModule;
import BoardModule;
import ShopModule;
import AuthModule;
//import <thread>;
//import <atomic>;

export class LoadingScreen {
private:

	Texture2D barEmpty;
	Texture2D barFill;
	bool loadingFinished = false;

public:
	void show(int screenWidth, int screenHeight, Resources& resources, Board& board, Shop& shop) {

		/*barEmpty = LoadTexture("textures/barempty.png");
		barFill = LoadTexture("textures/barfill.png");*/

		//std::atomic<int> progress = 0;

		auto startTime = std::chrono::high_resolution_clock::now();
		const int loadingDuration = 3000; //ms

		//NIE DZIALA
		/*std::thread loader([&]() {*/
		resources.loadTextures();
		//progress = 50;
		//board.init(resources.getPlayerRun(), resources.getNebula(), screenWidth, screenHeight);
		shop.init(resources, screenWidth, screenHeight);
		//progress = 100;
		//loadingFinished = true;
		//});
		//loader.detach();

		barEmpty = resources.getBarEmpty();
		barFill = resources.getBarFill();

		while (!loadingFinished && !WindowShouldClose()) {

			screenWidth = GetScreenWidth();
			screenHeight = GetScreenHeight();

			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
			float loadingProgress = static_cast<float>(duration.count()) / loadingDuration;

			//float percent = static_cast<float>(progress) / 100.f;

			if (loadingProgress > 1.f) {
				loadingProgress = 1.f;
				loadingFinished = true;
			}

			BeginDrawing();
			//ClearBackground(RAYWHITE);

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

    void showAuthTiles(int screenWidth, int screenHeight, Resources& resources) {
        
        constexpr float btnW = 200.0f;
        constexpr float btnH = 80.0f;

        float xLeft = screenWidth * 0.25f - btnW * 0.5f;
        float xRight = screenWidth * 0.75f - btnW * 0.5f;

        float yPos = screenHeight * 0.85f - btnH * 0.5f;

        Rectangle signInButton = { xLeft,  yPos, btnW, btnH };
        Rectangle logInButton = { xRight, yPos, btnW, btnH };
        
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

            // Draw Sign In button
            DrawRectangleRec(signInButton, LIGHTGRAY);
            DrawText("Sign In", static_cast<float>(signInButton.x + (signInButton.width - MeasureText("Sign In", 20)) / 2), static_cast<float>(signInButton.y + 30), 20, BLACK);

            // Draw Log In button
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

        while (!WindowShouldClose() && !validInput) {
            Vector2 mouse = GetMousePosition();

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Enter Username (3-20 chars, alphanumeric):", screenWidth / 2 - 200, screenHeight / 2 - 100, 20, BLACK);
            DrawText("Enter Password (8+ chars, letters and numbers):", screenWidth / 2 - 200, screenHeight / 2 - 50, 20, BLACK);

            if (auth.signIn(username, password)) {
                validInput = true;
            }

            EndDrawing();
        }
    }

    void handleLogIn(int screenWidth, int screenHeight) {
        AuthManager auth;
        std::string username, password;
        bool loggedIn = false;

        while (!WindowShouldClose() && !loggedIn) {
            Vector2 mouse = GetMousePosition();

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Enter Username:", screenWidth / 2 - 100, screenHeight / 2 - 100, 20, BLACK);
            DrawText("Enter Password:", screenWidth / 2 - 100, screenHeight / 2 - 50, 20, BLACK);

            if (auth.logIn(username, password)) {
                loggedIn = true;
            }

            EndDrawing();
        }
    }
};
