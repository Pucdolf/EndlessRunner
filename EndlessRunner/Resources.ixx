/**
 * @file Resources.ixx
 * @brief Modu³ definiuj¹cy klasê Resources, zarz¹dzaj¹c¹ teksturami gry.
 *
 * Klasa Resources odpowiada za ³adowanie, przechowywanie i udostêpnianie tekstur u¿ywanych w grze.
 */

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


/**
 * @concept TextureType
 * @brief Koncept dla typów tekstur zgodnych z Texture2D.
 *
 * Typy spe³niaj¹ce ten koncept musz¹ byæ typu Texture2D oraz posiadaæ pola `id`, `width` i `height` konwertowalne odpowiednio na `unsigned int` i `int`.
 * @tparam T Typ obiektu do sprawdzenia.
 */
export template<typename T>
concept TextureType = std::same_as<T, Texture2D>&& requires(T t) {
    { t.id } -> std::convertible_to<unsigned int>;
    { t.width } -> std::convertible_to<int>;
    { t.height } -> std::convertible_to<int>;
};

/**
 * @class Resources
 * @brief Klasa zarz¹dzaj¹ca teksturami gry.
 *
 * Odpowiada za ³adowanie, przechowywanie i udostêpnianie tekstur dla elementów gry, takich jak t³a, sprite'y i interfejs u¿ytkownika.
 */
export class Resources {
private:
    /** @brief Mapa przechowuj¹ca tekstury z kluczami w formacie std::string. */
    std::unordered_map<std::string, Texture2D> textures;

    /**
     * @struct TextureKeys
     * @brief Struktura grupuj¹ca klucze tekstur wed³ug kategorii.
     */
    struct TextureKeys {
        /**
          * @struct UI
          * @brief Klucze dla tekstur interfejsu u¿ytkownika.
          */
        struct UI {
            inline static const std::string MENU_BG = "menu_background"; /**< T³o menu g³ównego. */
            inline static const std::string LOADING_SCREEN_BG = "loading_screen_background"; /**< T³o ekranu ³adowania. */
            inline static const std::string BAR_EMPTY = "loading_bar_empty"; /**< Pusty pasek ³adowania. */
            inline static const std::string BAR_FULL = "loading_bar_full"; /**< Wype³niony pasek ³adowania. */
            inline static const std::string REGISTRATION_BG = "registration"; /**< T³o ekranu rejestracji. */
            inline static const std::string SHOP_BG = "shop_background"; /**< T³o sklepu. */
            inline static const std::string LEADERBOARD = "leaderboard"; /**< T³o tablicy wyników. */
            inline static const std::string HEART_ICON = "heart_icon"; /**< Ikona ¿ycia. */
            inline static const std::string LIFE_LOST_ICON = "life_lost_icon"; /**< Ikona utraconego ¿ycia. */
            inline static const std::string NUMBERS = "numbers"; /**< Tekstura cyfr. */
            inline static const std::string BUTTON = "button"; /**< Tekstura przycisku. */
            inline static const std::string BANNER = "banner"; /**< Tekstura baneru. */
        };

