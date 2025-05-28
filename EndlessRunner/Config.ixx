export module ConfigModule;

export namespace Config {
    // Istniej¹ce sta³e
    inline constexpr int DEFAULT_WINDOW_WIDTH = 1280;
    inline constexpr int DEFAULT_WINDOW_HEIGHT = 720;
    inline constexpr float PLAYER_SCALE = 5.0f;
    inline constexpr float OBSTACLE_SCALE = 4.0f;
    inline constexpr int BAT_FRAME_COUNT = 3;
    inline constexpr int PTERODACTYL_FRAME_COUNT = 4;
    inline constexpr int DUST_FRAME_COUNT = 5;
    inline constexpr float DUST_SPAWN_INTERVAL = 0.7f;
    inline constexpr float MIN_OBSTACLE_DISTANCE = 200.0f;
    inline constexpr float MAX_OBSTACLE_DISTANCE = 600.0f;
    inline constexpr float ANIMATION_UPDATE_TIME = 1.f / 12.f;
    inline constexpr float GRAVITY = 1000.f;
    inline constexpr float JUMP_VELOCITY = -600.f;
    inline constexpr int MAX_JUMPS = 2;

    // Nowe sta³e
    inline constexpr int MENU_BUTTON_COUNT = 5;           // Liczba przycisków w menu
    inline constexpr float BANNER_SCALE = 3.5f;            // Skala baneru
    inline constexpr float BANNER_Y = -25.0f;              // Pozycja Y baneru
    inline constexpr float UI_NUMB_SCALE = 3.5f;           // Skala ikon i cyfr w UI
    inline constexpr int PLAYER_LIVES = 3;                 // Liczba ¿yæ gracza
    inline constexpr float AUTH_BUTTON_WIDTH = 200.0f;     // Szerokoœæ przycisków autoryzacji
    inline constexpr float AUTH_BUTTON_HEIGHT = 80.0f;     // Wysokoœæ przycisków autoryzacji
    inline constexpr int LOADING_DURATION_MS = 2000;       // Czas ³adowania w ms
    inline constexpr int SHOP_DINO_COUNT = 4;              // Liczba dinozaurów w sklepie
    inline constexpr float SHOP_ANIMATION_UPDATE_TIME = 1.0f / 12.0f; // Czas aktualizacji animacji w sklepie
}