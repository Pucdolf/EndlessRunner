#include "raylib.h"
export module BoardModule;

import <array>;
import PlayerModule;
import DustModule;
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
	int selectedDinoFrameCount{ 6 };

	static constexpr int maxDustParticles{ 20 };
	std::array<Dust, maxDustParticles> dustParticles;
	float dustSpawnTimer{ 0.0f };
	float dustSpawnInterval{ 0.7f };

public:

	void setDinoTex(const Texture2D& dinoTex) {
		selectedDinoTex = dinoTex;
	}
	void setDinoFrameCount(int frameCount) {
		selectedDinoFrameCount = frameCount;
	}

	void init(const Texture2D& dinoTex, const Texture2D& nebulaTex, const Texture2D& dustTex, int windowWidth, int windowHeight) {

		//Gdy nie wybrano w sklepie textury - domyslnie zielona
		if (selectedDinoTex.id == 0) {
			selectedDinoTex = dinoTex;
			selectedDinoFrameCount = 6;
		}

		player.init(selectedDinoTex, selectedDinoFrameCount, windowWidth, windowHeight);

		for (int i = 0; i < amountOfNeb; i++){

			float startX = static_cast<float>(windowWidth + 300 * i);
			float startY = static_cast<float>(windowHeight);
			nebulae[i].init(nebulaTex, startX, startY);

		}

		for (auto& dust : dustParticles){
			dust.init(dustTex, 0, 0);
		}

		finishLine = nebulae.back().getPositionX();
	}

	void update(float deltaTime, int windowHeight) {
		player.update(deltaTime, windowHeight);

		for (auto& nebula : nebulae) {
			nebula.update(deltaTime);
		}

		for (auto& dust : dustParticles) {
			dust.update(deltaTime);
		}

		if (player.isOnGround(windowHeight)) {
			dustSpawnTimer += deltaTime;
			if (dustSpawnTimer >= dustSpawnInterval) {
				spawnDust();
				dustSpawnTimer = 0.f;
			}
		}
		finishLine += -200 * deltaTime;
	}

	void draw(const Texture2D& nebula) const {


		for (auto& nebula : nebulae)
			nebula.draw();


		for (const auto& dust : dustParticles)		{
			dust.draw();
		}


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

	private:
		void spawnDust() {
			for (auto& dust : dustParticles) {
				if (!dust.getIsActive()) {
					Vector2 playerPos = player.getPosition();
					float dustX = playerPos.x - 20;
					float dustY = playerPos.y + player.getCollisionRec().height - 50;
					dust.init(dust.getTexture(), dustX, dustY);
					break;
				}
			}
		}
};