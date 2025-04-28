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
	/*AnimData player;
	int velocity{ 0 };
	bool isInAir{ false };
	int gravity{ 1000 };
	int jumpVelocity{ -600 };*/

	Player player;
	static constexpr int amountOfNeb{ 10 };
	/*AnimData nebulae[amountOfNeb]{};
	int nebulaVel{ -200 };
	*/
	
	std::array<Nebula, amountOfNeb> nebulae;
	float finishLine;

public:
	void init(const Texture2D& dinoTex, const Texture2D& nebulaTex, int windowWidth, int windowHeight) {
		/*player.rec = { 0, 0, static_cast<float>(dinoTex.width / 6), static_cast<float>(dinoTex.height) };
		player.pos = { windowWidth / 2.0f - player.rec.width / 2.0f, static_cast<float>(windowHeight - player.rec.height) };
		player.frame = 0;
		player.updateTime = 1.0f / 12.0f;
		player.runningTime = 0;*/

		player.init(dinoTex, windowWidth, windowHeight);

		for (int i = 0; i < amountOfNeb; i++)
		{

			float startX = static_cast<float>(windowWidth + 300 * i);
			float startY = static_cast<float>(windowHeight);
			nebulae[i].init(nebulaTex, startX, startY);

		}

		/*for (int i = 0; i < amountOfNeb; i++) {
			nebulae[i].rec = { 0, 0, static_cast<float>(nebulaTex.width / 8), static_cast<float>(nebulaTex.height / 8) };
			nebulae[i].pos = { static_cast<float>(windowWidth + 300 * i), static_cast<float>(windowHeight - nebulae[i].rec.height) };
			nebulae[i].frame = 0;
			nebulae[i].updateTime = 1.0f / 16.0f;
			nebulae[i].runningTime = 0;
		}*/

		finishLine = nebulae.back().getPositionX();
	}

	void update(float deltaTime, int windowHeight) {
		/*if (isOnGround(player, windowHeight)) {
			velocity = 0;
			isInAir = false;
		}
		else {
			velocity += gravity * deltaTime;
			isInAir = true;
		}

		if (IsKeyPressed(KEY_SPACE) && !isInAir) {
			velocity += jumpVelocity;
		}*/
		player.update(deltaTime, windowHeight);

		for (auto& nebula : nebulae) {
			nebula.update(deltaTime);
		}

		finishLine += -200 * deltaTime;
		//player.pos.y += velocity * deltaTime;

		/*if (!isInAir) {
			player = updateAnimData(player, deltaTime, 5);
		}*/

		/*for (int i = 0; i < amountOfNeb; i++) {
			nebulae[i] = updateAnimData(nebulae[i], deltaTime, 7);
		}*/
	}

	void draw(const Texture2D& dinoTex, const Texture2D& nebula) const {

		/*for (int i = 0; i < amountOfNeb; i++) {
			DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
		}*/

		for (auto& nebula : nebulae)
			nebula.draw();
		//Rectangle source = { static_cast<float>(frame * frameWidth), 0,
		//static_cast<float>(frameWidth),
		//	static_cast<float>(frameHeight) };

		player.draw();
		//DrawTextureRec(dinoTex, player.rec, player.pos, WHITE);
	}


	bool checkLoss() const {
		for (const auto& nebula : nebulae){
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
