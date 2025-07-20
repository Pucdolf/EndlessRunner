/**
 * @file Config.ixx
 * @brief Moduł zawierający stałe konfiguracyjne gry.
 *
 * Definiuje namespace Config z wszystkimi stałymi używanymi w grze.
 */


export module ConfigModule;


/**
 * @namespace Config
 * @brief Namespace zawierający stałe konfiguracyjne gry.
 */
export namespace Config {
    /** @brief Domyślna szerokość okna gry (w pikselach). */
    inline constexpr int DEFAULT_WINDOW_WIDTH = 1280;
    /** @brief Domyślna wysokość okna gry (w pikselach). */
    inline constexpr int DEFAULT_WINDOW_HEIGHT = 720;
    /** @brief Skala sprite'a gracza. */
    inline constexpr float PLAYER_SCALE = 5.0f;
    /** @brief Skala sprite'ów przeszkód. */
    inline constexpr float OBSTACLE_SCALE = 4.0f;
    /** @brief Liczba klatek animacji nietoperza. */
    inline constexpr int BAT_FRAME_COUNT = 3;
    /** @brief Liczba klatek animacji pterodaktyla. */
    inline constexpr int PTERODACTYL_FRAME_COUNT = 4;
    /** @brief Liczba klatek animacji pyłu. */
    inline constexpr int DUST_FRAME_COUNT = 5;
    /** @brief Interwał spawnu pyłu (w sekundach). */
    inline constexpr float DUST_SPAWN_INTERVAL = 0.7f;
    /** @brief Minimalna odległość między przeszkodami (w pikselach). */
    inline constexpr float MIN_OBSTACLE_DISTANCE = 200.0f;
    /** @brief Maksymalna odległość między przeszkodami (w pikselach). */
    inline constexpr float MAX_OBSTACLE_DISTANCE = 400.0f;
    /** @brief Czas między zmianami klatek animacji (w sekundach). */
    inline constexpr float ANIMATION_UPDATE_TIME = 1.f / 12.f;
    /** @brief Przyspieszenie grawitacyjne (piksele/s²). */
    inline constexpr float GRAVITY = 1000.f;
    /** @brief Początkowa prędkość skoku (piksele/s). */
    inline constexpr float JUMP_VELOCITY = -600.f;
    /** @brief Maksymalna liczba skoków (podwójny skok). */
    inline constexpr int MAX_JUMPS = 2;

   /** @brief Liczba przycisków w menu głównym. */
    inline constexpr int MENU_BUTTON_COUNT = 5;
    /** @brief Skala baneru w menu. */
    inline constexpr float BANNER_SCALE = 3.5f;
    /** @brief Pozycja Y baneru w menu. */
    inline constexpr float BANNER_Y = -25.0f;
    /** @brief Skala ikon i cyfr w interfejsie użytkownika. */
    inline constexpr float UI_NUMB_SCALE = 3.5f;
    /** @brief Początkowa liczba żyć gracza. */
    inline constexpr int PLAYER_LIVES = 3;
    /** @brief Szerokość przycisków autoryzacji (w pikselach). */
    inline constexpr float AUTH_BUTTON_WIDTH = 200.0f;
    /** @brief Wysokość przycisków autoryzacji (w pikselach). */
    inline constexpr float AUTH_BUTTON_HEIGHT = 80.0f;
    /** @brief Czas trwania ekranu ładowania (w milisekundach). */
    inline constexpr int LOADING_DURATION_MS = 2000;
    /** @brief Liczba dinozaurów w sklepie. */
    inline constexpr int SHOP_DINO_COUNT = 4;
    /** @brief Czas aktualizacji animacji w sklepie (w sekundach). */
    inline constexpr float SHOP_ANIMATION_UPDATE_TIME = 1.0f / 12.0f;
}