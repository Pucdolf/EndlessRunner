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
	loader.show(screenWidth, screenHeight, resources, board, shop);

	Menu menu;
	menu.setContext(resources, board, shop);
	menu.showMenu(screenWidth, screenHeight);
	return 0;
}