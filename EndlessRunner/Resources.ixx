#include "raylib.h"
export module ResourcesModule;

import <array>;

export class Resources {
private:

	//Menu
	Texture2D menuBackground{};
	//Loading screen
	Texture2D barEmpty{};
	Texture2D barFill{};
	//Shop
	Texture2D shopBackground{};
	Texture2D greenDinoIdle{};
	Texture2D blueDinoIdle{};
	Texture2D yellowDinoIdle{};
	Texture2D redDinoIdle{};
	//Game
	Texture2D gameBackground{};
	Texture2D gameMidground{};
	Texture2D gameForeground{};

	//Chaaracters
	Texture2D greenDinoRun{};
	Texture2D blueDinoRun{};
	Texture2D yellowDinoRun{};
	Texture2D redDinoRun{};

	//Obstacles
	Texture2D nebula{};

	//Stats
	Texture2D heartIcon{};
	Texture2D lifeLostIcon{};
	Texture2D numbersTexture{};


public:
	void loadTextures() {

		//Menu
		menuBackground = LoadTexture("textures/main_menu_background.png");
		//Loading screen
		barEmpty = LoadTexture("textures/barempty.png");
		barFill = LoadTexture("textures/barfill.png");
		//Shop
		shopBackground = LoadTexture("textures/shop_background.png");
		greenDinoIdle = LoadTexture("textures/Characters/Player 1/p1_idle.png");
		blueDinoIdle = LoadTexture("textures/Characters/Player 2/p2_idle.png");
		yellowDinoIdle = LoadTexture("textures/Characters/Player 3/p3_idle.png");
		redDinoIdle = LoadTexture("textures/Characters/Player 4/p4_idle.png");

		//Game
		gameBackground = LoadTexture("textures/far-buildings.png");
		gameMidground = LoadTexture("textures/back-buildings.png");
		gameForeground = LoadTexture("textures/foreground.png");

		//Characters
		greenDinoRun = LoadTexture("textures/Characters/Player 1/p1_run.png");
		blueDinoRun = LoadTexture("textures/Characters/Player 2/p2_run.png");
		yellowDinoRun = LoadTexture("textures/Characters/Player 3/p3_run.png");
		redDinoRun = LoadTexture("textures/Characters/Player 4/p4_run.png");


		//Obstacles
		nebula = LoadTexture("textures/12_nebula_spritesheet.png");

		//Stats
		heartIcon = LoadTexture("textures/life_icon.png");
		lifeLostIcon = LoadTexture("textures/life_lost_icon.png");
		numbersTexture = LoadTexture("textures/numbers.png");


	}

	void unloadTextures() {
		//Menu
		UnloadTexture(menuBackground);

		//Loading screen
		UnloadTexture(barEmpty);
		UnloadTexture(barFill);

		//Shop
		UnloadTexture(shopBackground);
		UnloadTexture(greenDinoIdle);
		UnloadTexture(blueDinoIdle);
		UnloadTexture(yellowDinoIdle);
		UnloadTexture(redDinoIdle);

		//Game
		UnloadTexture(gameBackground);
		UnloadTexture(gameMidground);
		UnloadTexture(gameForeground);

		//Characters
		UnloadTexture(greenDinoRun);
		UnloadTexture(blueDinoRun);
		UnloadTexture(yellowDinoRun);
		UnloadTexture(redDinoRun);
		UnloadTexture(nebula);

		//Stats
		UnloadTexture(heartIcon);
		UnloadTexture(lifeLostIcon);
		UnloadTexture(numbersTexture);

	}

	// Gettery
	Texture2D& getMenuBackground() { return menuBackground; }
	Texture2D& getShopBackground() { return shopBackground; }

	Texture2D& getGreenIdle() { return greenDinoIdle; }
	Texture2D& getBlueIdle() { return blueDinoIdle; }
	Texture2D& getYellowIdle() { return yellowDinoIdle; }
	Texture2D& getRedIdle() { return redDinoIdle; }

	Texture2D& getGameBackground() { return gameBackground; }
	Texture2D& getGameMidground() { return gameMidground; }
	Texture2D& getGameForeground() { return gameForeground; }

	Texture2D& getGreenDinoRun() { return greenDinoRun; }
	Texture2D& getBlueDinoRun() { return blueDinoRun; }
	Texture2D& getYellowDinoRun() { return yellowDinoRun; }
	Texture2D& getRedDinoRun() { return redDinoRun; }

	Texture2D& getNebula() { return nebula; }

	Texture2D& getHeartIcon() { return heartIcon; }
	Texture2D& getLifeLostIcon() { return lifeLostIcon; }
	Texture2D& getNumbersTexture() { return numbersTexture; }

	Texture2D& getBarEmpty() { return barEmpty; }
	Texture2D& getBarFill() { return barFill; }


};
