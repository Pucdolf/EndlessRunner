module;
#include "raylib.h"
#include <iostream>  // Dodajemy do logowania

export module ResourcesModule;
import <array>;
import <unordered_map>;
import <string>;
import <filesystem>;
import <ranges>;
import <concepts>;

export class Resources {
private:
	std::unordered_map<std::string, Texture2D> textures;

	inline static const std::string MENU_BG = "menu_background";
	inline static const std::string LOADING_SCREEN_BG = "loading_screen_background";
	inline static const std::string BAR_EMPTY = "loading_bar_empty";
	inline static const std::string BAR_FULL = "loading_bar_full";
	inline static const std::string REGISTRATION_BG = "registration";
	inline static const std::string SHOP_BG = "shop_background";
	inline static const std::string DINO_SHADOW = "dino_shadow";
	inline static const std::string GREEN_DINO_IDLE = "green_dino_idle";
	inline static const std::string BLUE_DINO_IDLE = "blue_dino_idle";
	inline static const std::string YELLOW_DINO_IDLE = "yellow_dino_idle";
	inline static const std::string RED_DINO_IDLE = "red_dino_idle";
	inline static const std::string GAME_BG = "game_background";
	inline static const std::string GAME_MG = "game_midground";
	inline static const std::string GAME_FG = "game_foreground";
	inline static const std::string DUST_RUN = "dust_run";
	inline static const std::string GREEN_DINO_RUN = "green_dino_run";
	inline static const std::string BLUE_DINO_RUN = "blue_dino_run";
	inline static const std::string YELLOW_DINO_RUN = "yellow_dino_run";
	inline static const std::string RED_DINO_RUN = "red_dino_run";

	inline static const std::string HEART_ICON = "heart_icon";
	inline static const std::string LIFE_LOST_ICON = "life_lost_icon";
	inline static const std::string NUMBERS = "numbers";
	// Nowe t³a
	inline static const std::string DESERT_BG = "desert_background";
	inline static const std::string DESERT_MG = "desert_midground";
	inline static const std::string DESERT_FG = "desert_foreground";

	inline static const std::string DESERT_NIGHT_BG = "desert_night_background";
	inline static const std::string DESERT_NIGHT_MG = "desert_night_midground";
	inline static const std::string DESERT_NIGHT_FG = "desert_night_foreground";

	inline static const std::string FOREST_BG = "forest_background";
	inline static const std::string FOREST_MG = "forest_midground";
	inline static const std::string FOREST_FG = "forest_foreground";

	inline static const std::string FOREST_NIGHT_BG = "forest_night_background";
	inline static const std::string FOREST_NIGHT_MG = "forest_night_midground";
	inline static const std::string FOREST_NIGHT_FG = "forest_night_foreground";

	//OBSTACLES
	inline static const std::string NEBULA = "nebula";
	inline static const std::string PTERO = "pterosaur";
	inline static const std::string BAT = "bat";

	//pusytnia
	inline static const std::string SMALL_CACTUS = "small_cactus";
	/*inline static const std::string SMALL_CACTUS2= "small_cactus2";*/
	inline static const std::string BIG_CACTUS = "big_cactus";
	inline static const std::string SKULLS = "skulls";
	inline static const std::string SKULLS2 = "skulls2";
	//dzien
	inline static const std::string ROCK_D = "rock_d";
	inline static const std::string BIG_ROCK_D = "big_rock_d";
	//noc
	inline static const std::string ROCK_D_N = "rock_d_n";
	inline static const std::string BIG_ROCK_D_N = "big_rock_d_n";


	//las
	inline static const std::string ROCK_F = "rock";
	inline static const std::string BIG_ROCK_F = "big_rock";
	//dzien
	inline static const std::string SMALL_TREE = "small_tree";
	inline static const std::string BIG_TREE = "big_tree";
	inline static const std::string LOG = "log";
	inline static const std::string SPIKES = "spikes";
	//noc
	inline static const std::string SMALL_TREE_N = "small_tree_n";
	inline static const std::string BIG_TREE_N = "big_tree_n";
	inline static const std::string LOG_N = "log_n";
	inline static const std::string SPIKES_N = "spikes_n";


public:
	Resources() = default;

