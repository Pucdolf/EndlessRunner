#include "raylib.h"
import MenuModule;
import LoadingScreenModule;
import ResourcesModule;
import BoardModule;
import ShopModule;
import ConfigModule;

int main() {


    const int screenWidth = Config::DEFAULT_WINDOW_WIDTH;
    const int screenHeight = Config::DEFAULT_WINDOW_HEIGHT;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Dino Rush");

    Resources resources;
    Board board(resources);  // Przekazujemy resources do konstruktora Board
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
            //break;
        }
    }

    CloseWindow();
    return 0;
}