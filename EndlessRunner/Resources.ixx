module;
#include "raylib.h"
#include <iostream>

export module ResourcesModule;
import <array>;
import <unordered_map>;
import <string>;
import <filesystem>;
import <ranges>;
import <concepts>;

export template<typename T>
concept TextureType = std::same_as<T, Texture2D>&& requires(T t) {
    { t.id } -> std::convertible_to<unsigned int>;
    { t.width } -> std::convertible_to<int>;
    { t.height } -> std::convertible_to<int>;
};

export class Resources {
private:
    std::unordered_map<std::string, Texture2D> textures;

    struct TextureKeys {
        struct UI {
            inline static const std::string MENU_BG = "menu_background";
            inline static const std::string LOADING_SCREEN_BG = "loading_screen_background";
            inline static const std::string BAR_EMPTY = "loading_bar_empty";
            inline static const std::string BAR_FULL = "loading_bar_full";
            inline static const std::string REGISTRATION_BG = "registration";
            inline static const std::string SHOP_BG = "shop_background";
            inline static const std::string LEADERBOARD = "leaderboard";
            inline static const std::string HEART_ICON = "heart_icon";
            inline static const std::string LIFE_LOST_ICON = "life_lost_icon";
            inline static const std::string NUMBERS = "numbers";
            inline static const std::string BUTTON = "button";
            inline static const std::string BANNER = "banner";
        };

        struct Characters {
            inline static const std::string DINO_SHADOW = "dino_shadow";
            inline static const std::string DUST_RUN = "dust_run";
            inline static const std::string GREEN_DINO_IDLE = "green_dino_idle";
            inline static const std::string BLUE_DINO_IDLE = "blue_dino_idle";
            inline static const std::string YELLOW_DINO_IDLE = "yellow_dino_idle";
            inline static const std::string RED_DINO_IDLE = "red_dino_idle";
            inline static const std::string GREEN_DINO_RUN = "green_dino_run";
            inline static const std::string BLUE_DINO_RUN = "blue_dino_run";
            inline static const std::string YELLOW_DINO_RUN = "yellow_dino_run";
            inline static const std::string RED_DINO_RUN = "red_dino_run";
            inline static const std::string NEBULA = "nebula";
            inline static const std::string PTERO = "pterosaur";
            inline static const std::string BAT = "bat";
        };

        struct Backgrounds {
            inline static const std::string GAME_BG = "game_background";
            inline static const std::string GAME_MG = "game_midground";
            inline static const std::string GAME_FG = "game_foreground";
            inline static const std::string DESERT_BG = "desert_background";
            inline static const std::string DESERT_MG = "desert_midground";
            inline static const std::string DESERT_FG = "desert_foreground";
            inline static const std::string DESERT_GR = "desert_ground";
            inline static const std::string DESERT_NIGHT_BG = "desert_night_background";
            inline static const std::string DESERT_NIGHT_MG = "desert_night_midground";
            inline static const std::string DESERT_NIGHT_FG = "desert_night_foreground";
            inline static const std::string DESERT_NIGHT_GR = "desert_night_ground";
            inline static const std::string FOREST_BG = "forest_background";
            inline static const std::string FOREST_MG = "forest_midground";
            inline static const std::string FOREST_FG = "forest_foreground";
            inline static const std::string FOREST_GR = "forest_ground";
            inline static const std::string FOREST_NIGHT_BG = "forest_night_background";
            inline static const std::string FOREST_NIGHT_MG = "forest_night_midground";
            inline static const std::string FOREST_NIGHT_FG = "forest_night_foreground";
            inline static const std::string FOREST_NIGHT_GR = "forest_night_ground";
        };

        struct Obstacles {
            inline static const std::string SMALL_CACTUS = "small_cactus";
            inline static const std::string BIG_CACTUS = "big_cactus";
            inline static const std::string SKULLS = "skulls";
            inline static const std::string SKULLS2 = "skulls2";
            inline static const std::string ROCK_D = "rock_d";
            inline static const std::string BIG_ROCK_D = "big_rock_d";
            inline static const std::string ROCK_D_N = "rock_d_n";
            inline static const std::string BIG_ROCK_D_N = "big_rock_d_n";
            inline static const std::string ROCK_F = "rock";
            inline static const std::string BIG_ROCK_F = "big_rock";
            inline static const std::string SMALL_TREE = "small_tree";
            inline static const std::string BIG_TREE = "big_tree";
            inline static const std::string LOG = "log";
            inline static const std::string SPIKES = "spikes";
            inline static const std::string SMALL_TREE_N = "small_tree_n";
            inline static const std::string BIG_TREE_N = "big_tree_n";
            inline static const std::string LOG_N = "log_n";
            inline static const std::string SPIKES_N = "spikes_n";
        };
    };

public:
    Resources() = default;

    template<TextureType T>
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