	void loadTextures() {
		loadTexture(MENU_BG, "textures/main_menu_background.png");
		loadTexture(LOADING_SCREEN_BG, "textures/loading_screen.png");
		loadTexture(BAR_EMPTY, "textures/barempty.png");
		loadTexture(BAR_FULL, "textures/barfill.png");
		loadTexture(REGISTRATION_BG, "textures/registration.png");
		loadTexture(SHOP_BG, "textures/shop.png");
		loadTexture(DINO_SHADOW, "textures/Characters/shadow_2.png");
		loadTexture(GREEN_DINO_IDLE, "textures/Characters/Player 1/p1_idle.png");
		loadTexture(BLUE_DINO_IDLE, "textures/Characters/Player 2/p2_idle.png");
		loadTexture(YELLOW_DINO_IDLE, "textures/Characters/Player 3/p3_idle.png");
		loadTexture(RED_DINO_IDLE, "textures/Characters/Player 4/p4_idle.png");
		loadTexture(GAME_BG, "textures/far-buildings.png");
		loadTexture(GAME_MG, "textures/back-buildings.png");
		loadTexture(GAME_FG, "textures/foreground - Copy.png");
		loadTexture(DUST_RUN, "textures/Characters/dust.png");
		loadTexture(GREEN_DINO_RUN, "textures/Characters/Player 1/p1_run.png");
		loadTexture(BLUE_DINO_RUN, "textures/Characters/Player 2/p2_run.png");
		loadTexture(YELLOW_DINO_RUN, "textures/Characters/Player 3/p3_run.png");
		loadTexture(RED_DINO_RUN, "textures/Characters/Player 4/p4_run.png");
		loadTexture(NEBULA, "textures/12_nebula_spritesheet.png");
		loadTexture(PTERO, "textures/pterosaur_spritesheet.png");
		loadTexture(BAT, "textures/BatIdleMoving.png");
		loadTexture(HEART_ICON, "textures/life_icon.png");
		loadTexture(LIFE_LOST_ICON, "textures/life_lost_icon.png");
		loadTexture(NUMBERS, "textures/numbers.png");
		// Wczytywanie nowych t³a
		loadTexture(DESERT_BG, "textures/Desert/bg_1.png");
		loadTexture(DESERT_MG, "textures/Desert/bg_2.png");
		loadTexture(DESERT_FG, "textures/Desert/bg_3 - Copy.png");

		loadTexture(FOREST_BG, "textures/Forest/bg_1.png");
		loadTexture(FOREST_MG, "textures/Forest/bg_2.png");
		loadTexture(FOREST_FG, "textures/Forest/bg_3 - Copy.png");

		loadTexture(DESERT_NIGHT_BG, "textures/Desert/night_bg_1.png");
		loadTexture(DESERT_NIGHT_MG, "textures/Desert/night_bg_2.png");
		loadTexture(DESERT_NIGHT_FG, "textures/Desert/night_bg_3 - Copy.png");

		loadTexture(FOREST_NIGHT_BG, "textures/Forest/night_bg_1.png");
		loadTexture(FOREST_NIGHT_MG, "textures/Forest/night_bg_2.png");
		loadTexture(FOREST_NIGHT_FG, "textures/Forest/night_bg_3 - Copy.png");

		//Przeszkody
		//pusytnia
		loadTexture(SMALL_CACTUS, "textures/Desert/small_cactus.png");
		/*inline static const std::string SMALL_CACTUS2= "small_cactus2";*/
		loadTexture(BIG_CACTUS, "textures/Desert/big_cactus.png");
		loadTexture(SKULLS, "textures/Desert/skulls.png");
		loadTexture(SKULLS2, "textures/Desert/skulls2.png");
		//dzien
		loadTexture(ROCK_D, "textures/Desert/rock.png");
		loadTexture(BIG_ROCK_D, "textures/Desert/big_rock.png");
		//noc
		loadTexture(ROCK_D_N, "textures/Desert/rock_n.png");
		loadTexture(BIG_ROCK_D_N, "textures/Desert/big_rock_n.png");


		//las

		loadTexture(ROCK_F, "textures/Forest/rock_f.png");
		loadTexture(BIG_ROCK_F, "textures/Forest/big_rock_f.png");
		//dzien
		loadTexture(SMALL_TREE, "textures/Forest/small_tree.png");
		loadTexture(BIG_TREE, "textures/Forest/big_tree.png");
		loadTexture(LOG, "textures/Forest/log.png");
		loadTexture(SPIKES, "textures/Forest/spikes.png");
		//noc
		loadTexture(SMALL_TREE_N, "textures/Forest/small_tree_n.png");
		loadTexture(BIG_TREE_N, "textures/Forest/big_tree_n.png");
		loadTexture(LOG_N, "textures/Forest/log_n.png");
		loadTexture(SPIKES_N, "textures/Forest/spikes_n.png");
	}



	void unloadTextures() {
		for (auto& texture : textures | std::ranges::views::values) {
			UnloadTexture(texture);
		}
	}

