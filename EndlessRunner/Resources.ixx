#include "raylib.h"
export module ResourcesModule;

import <array>;

export class Resources {
private:
	std::array<Texture2D, 12> textures{};

public:
	void loadTextures() {
		textures[0] = LoadTexture("textures/Characters/Player 1/p1_run.png");
		textures[1] = LoadTexture("textures/12_nebula_spritesheet.png");
		textures[2] = LoadTexture("textures/far-buildings.png");
		textures[3] = LoadTexture("textures/back-buildings.png");
		textures[4] = LoadTexture("textures/foreground.png");
		textures[5] = LoadTexture("textures/life_icon.png");
		textures[6] = LoadTexture("textures/life_lost_icon.png");
		textures[7] = LoadTexture("textures/numbers.png");

		textures[8] = LoadTexture("textures/Characters/Player 1/p1_idle.png");
		textures[9] = LoadTexture("textures/Characters/Player 2/p2_idle.png");
		textures[10] = LoadTexture("textures/Characters/Player 3/p3_idle.png");
		textures[11] = LoadTexture("textures/Characters/Player 4/p4_idle.png");

	}

	Texture2D& getDino() { return textures[0]; }
	Texture2D& getNebula() { return textures[1]; }

	Texture2D& getBackground() { return textures[2]; }
	Texture2D& getMidground() { return textures[3]; }
	Texture2D& getForeground() { return textures[4]; }
	Texture2D& getLifeFull() { return textures[5]; }
	Texture2D& getLifeEmpty() { return textures[6]; }
	Texture2D& getNumbers() { return textures[7]; }

	Texture2D& getGreenIdle() { return textures[8]; }
	Texture2D& getBlueIdle() { return textures[9]; }
	Texture2D& getYellowIdle() { return textures[10]; }
	Texture2D& getRedIdle() { return textures[11]; }


	void unloadTextures() {
		for (auto& tex : textures) {
			UnloadTexture(tex);
		}
	}
};
