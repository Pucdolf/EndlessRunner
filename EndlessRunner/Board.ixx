#include "raylib.h"
export module BoardModule;

import <array>;
import PlayerModule;
import NebulaModule;
import UtilitiesModule;
import ResourcesModule;
import CollisionHandlingModule;


export class Board {
private:

	Player player{};
	static constexpr int amountOfNeb{ 10 };
	std::array<Nebula, amountOfNeb> nebulae;
	float finishLine{};
	Texture2D selectedDinoTex{};

public:

	void setDinoTex(const Texture2D& dinoTex) {
		selectedDinoTex = dinoTex;
	}

	void init(const Texture2D& dinoTex, const Texture2D& nebulaTex, int windowWidth, int windowHeight) {
		
		//Gdy nie wybrano w sklepie textury - domyslnie zielona
		if (selectedDinoTex.id == 0) {
			selectedDinoTex = dinoTex;
		}

		player.init(selectedDinoTex, windowWidth, windowHeight);

		for (int i = 0; i < amountOfNeb; i++)
		{

			float startX = static_cast<float>(windowWidth + 300 * i);
			float startY = static_cast<float>(windowHeight);
			nebulae[i].init(nebulaTex, startX, startY);

		}

		finishLine = nebulae.back().getPositionX();
	}

	void update(float deltaTime, int windowHeight) {
		player.update(deltaTime, windowHeight);

		for (auto& nebula : nebulae) {
			nebula.update(deltaTime);
		}

		finishLine += -200 * deltaTime;
	}

	void draw(/*const Texture2D& dinoTex, */const Texture2D& nebula) const {


		for (auto& nebula : nebulae)
			nebula.draw();

		player.draw();

	}


	bool checkLoss() const {
		for (const auto& nebula : nebulae) {
			if (nebulaCollision(nebula.getCollisionRec(), player.getCollisionRec())) {
				return true;
			}
		}
		return false;
	}

	bool checkWin() const {
		return player.getWorldPos().x >= finishLine;
	}
};