export module ConfigModule;

export namespace Config {
    // Sta³e dla gry
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
}