	Texture2D& getMenuBackground() { return getTexture(MENU_BG); }
	Texture2D& getShopBackground() { return getTexture(SHOP_BG); }
	Texture2D& getLoadingScreenBackground() { return getTexture(LOADING_SCREEN_BG); }
	Texture2D& getBarEmpty() { return getTexture(BAR_EMPTY); }
	Texture2D& getBarFill() { return getTexture(BAR_FULL); }
	Texture2D& getRegistrationBackground() { return getTexture(REGISTRATION_BG); }
	Texture2D& getShadowTexture() { return getTexture(DINO_SHADOW); }
	Texture2D& getGreenIdle() { return getTexture(GREEN_DINO_IDLE); }
	Texture2D& getBlueIdle() { return getTexture(BLUE_DINO_IDLE); }
	Texture2D& getYellowIdle() { return getTexture(YELLOW_DINO_IDLE); }
	Texture2D& getRedIdle() { return getTexture(RED_DINO_IDLE); }
	Texture2D& getGameBackground() { return getTexture(GAME_BG); }
	Texture2D& getGameMidground() { return getTexture(GAME_MG); }
	Texture2D& getGameForeground() { return getTexture(GAME_FG); }
	Texture2D& getDustRun() { return getTexture(DUST_RUN); }
	Texture2D& getGreenDinoRun() { return getTexture(GREEN_DINO_RUN); }
	Texture2D& getBlueDinoRun() { return getTexture(BLUE_DINO_RUN); }
	Texture2D& getYellowDinoRun() { return getTexture(YELLOW_DINO_RUN); }
	Texture2D& getRedDinoRun() { return getTexture(RED_DINO_RUN); }
	Texture2D& getNebula() { return getTexture(NEBULA); }
	Texture2D& getPtero() { return getTexture(PTERO); }
	Texture2D& getBat() { return getTexture(BAT); }
	Texture2D& getHeartIcon() { return getTexture(HEART_ICON); }
	Texture2D& getLifeLostIcon() { return getTexture(LIFE_LOST_ICON); }
	Texture2D& getNumbersTexture() { return getTexture(NUMBERS); }
	// Dostêp do nowych t³a
	Texture2D& getDesertBackground() { return getTexture(DESERT_BG); }
	Texture2D& getDesertMidground() { return getTexture(DESERT_MG); }
	Texture2D& getDesertForeground() { return getTexture(DESERT_FG); }

	Texture2D& getForestBackground() { return getTexture(FOREST_BG); }
	Texture2D& getForestMidground() { return getTexture(FOREST_MG); }
	Texture2D& getForestForeground() { return getTexture(FOREST_FG); }

	Texture2D& getDesertNightBackground() { return getTexture(DESERT_NIGHT_BG); }
	Texture2D& getDesertNightMidground() { return getTexture(DESERT_NIGHT_MG); }
	Texture2D& getDesertNightForeground() { return getTexture(DESERT_NIGHT_FG); }

	Texture2D& getForestNightBackground() { return getTexture(FOREST_NIGHT_BG); }
	Texture2D& getForestNightMidground() { return getTexture(FOREST_NIGHT_MG); }
	Texture2D& getForestNightForeground() { return getTexture(FOREST_NIGHT_FG); }



	//Przeszkody
		//pusytnia
	Texture2D& getSmallCactus() { return getTexture(SMALL_CACTUS); }

	Texture2D& getBigCactus() { return getTexture(BIG_CACTUS); }
	Texture2D& getSkulls() { return getTexture(SKULLS); }
	Texture2D& getSkulls2() { return getTexture(SKULLS2); }
	//dzien
	Texture2D& getRockDust() { return getTexture(ROCK_D); }
	Texture2D& getBigRockDust() { return getTexture(BIG_ROCK_D); }
	//noc
	Texture2D& getRockDustNight() { return getTexture(ROCK_D_N); }
	Texture2D& getBigRockDustNight() { return getTexture(BIG_ROCK_D_N); }

	//las
	Texture2D& getRockForest() { return getTexture(ROCK_F); }
	Texture2D& getBigRockForest() { return getTexture(BIG_ROCK_F); }
	//dzien
	Texture2D& getSmallTree() { return getTexture(SMALL_TREE); }
	Texture2D& getBigTree() { return getTexture(BIG_TREE); }
	Texture2D& getLog() { return getTexture(LOG); }
	Texture2D& getSpikes() { return getTexture(SPIKES); }
	//noc
	Texture2D& getSmallTreeNight() { return getTexture(SMALL_TREE_N); }
	Texture2D& getBigTreeNight() { return getTexture(BIG_TREE_N); }
	Texture2D& getLogNight() { return getTexture(LOG_N); }
	Texture2D& getSpikesNight() { return getTexture(SPIKES_N); }


private:
	void loadTexture(const std::string& key, const std::string& path) {
		if (std::filesystem::exists(path)) {
			textures[key] = LoadTexture(path.c_str());
			std::cout << "Loaded texture: " << key << " from " << path
				<< ", ID: " << textures[key].id
				<< ", Width: " << textures[key].width
				<< ", Height: " << textures[key].height << "\n";
			if (textures[key].id == 0 || textures[key].width == 0 || textures[key].height == 0) {
				std::cout << "Warning: Texture " << key << " has invalid dimensions, loading fallback!\n";
				textures[key] = LoadTexture("textures/missing_texture.png");
			}
		}
		else {
			std::cout << "Texture not found: " << path << ", using missing_texture.png\n";
			textures[key] = LoadTexture("textures/missing_texture.png");
			if (textures[key].id == 0 || textures[key].width == 0 || textures[key].height == 0) {
				std::cout << "Error: Fallback missing_texture.png failed!\n";
			}
		}
	}

	Texture2D& getTexture(const std::string& key) {
		auto it = textures.find(key);
		if (it != textures.end()) {
			return it->second;
		}
		textures[key] = LoadTexture("textures/missing_texture.png");
		return textures[key];
	}
};