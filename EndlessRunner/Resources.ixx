module;
#include "raylib.h"

export module ResourcesModule;
import <array>;
import <unordered_map>;
import <string>;
import  <filesystem>;
import <ranges>;
import <concepts>; 

export class Resources {
private:
	//Mapa ze strukturami
	std::unordered_map<std::string, Texture2D> textures;

	// Stale klucze tekstur 
	//MENU
	inline static const std::string MENU_BG = "menu_background";
	//LOADING SCREEN
	inline static const std::string LOADING_SCREEN_BG = "loading_screen_background";
	inline static const std::string BAR_EMPTY = "loading_bar_empty";
	inline static const std::string BAR_FULL = "loading_bar_full";
	//REGISTRATION
	inline static const std::string REGISTRATION_BG = "registration";
	//SHOP
	inline static const std::string SHOP_BG = "shop_background";
	inline static const std::string DINO_SHADOW = "dino_shadow";
	inline static const std::string GREEN_DINO_IDLE = "green_dino_idle";
	inline static const std::string BLUE_DINO_IDLE = "blue_dino_idle";
	inline static const std::string YELLOW_DINO_IDLE = "yellow_dino_idle";
	inline static const std::string RED_DINO_IDLE = "red_dino_idle";
	//GAME
	inline static const std::string GAME_BG = "game_background";
	inline static const std::string GAME_MG = "game_midground";
	inline static const std::string GAME_FG = "game_foreground";
	//CHARACTERS
	inline static const std::string DUST_RUN = "dust_run";
	inline static const std::string GREEN_DINO_RUN = "green_dino_run";
	inline static const std::string BLUE_DINO_RUN = "blue_dino_run";
	inline static const std::string YELLOW_DINO_RUN = "yellow_dino_run";
	inline static const std::string RED_DINO_RUN = "red_dino_run";
	//OBSTACLES
	inline static const std::string NEBULA = "nebula";
	inline static const std::string PTERO = "pterosaur";
	inline static const std::string BAT = "bat";

	//STATS
	inline static const std::string HEART_ICON = "heart_icon";
	inline static const std::string LIFE_LOST_ICON = "life_lost_icon";
	inline static const std::string NUMBERS = "numbers";


public:
	Resources() = default;


	void loadTextures() {
		//MENU
		loadTexture(MENU_BG, "textures/main_menu_background.png");
		//LOADING SCREEN
		loadTexture(LOADING_SCREEN_BG, "textures/loading_screen.png");
		loadTexture(BAR_EMPTY, "textures/barempty.png");
		loadTexture(BAR_FULL, "textures/barfill.png");
		//REGISTRATION
		loadTexture(REGISTRATION_BG, "textures/registration.png");
		//SHOP
		loadTexture(SHOP_BG, "textures/shop.png");
		loadTexture(DINO_SHADOW, "textures/Characters/shadow_2.png");
		loadTexture(GREEN_DINO_IDLE, "textures/Characters/Player 1/p1_idle.png");
		loadTexture(BLUE_DINO_IDLE, "textures/Characters/Player 2/p2_idle.png");
		loadTexture(YELLOW_DINO_IDLE, "textures/Characters/Player 3/p3_idle.png");
		loadTexture(RED_DINO_IDLE, "textures/Characters/Player 4/p4_idle.png");
		//GAME
		loadTexture(GAME_BG, "textures/far-buildings.png");
		loadTexture(GAME_MG, "textures/back-buildings.png");
		loadTexture(GAME_FG, "textures/foreground.png");
		//CHARACTERS
		loadTexture(DUST_RUN, "textures/Characters/dust.png");
		loadTexture(GREEN_DINO_RUN, "textures/Characters/Player 1/p1_run.png");
		loadTexture(BLUE_DINO_RUN, "textures/Characters/Player 2/p2_run.png");
		loadTexture(YELLOW_DINO_RUN, "textures/Characters/Player 3/p3_run.png");
		loadTexture(RED_DINO_RUN, "textures/Characters/Player 4/p4_run.png");
		//OBSTACLES
		loadTexture(NEBULA, "textures/12_nebula_spritesheet.png");
		loadTexture(PTERO, "textures/pterosaur_sptitesheet.png");
		loadTexture(BAT, "textures/BatIdleMoving.png");

		//STATS
		loadTexture(HEART_ICON, "textures/life_icon.png");
		loadTexture(LIFE_LOST_ICON, "textures/life_lost_icon.png");
		loadTexture(NUMBERS, "textures/numbers.png");

	}

	void unloadTextures() {

		for (auto& texture : textures | std::ranges::views::values) {
			UnloadTexture(texture);
		}
		//textures.clear();

	}

	// Gettery
	Texture2D& getMenuBackground() { return getTexture(MENU_BG); }
	Texture2D& getShopBackground() { return getTexture(SHOP_BG); }
	//LOADING SCREEN
	Texture2D& getLoadingScreenBackground() { return getTexture(LOADING_SCREEN_BG); }
	Texture2D& getBarEmpty() { return getTexture(BAR_EMPTY); }
	Texture2D& getBarFill() { return getTexture(BAR_FULL); }
	//REGISTRATION
	Texture2D& getRegistrationBackground() { return getTexture(REGISTRATION_BG); }
	//SHOP
	Texture2D& getShadowTexture() { return getTexture(DINO_SHADOW); }
	Texture2D& getGreenIdle() { return getTexture(GREEN_DINO_IDLE); }
	Texture2D& getBlueIdle() { return getTexture(BLUE_DINO_IDLE); }
	Texture2D& getYellowIdle() { return getTexture(YELLOW_DINO_IDLE); }
	Texture2D& getRedIdle() { return getTexture(RED_DINO_IDLE); }
	//GAME
	Texture2D& getGameBackground() { return getTexture(GAME_BG); }
	Texture2D& getGameMidground() { return getTexture(GAME_MG); }
	Texture2D& getGameForeground() { return getTexture(GAME_FG); }
	//CHARACTERS
	Texture2D& getDustRun() { return getTexture(DUST_RUN); }
	Texture2D& getGreenDinoRun() { return getTexture(GREEN_DINO_RUN); }
	Texture2D& getBlueDinoRun() { return getTexture(BLUE_DINO_RUN); }
	Texture2D& getYellowDinoRun() { return getTexture(YELLOW_DINO_RUN); }
	Texture2D& getRedDinoRun() { return getTexture(RED_DINO_RUN); }
	//OBSTACLES
	Texture2D& getNebula() { return getTexture(NEBULA); }
	Texture2D& getPtero() { return getTexture(PTERO); }
	Texture2D& getBat() { return getTexture(BAT); }

	//STATS
	Texture2D& getHeartIcon() { return getTexture(HEART_ICON); }
	Texture2D& getLifeLostIcon() { return getTexture(LIFE_LOST_ICON); }
	Texture2D& getNumbersTexture() { return getTexture(NUMBERS); }


private:
	//Pomocnicza metoda do ladowania tekstury
	void loadTexture(const std::string& key, const std::string& path) {
		if (std::filesystem::exists(path)) {
			textures[key] = LoadTexture(path.c_str());
		}
		else {
			textures[key] = LoadTexture("textures/missing_texture.png");
		}
	}

	//Pomocnicza metoda do pobierania tekstury
	Texture2D& getTexture(const std::string& key) /*const */ {
		auto it = textures.find(key);
		if (it != textures.end()) {
			return it->second;
		}
		//throw std::runtime_error("Texture not found: " + key);
		textures[key] = LoadTexture("textures/missing_texture.png");
		return textures[key];
	}

};