        /**
          * @struct Characters
          * @brief Klucze dla tekstur postaci i animacji.
          */
        struct Characters {
            inline static const std::string DINO_SHADOW = "dino_shadow"; /**< Cieñ dinozaura. */
            inline static const std::string DUST_RUN = "dust_run"; /**< Efekt py³u podczas biegu. */
            inline static const std::string GREEN_DINO_IDLE = "green_dino_idle"; /**< Zielony dinozaur w stanie bezczynnoœci. */
            inline static const std::string BLUE_DINO_IDLE = "blue_dino_idle"; /**< Niebieski dinozaur w stanie bezczynnoœci. */
            inline static const std::string YELLOW_DINO_IDLE = "yellow_dino_idle"; /**< ¯ó³ty dinozaur w stanie bezczynnoœci. */
            inline static const std::string RED_DINO_IDLE = "red_dino_idle"; /**< Czerwony dinozaur w stanie bezczynnoœci. */
            inline static const std::string GREEN_DINO_RUN = "green_dino_run"; /**< Zielony dinozaur podczas biegu. */
            inline static const std::string BLUE_DINO_RUN = "blue_dino_run"; /**< Niebieski dinozaur podczas biegu. */
            inline static const std::string YELLOW_DINO_RUN = "yellow_dino_run"; /**< ¯ó³ty dinozaur podczas biegu. */
            inline static const std::string RED_DINO_RUN = "red_dino_run"; /**< Czerwony dinozaur podczas biegu. */
            inline static const std::string NEBULA = "nebula"; /**< Tekstura mg³awicy. */
            inline static const std::string PTERO = "pterosaur"; /**< Tekstura pterodaktyla. */
            inline static const std::string BAT = "bat"; /**< Tekstura nietoperza. */
        };

        /**
          * @struct Backgrounds
          * @brief Klucze dla tekstur t³a gry.
          */
        struct Backgrounds {
            inline static const std::string GAME_BG = "game_background"; /**< Ogólne t³o gry. */
            inline static const std::string GAME_MG = "game_midground"; /**< Ogólny plan œrodkowy gry. */
            inline static const std::string GAME_FG = "game_foreground"; /**< Ogólny plan przedni gry. */
            inline static const std::string DESERT_BG = "desert_background"; /**< T³o pustyni za dnia. */
            inline static const std::string DESERT_MG = "desert_midground"; /**< Plan œrodkowy pustyni za dnia. */
            inline static const std::string DESERT_FG = "desert_foreground"; /**< Plan przedni pustyni za dnia. */
            inline static const std::string DESERT_GR = "desert_ground"; /**< Pod³o¿e pustyni za dnia. */
            inline static const std::string DESERT_NIGHT_BG = "desert_night_background"; /**< T³o pustyni w nocy. */
            inline static const std::string DESERT_NIGHT_MG = "desert_night_midground"; /**< Plan œrodkowy pustyni w nocy. */
            inline static const std::string DESERT_NIGHT_FG = "desert_night_foreground"; /**< Plan przedni pustyni w nocy. */
            inline static const std::string DESERT_NIGHT_GR = "desert_night_ground"; /**< Pod³o¿e pustyni w nocy. */
            inline static const std::string FOREST_BG = "forest_background"; /**< T³o lasu za dnia. */
            inline static const std::string FOREST_MG = "forest_midground"; /**< Plan œrodkowy lasu za dnia. */
            inline static const std::string FOREST_FG = "forest_foreground"; /**< Plan przedni lasu za dnia. */
            inline static const std::string FOREST_GR = "forest_ground"; /**< Pod³o¿e lasu za dnia. */
            inline static const std::string FOREST_NIGHT_BG = "forest_night_background"; /**< T³o lasu w nocy. */
            inline static const std::string FOREST_NIGHT_MG = "forest_night_midground"; /**< Plan œrodkowy lasu w nocy. */
            inline static const std::string FOREST_NIGHT_FG = "forest_night_foreground"; /**< Plan przedni lasu w nocy. */
            inline static const std::string FOREST_NIGHT_GR = "forest_night_ground"; /**< Pod³o¿e lasu w nocy. */
        };

