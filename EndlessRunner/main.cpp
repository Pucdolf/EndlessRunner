#include "raylib.h"
import MenuModule;
import LoadingScreenModule;
import ResourcesModule;
import BoardModule;
import ShopModule;

int main() {
	const int screenWidth = 1280;
	const int screenHeight = 720;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Dino Rush");

	Resources resources;
	Board board;
	Shop shop;

	LoadingScreen loader;
	std::string username;

	while (!WindowShouldClose()) {
		username = loader.show(screenWidth, screenHeight, resources, board, shop);
		if (!username.empty()) {
			Menu menu;
			menu.setContext(resources, board, shop);
			menu.setUsername(username);
			menu.showMenu(screenWidth, screenHeight);
			//break;
		}
	}


	CloseWindow();
	return 0;
}