    void loadTextures() {
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

    void unloadTextures() {
        for (auto& texture : textures | std::ranges::views::values) {
            UnloadTexture(texture);
        }
    }

    template<TextureType T>
    T& getTexture(const std::string& key) {
        auto it = textures.find(key);
        if (it != textures.end()) {
            return it->second;
        }
        textures[key] = LoadTexture("textures/missing_texture.png");
        return textures[key];
    }

    Texture2D& getMenuBackground() { return getTexture<Texture2D>(TextureKeys::UI::MENU_BG); }
    Texture2D& getShopBackground() { return getTexture<Texture2D>(TextureKeys::UI::SHOP_BG); }
    Texture2D& getLoadingScreenBackground() { return getTexture<Texture2D>(TextureKeys::UI::LOADING_SCREEN_BG); }
    Texture2D& getBarEmpty() { return getTexture<Texture2D>(TextureKeys::UI::BAR_EMPTY); }
    Texture2D& getBarFill() { return getTexture<Texture2D>(TextureKeys::UI::BAR_FULL); }
    Texture2D& getRegistrationBackground() { return getTexture<Texture2D>(TextureKeys::UI::REGISTRATION_BG); }
    Texture2D& getShadowTexture() { return getTexture<Texture2D>(TextureKeys::Characters::DINO_SHADOW); }
    Texture2D& getGreenIdle() { return getTexture<Texture2D>(TextureKeys::Characters::GREEN_DINO_IDLE); }
    Texture2D& getBlueIdle() { return getTexture<Texture2D>(TextureKeys::Characters::BLUE_DINO_IDLE); }
    Texture2D& getYellowIdle() { return getTexture<Texture2D>(TextureKeys::Characters::YELLOW_DINO_IDLE); }
    Texture2D& getRedIdle() { return getTexture<Texture2D>(TextureKeys::Characters::RED_DINO_IDLE); }
    Texture2D& getGameBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::GAME_BG); }
    Texture2D& getGameMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::GAME_MG); }
    Texture2D& getGameForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::GAME_FG); }
    Texture2D& getDustRun() { return getTexture<Texture2D>(TextureKeys::Characters::DUST_RUN); }
    Texture2D& getGreenDinoRun() { return getTexture<Texture2D>(TextureKeys::Characters::GREEN_DINO_RUN); }
    Texture2D& getBlueDinoRun() { return getTexture<Texture2D>(TextureKeys::Characters::BLUE_DINO_RUN); }
    Texture2D& getYellowDinoRun() { return getTexture<Texture2D>(TextureKeys::Characters::YELLOW_DINO_RUN); }
    Texture2D& getRedDinoRun() { return getTexture<Texture2D>(TextureKeys::Characters::RED_DINO_RUN); }
    Texture2D& getNebula() { return getTexture<Texture2D>(TextureKeys::Characters::NEBULA); }
    Texture2D& getPtero() { return getTexture<Texture2D>(TextureKeys::Characters::PTERO); }
    Texture2D& getBat() { return getTexture<Texture2D>(TextureKeys::Characters::BAT); }
    Texture2D& getHeartIcon() { return getTexture<Texture2D>(TextureKeys::UI::HEART_ICON); }
    Texture2D& getLifeLostIcon() { return getTexture<Texture2D>(TextureKeys::UI::LIFE_LOST_ICON); }
    Texture2D& getNumbersTexture() { return getTexture<Texture2D>(TextureKeys::UI::NUMBERS); }
    Texture2D& getButtonTexture() { return getTexture<Texture2D>(TextureKeys::UI::BUTTON); }
    Texture2D& getLeaderboard() { return getTexture<Texture2D>(TextureKeys::UI::LEADERBOARD); }
    Texture2D& getBanner() { return getTexture<Texture2D>(TextureKeys::UI::BANNER); }
    Texture2D& getDesertBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_BG); }
    Texture2D& getDesertMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_MG); }
    Texture2D& getDesertForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_FG); }
    Texture2D& getDesertGround() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_GR); }
    Texture2D& getForestBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_BG); }
    Texture2D& getForestMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_MG); }
    Texture2D& getForestForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_FG); }
    Texture2D& getForestGround() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_GR); }
    Texture2D& getDesertNightBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_BG); }
    Texture2D& getDesertNightMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_MG); }
    Texture2D& getDesertNightForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_FG); }
    Texture2D& getDesertNightGround() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_GR); }
    Texture2D& getForestNightBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_BG); }
    Texture2D& getForestNightMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_MG); }
    Texture2D& getForestNightForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_FG); }
    Texture2D& getForestNightGround() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_GR); }
    Texture2D& getSmallCactus() { return getTexture<Texture2D>(TextureKeys::Obstacles::SMALL_CACTUS); }
    Texture2D& getBigCactus() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_CACTUS); }
    Texture2D& getSkulls() { return getTexture<Texture2D>(TextureKeys::Obstacles::SKULLS); }
    Texture2D& getSkulls2() { return getTexture<Texture2D>(TextureKeys::Obstacles::SKULLS2); }
    Texture2D& getRockDust() { return getTexture<Texture2D>(TextureKeys::Obstacles::ROCK_D); }
    Texture2D& getBigRockDust() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_D); }
    Texture2D& getRockDustNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::ROCK_D_N); }
    Texture2D& getBigRockDustNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_D_N); }
    Texture2D& getRockForest() { return getTexture<Texture2D>(TextureKeys::Obstacles::ROCK_F); }
    Texture2D& getBigRockForest() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_F); }
    Texture2D& getSmallTree() { return getTexture<Texture2D>(TextureKeys::Obstacles::SMALL_TREE); }
    Texture2D& getBigTree() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_TREE); }
    Texture2D& getLog() { return getTexture<Texture2D>(TextureKeys::Obstacles::LOG); }
    Texture2D& getSpikes() { return getTexture<Texture2D>(TextureKeys::Obstacles::SPIKES); }
    Texture2D& getSmallTreeNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::SMALL_TREE_N); }
    Texture2D& getBigTreeNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_TREE_N); }
    Texture2D& getLogNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::LOG_N); }
    Texture2D& getSpikesNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::SPIKES_N); }
};