        /**
          * @struct Obstacles
          * @brief Klucze dla tekstur przeszkód statycznych.
          */
        struct Obstacles {
            inline static const std::string SMALL_CACTUS = "small_cactus"; /**< Ma³y kaktus. */
            inline static const std::string BIG_CACTUS = "big_cactus"; /**< Du¿y kaktus. */
            inline static const std::string SKULLS = "skulls"; /**< Czaszki (pierwszy wariant). */
            inline static const std::string SKULLS2 = "skulls2"; /**< Czaszki (drugi wariant). */
            inline static const std::string ROCK_D = "rock_d"; /**< Kamieñ pustynny za dnia. */
            inline static const std::string BIG_ROCK_D = "big_rock_d"; /**< Du¿y kamieñ pustynny za dnia. */
            inline static const std::string ROCK_D_N = "rock_d_n"; /**< Kamieñ pustynny w nocy. */
            inline static const std::string BIG_ROCK_D_N = "big_rock_d_n"; /**< Du¿y kamieñ pustynny w nocy. */
            inline static const std::string ROCK_F = "rock"; /**< Kamieñ leœny. */
            inline static const std::string BIG_ROCK_F = "big_rock"; /**< Du¿y kamieñ leœny. */
            inline static const std::string SMALL_TREE = "small_tree"; /**< Ma³e drzewo leœne. */
            inline static const std::string BIG_TREE = "big_tree"; /**< Du¿e drzewo leœne. */
            inline static const std::string LOG = "log"; /**< K³oda leœna. */
            inline static const std::string SPIKES = "spikes"; /**< Kolce leœne. */
            inline static const std::string SMALL_TREE_N = "small_tree_n"; /**< Ma³e drzewo leœne w nocy. */
            inline static const std::string BIG_TREE_N = "big_tree_n"; /**< Du¿e drzewo leœne w nocy. */
            inline static const std::string LOG_N = "log_n"; /**< K³oda leœna w nocy. */
            inline static const std::string SPIKES_N = "spikes_n"; /**< Kolce leœne w nocy. */
        };
    };

public:
    /**
     * @brief Konstruktor domyœlny klasy Resources.
     */
    Resources() = default;

    /**
    * @brief £aduje teksturê i zapisuje j¹ pod okreœlonym kluczem.
    * @tparam T Typ tekstury (musi spe³niaæ koncept TextureType).
    * @param key Klucz, pod którym tekstura bêdzie przechowywana.
    * @param path Œcie¿ka do pliku tekstury.
    */
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

    /**
     * @brief £aduje wszystkie tekstury gry z predefiniowanych œcie¿ek.
     */
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

    /**
     * @brief Zwalnia wszystkie za³adowane tekstury z pamiêci.
     */
    void unloadTextures() {
        for (auto& texture : textures | std::ranges::views::values) {
            UnloadTexture(texture);
        }
    }


    /**
     * @brief Pobiera teksturê na podstawie klucza.
     * @tparam T Typ tekstury (musi spe³niaæ koncept TextureType).
     * @param key Klucz tekstury.
     * @return Referencja do tekstury; jeœli klucz nie istnieje, ³aduje domyœln¹ teksturê zastêpcz¹.
     */
    template<TextureType T>
    T& getTexture(const std::string& key) {
        auto it = textures.find(key);
        if (it != textures.end()) {
            return it->second;
        }
        textures[key] = LoadTexture("textures/missing_texture.png");
        return textures[key];
    }

