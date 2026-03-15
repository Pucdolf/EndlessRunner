#include "raylib.h"
#include <filesystem>
import MenuModule;
import LoadingScreenModule;
import ResourcesModule;
import BoardModule;
import ShopModule;
import ConfigModule;

int main() {
    // Ustawienie katalogu roboczego:
    // Jeśli folder 'textures' nie istnieje obok .exe (np. w Visual Studio), 
    // to nie zmieniaj katalogu, aby korzystać z folderu projektu.
    if (std::filesystem::exists(std::filesystem::path(GetApplicationDirectory()) / "textures")) {
        ChangeDirectory(GetApplicationDirectory());
    }

    const int screenWidth = Config::DEFAULT_WINDOW_WIDTH;
    const int screenHeight = Config::DEFAULT_WINDOW_HEIGHT;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Dino Rush");

    Resources resources;
    Board board(resources);
    Shop shop;

    LoadingScreen loader;
    std::string username;

    while (!WindowShouldClose()) {
        username = loader.show(screenWidth, screenHeight, resources, board, shop);
        if (!username.empty()) {
            Menu menu;
            menu.setContext(resources, board, shop);
            menu.setUsername(username);
            menu.showMenu(static_cast<int>(screenWidth), static_cast<int>(screenHeight));
        }
    }

    CloseWindow();
    return 0;
}