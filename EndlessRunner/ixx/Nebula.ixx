module;
#include "raylib.h"
export module NebulaModule;
import ResourcesModule;

export class Nebula
{
	Resources res;
	Texture2D texture{ res.getNebula() };
	Vector2 screenPos;
	//Vector2 worldPos{};

	float width{};
	float height{};

	int frame;
	const float maxFrames{ 8.f };
	float updateTime;
	float runningTime;
	const float scale{ 1.0f };

	int nebulaVel{ -200 };
	float finishLine;

public:
	void init(const Texture nebulaTex, float startX, float startY) {

		texture = nebulaTex;
		width = static_cast<float>(nebulaTex.width / maxFrames);
		height = static_cast<float> (nebulaTex.height / maxFrames);

		screenPos.x = startX;
		screenPos.y = startY - height * scale;
		frame = 0;
		updateTime = 1.0f / 16.0f;
		runningTime = 0.0f;
	}

	void update(float deltaTime) {

		screenPos.x += nebulaVel * deltaTime;
		updateAnimation(deltaTime);

	}


	void updateAnimation(float deltaTime) {

		runningTime += deltaTime;
		if (runningTime >= updateTime) {
			runningTime = 0.0f;
			frame = (frame > maxFrames) ? 0 : frame + 1;
		}
	}


	void draw() const {

		Rectangle source{ static_cast<float>(frame) * width, 0.0f, width, height };
		Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };
		DrawTexturePro(texture, source, dest, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	}

	Rectangle getCollisionRec() const {
		return Rectangle{ screenPos.x, screenPos.y, width * scale, height * scale };
	}

	float getPositionX() const { return screenPos.x; }
};