    /** @brief Pobiera teksturê t³a menu. @return Referencja do tekstury. */
    Texture2D& getMenuBackground() { return getTexture<Texture2D>(TextureKeys::UI::MENU_BG); }
    /** @brief Pobiera teksturê t³a sklepu. @return Referencja do tekstury. */
    Texture2D& getShopBackground() { return getTexture<Texture2D>(TextureKeys::UI::SHOP_BG); }
    /** @brief Pobiera teksturê ekranu ³adowania. @return Referencja do tekstury. */
    Texture2D& getLoadingScreenBackground() { return getTexture<Texture2D>(TextureKeys::UI::LOADING_SCREEN_BG); }
    /** @brief Pobiera teksturê pustego paska ³adowania. @return Referencja do tekstury. */
    Texture2D& getBarEmpty() { return getTexture<Texture2D>(TextureKeys::UI::BAR_EMPTY); }
    /** @brief Pobiera teksturê pe³nego paska ³adowania. @return Referencja do tekstury. */
    Texture2D& getBarFill() { return getTexture<Texture2D>(TextureKeys::UI::BAR_FULL); }
    /** @brief Pobiera teksturê t³a rejestracji. @return Referencja do tekstury. */
    Texture2D& getRegistrationBackground() { return getTexture<Texture2D>(TextureKeys::UI::REGISTRATION_BG); }
    /** @brief Pobiera teksturê cienia dinozaura. @return Referencja do tekstury. */
    Texture2D& getShadowTexture() { return getTexture<Texture2D>(TextureKeys::Characters::DINO_SHADOW); }
    /** @brief Pobiera teksturê zielonego dinozaura w stanie bezczynnoœci. @return Referencja do tekstury. */
    Texture2D& getGreenIdle() { return getTexture<Texture2D>(TextureKeys::Characters::GREEN_DINO_IDLE); }
    /** @brief Pobiera teksturê niebieskiego dinozaura w stanie bezczynnoœci. @return Referencja do tekstury. */
    Texture2D& getBlueIdle() { return getTexture<Texture2D>(TextureKeys::Characters::BLUE_DINO_IDLE); }
    /** @brief Pobiera teksturê ¿ó³tego dinozaura w stanie bezczynnoœci. @return Referencja do tekstury. */
    Texture2D& getYellowIdle() { return getTexture<Texture2D>(TextureKeys::Characters::YELLOW_DINO_IDLE); }
    /** @brief Pobiera teksturê czerwonego dinozaura w stanie bezczynnoœci. @return Referencja do tekstury. */
    Texture2D& getRedIdle() { return getTexture<Texture2D>(TextureKeys::Characters::RED_DINO_IDLE); }
    /** @brief Pobiera teksturê ogólnego t³a gry. @return Referencja do tekstury. */
    Texture2D& getGameBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::GAME_BG); }
    /** @brief Pobiera teksturê ogólnego planu œrodkowego gry. @return Referencja do tekstury. */
    Texture2D& getGameMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::GAME_MG); }
    /** @brief Pobiera teksturê ogólnego przedniego planu gry. @return Referencja do tekstury. */
    Texture2D& getGameForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::GAME_FG); }
    /** @brief Pobiera teksturê animacji py³u podczas biegu. @return Referencja do tekstury. */
    Texture2D& getDustRun() { return getTexture<Texture2D>(TextureKeys::Characters::DUST_RUN); }
    /** @brief Pobiera teksturê zielonego dinozaura w biegu. @return Referencja do tekstury. */
    Texture2D& getGreenDinoRun() { return getTexture<Texture2D>(TextureKeys::Characters::GREEN_DINO_RUN); }
    /** @brief Pobiera teksturê niebieskiego dinozaura w biegu. @return Referencja do tekstury. */
    Texture2D& getBlueDinoRun() { return getTexture<Texture2D>(TextureKeys::Characters::BLUE_DINO_RUN); }
    /** @brief Pobiera teksturê ¿ó³tego dinozaura w biegu. @return Referencja do tekstury. */
    Texture2D& getYellowDinoRun() { return getTexture<Texture2D>(TextureKeys::Characters::YELLOW_DINO_RUN); }
    /** @brief Pobiera teksturê czerwonego dinozaura w biegu. @return Referencja do tekstury. */
    Texture2D& getRedDinoRun() { return getTexture<Texture2D>(TextureKeys::Characters::RED_DINO_RUN); }
    /** @brief Pobiera teksturê mg³awicy. @return Referencja do tekstury. */
    Texture2D& getNebula() { return getTexture<Texture2D>(TextureKeys::Characters::NEBULA); }
    /** @brief Pobiera teksturê pterozaura. @return Referencja do tekstury. */
    Texture2D& getPtero() { return getTexture<Texture2D>(TextureKeys::Characters::PTERO); }
    /** @brief Pobiera teksturê nietoperza. @return Referencja do tekstury. */
    Texture2D& getBat() { return getTexture<Texture2D>(TextureKeys::Characters::BAT); }
    /** @brief Pobiera teksturê ikony ¿ycia. @return Referencja do tekstury. */
    Texture2D& getHeartIcon() { return getTexture<Texture2D>(TextureKeys::UI::HEART_ICON); }
    /** @brief Pobiera teksturê ikony utraconego ¿ycia. @return Referencja do tekstury. */
    Texture2D& getLifeLostIcon() { return getTexture<Texture2D>(TextureKeys::UI::LIFE_LOST_ICON); }
    /** @brief Pobiera teksturê liczb. @return Referencja do tekstury. */
    Texture2D& getNumbersTexture() { return getTexture<Texture2D>(TextureKeys::UI::NUMBERS); }
    /** @brief Pobiera teksturê przycisku. @return Referencja do tekstury. */
    Texture2D& getButtonTexture() { return getTexture<Texture2D>(TextureKeys::UI::BUTTON); }
    /** @brief Pobiera teksturê tablicy wyników. @return Referencja do tekstury. */
    Texture2D& getLeaderboard() { return getTexture<Texture2D>(TextureKeys::UI::LEADERBOARD); }
    /** @brief Pobiera teksturê baneru. @return Referencja do tekstury. */
    Texture2D& getBanner() { return getTexture<Texture2D>(TextureKeys::UI::BANNER); }
    /** @brief Pobiera teksturê t³a pustyni za dnia. @return Referencja do tekstury. */
    Texture2D& getDesertBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_BG); }
    /** @brief Pobiera teksturê œrodkowego planu pustyni za dnia. @return Referencja do tekstury. */
    Texture2D& getDesertMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_MG); }
    /** @brief Pobiera teksturê przedniego planu pustyni za dnia. @return Referencja do tekstury. */
    Texture2D& getDesertForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_FG); }
    /** @brief Pobiera teksturê ziemi pustyni za dnia. @return Referencja do tekstury. */
    Texture2D& getDesertGround() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_GR); }
    /** @brief Pobiera teksturê t³a lasu za dnia. @return Referencja do tekstury. */
    Texture2D& getForestBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_BG); }
    /** @brief Pobiera teksturê œrodkowego planu lasu za dnia. @return Referencja do tekstury. */
    Texture2D& getForestMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_MG); }
    /** @brief Pobiera teksturê przedniego planu lasu za dnia. @return Referencja do tekstury. */
    Texture2D& getForestForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_FG); }
    /** @brief Pobiera teksturê ziemi lasu za dnia. @return Referencja do tekstury. */
    Texture2D& getForestGround() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_GR); }
    /** @brief Pobiera teksturê t³a pustyni w nocy. @return Referencja do tekstury. */
    Texture2D& getDesertNightBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_BG); }
    /** @brief Pobiera teksturê œrodkowego planu pustyni w nocy. @return Referencja do tekstury. */
    Texture2D& getDesertNightMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_MG); }
    /** @brief Pobiera teksturê przedniego planu pustyni w nocy. @return Referencja do tekstury. */
    Texture2D& getDesertNightForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_FG); }
    /** @brief Pobiera teksturê ziemi pustyni w nocy. @return Referencja do tekstury. */
    Texture2D& getDesertNightGround() { return getTexture<Texture2D>(TextureKeys::Backgrounds::DESERT_NIGHT_GR); }
    /** @brief Pobiera teksturê t³a lasu w nocy. @return Referencja do tekstury. */
    Texture2D& getForestNightBackground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_BG); }
    /** @brief Pobiera teksturê œrodkowego planu lasu w nocy. @return Referencja do tekstury. */
    Texture2D& getForestNightMidground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_MG); }
    /** @brief Pobiera teksturê przedniego planu lasu w nocy. @return Referencja do tekstury. */
    Texture2D& getForestNightForeground() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_FG); }
    /** @brief Pobiera teksturê ziemi lasu w nocy. @return Referencja do tekstury. */
    Texture2D& getForestNightGround() { return getTexture<Texture2D>(TextureKeys::Backgrounds::FOREST_NIGHT_GR); }
    /** @brief Pobiera teksturê ma³ego kaktusa. @return Referencja do tekstury. */
    Texture2D& getSmallCactus() { return getTexture<Texture2D>(TextureKeys::Obstacles::SMALL_CACTUS); }
    /** @brief Pobiera teksturê du¿ego kaktusa. @return Referencja do tekstury. */
    Texture2D& getBigCactus() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_CACTUS); }
    /** @brief Pobiera teksturê czaszek (wariant 1). @return Referencja do tekstury. */
    Texture2D& getSkulls() { return getTexture<Texture2D>(TextureKeys::Obstacles::SKULLS); }
    /** @brief Pobiera teksturê czaszek (wariant 2). @return Referencja do tekstury. */
    Texture2D& getSkulls2() { return getTexture<Texture2D>(TextureKeys::Obstacles::SKULLS2); }
    /** @brief Pobiera teksturê kamienia (pustynia za dnia). @return Referencja do tekstury. */
    Texture2D& getRockDust() { return getTexture<Texture2D>(TextureKeys::Obstacles::ROCK_D); }
    /** @brief Pobiera teksturê du¿ego kamienia (pustynia za dnia). @return Referencja do tekstury. */
    Texture2D& getBigRockDust() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_D); }
    /** @brief Pobiera teksturê kamienia (pustynia w nocy). @return Referencja do tekstury. */
    Texture2D& getRockDustNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::ROCK_D_N); }
    /** @brief Pobiera teksturê du¿ego kamienia (pustynia w nocy). @return Referencja do tekstury. */
    Texture2D& getBigRockDustNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_D_N); }
    /** @brief Pobiera teksturê kamienia (las). @return Referencja do tekstury. */
    Texture2D& getRockForest() { return getTexture<Texture2D>(TextureKeys::Obstacles::ROCK_F); }
    /** @brief Pobiera teksturê du¿ego kamienia (las). @return Referencja do tekstury. */
    Texture2D& getBigRockForest() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_ROCK_F); }
    /** @brief Pobiera teksturê ma³ego drzewa (las za dnia). @return Referencja do tekstury. */
    Texture2D& getSmallTree() { return getTexture<Texture2D>(TextureKeys::Obstacles::SMALL_TREE); }
    /** @brief Pobiera teksturê du¿ego drzewa (las za dnia). @return Referencja do tekstury. */
    Texture2D& getBigTree() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_TREE); }
    /** @brief Pobiera teksturê k³ody (las za dnia). @return Referencja do tekstury. */
    Texture2D& getLog() { return getTexture<Texture2D>(TextureKeys::Obstacles::LOG); }
    /** @brief Pobiera teksturê kolców (las za dnia). @return Referencja do tekstury. */
    Texture2D& getSpikes() { return getTexture<Texture2D>(TextureKeys::Obstacles::SPIKES); }
    /** @brief Pobiera teksturê ma³ego drzewa (las w nocy). @return Referencja do tekstury. */
    Texture2D& getSmallTreeNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::SMALL_TREE_N); }
    /** @brief Pobiera teksturê du¿ego drzewa (las w nocy). @return Referencja do tekstury. */
    Texture2D& getBigTreeNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::BIG_TREE_N); }
    /** @brief Pobiera teksturê k³ody (las w nocy). @return Referencja do tekstury. */
    Texture2D& getLogNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::LOG_N); }
    /** @brief Pobiera teksturê kolców (las w nocy). @return Referencja do tekstury. */
    Texture2D& getSpikesNight() { return getTexture<Texture2D>(TextureKeys::Obstacles::SPIKES_N); }
};