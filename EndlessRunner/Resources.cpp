/**
 * @file Resources.cpp
 * @brief Implementacja klasy Resources.
 */

module;
#include "raylib.h"
#include <filesystem>
#include <ranges>

module ResourcesModule;

void Resources::loadTextures() {
	loadTexture<Texture2D>(TextureKeys::UI::MENU_BG, "textures/main_menu_background.png");
	loadTexture<Texture2D>(TextureKeys::UI::LOADING_SCREEN_BG, "textures/loading_screen.png");
	loadTexture<Texture2D>(TextureKeys::UI::BAR_EMPTY, "textures/barempty.png");
	loadTexture<Texture2D>(TextureKeys::UI::BAR_FULL, "textures/barfill.png");
	loadTexture<Texture2D>(TextureKeys::UI::REGISTRATION_BG, "textures/registration_with_table.png");
	loadTexture<Texture2D>(TextureKeys::UI::SHOP_BG, "textures/shop.png");
	loadTexture<Texture2D>(TextureKeys::UI::LEADERBOARD, "textures/leaderboard.png");
	loadTexture<Texture2D>(TextureKeys::UI::HEART_ICON, "textures/life_icon.png");
	loadTexture<Texture2D>(TextureKeys::UI::LIFE_LOST_ICON, "textures/life_lost_icon.png");
	loadTexture<Texture2D>(TextureKeys::UI::NUMBERS, "textures/numbers.png");
	loadTexture<Texture2D>(TextureKeys::UI::BUTTON, "textures/button.png");
	loadTexture<Texture2D>(TextureKeys::UI::BANNER, "textures/banner4.png");
	loadTexture<Texture2D>(TextureKeys::Characters::DINO_SHADOW, "textures/Characters/shadow_2.png");
	loadTexture<Texture2D>(TextureKeys::Characters::DUST_RUN, "textures/Characters/dust.png");
	loadTexture<Texture2D>(TextureKeys::Characters::GREEN_DINO_IDLE, "textures/Characters/Player 1/p1_idle.png");
	loadTexture<Texture2D>(TextureKeys::Characters::BLUE_DINO_IDLE, "textures/Characters/Player 2/p2_idle.png");
	loadTexture<Texture2D>(TextureKeys::Characters::YELLOW_DINO_IDLE, "textures/Characters/Player 3/p3_idle.png");
	loadTexture<Texture2D>(TextureKeys::Characters::RED_DINO_IDLE, "textures/Characters/Player 4/p4_idle.png");
	loadTexture<Texture2D>(TextureKeys::Characters::GREEN_DINO_RUN, "textures/Characters/Player 1/p1_run.png");
	loadTexture<Texture2D>(TextureKeys::Characters::BLUE_DINO_RUN, "textures/Characters/Player 2/p2_run.png");
	loadTexture<Texture2D>(TextureKeys::Characters::YELLOW_DINO_RUN, "textures/Characters/Player 3/p3_run.png");
	loadTexture<Texture2D>(TextureKeys::Characters::RED_DINO_RUN, "textures/Characters/Player 4/p4_run.png");
	loadTexture<Texture2D>(TextureKeys::Characters::NEBULA, "textures/12_nebula_spritesheet.png");
	loadTexture<Texture2D>(TextureKeys::Characters::PTERO, "textures/pterosaur_spritesheet.png");
	loadTexture<Texture2D>(TextureKeys::Characters::BAT, "textures/BatIdleMoving.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_BG, "textures/Desert/bg_1.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_MG, "textures/Desert/bg_2.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_FG, "textures/Desert/bg_3.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_GR, "textures/Desert/ground.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_BG, "textures/Desert/night_bg_1.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_MG, "textures/Desert/night_bg_2.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_FG, "textures/Desert/night_bg_3.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_GR, "textures/Desert/night_ground.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_BG, "textures/Forest/bg_1.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_MG, "textures/Forest/bg_2.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_FG, "textures/Forest/bg_3.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_GR, "textures/Forest/ground.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_BG, "textures/Forest/night_bg_1.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_MG, "textures/Forest/night_bg_2.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_FG, "textures/Forest/night_bg_3.png");
	loadTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_GR, "textures/Forest/night_ground.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::SMALL_CACTUS, "textures/Desert/small_cactus.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::BIG_CACTUS, "textures/Desert/big_cactus.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::SKULLS, "textures/Desert/skulls.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::SKULLS2, "textures/Desert/skulls2.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::ROCK_D, "textures/Desert/rock.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_D, "textures/Desert/big_rock.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::ROCK_D_N, "textures/Desert/rock_n.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_D_N, "textures/Desert/big_rock_n.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::ROCK_F, "textures/Forest/rock_f.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_F, "textures/Forest/big_rock_f.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::SMALL_TREE, "textures/Forest/small_tree.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::BIG_TREE, "textures/Forest/big_tree.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::LOG, "textures/Forest/log.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::SPIKES, "textures/Forest/spikes.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::SMALL_TREE_N, "textures/Forest/small_tree_n.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::BIG_TREE_N, "textures/Forest/big_tree_n.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::LOG_N, "textures/Forest/log_n.png");
	loadTexture<Texture2D>(TextureKeys::Obstacles::SPIKES_N, "textures/Forest/spikes_n.png");
}

void Resources::unloadTextures() {
	for (auto& texture : textures | std::ranges::views::values) {
		UnloadTexture(texture);
	}
}