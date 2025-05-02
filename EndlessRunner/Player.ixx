#include "raylib.h"

export module PlayerModule;

import ResourcesModule;
import UtilitiesModule;

export class Player
{

	Texture2D texture_run{ };
	Vector2 screenPos{};
	Vector2 worldPos{};

	float width{};
	float height{};

	float velocity{ 0 };
	float gravity{ 1000.f };
	float jumpVelocity{ -600.f };
	bool isInAir{ false };


	int frame{};
	float maxFrames{};
	float updateTime{};
	float runningTime{};
	const float scale{ 4.0f };


public:
	Player() = default;

	void init(const Texture2D& dinoTex, int frameCount, int windowWidth, int windowHeight) {

		maxFrames = static_cast<float>(frameCount);
		texture_run = dinoTex;

		width = static_cast<float>(dinoTex.width / maxFrames);
		height = static_cast<float> (dinoTex.height);

		screenPos.x = windowWidth / 2.f - (scale * width / 2.f);
		screenPos.y = windowHeight - (scale * height);

		frame = 0;
		updateTime = 1.0f / 12.0f;
		runningTime = 0.0;

	}

	void update(float deltaTime, int windowHeight) {

		if (isOnGround(windowHeight)) {
			velocity = 0.f;
			isInAir = false;
		}
		else {
			velocity += gravity * deltaTime;
			isInAir = true;
		}

		if (IsKeyPressed(KEY_SPACE) && !isInAir) {
			velocity += jumpVelocity;
		}

		screenPos.y += velocity * deltaTime;
		if (!isInAir)
		{
			updateAnimation(deltaTime);
		}

	}

	void updateAnimation(float deltaTime) {

		runningTime += deltaTime;
		if (runningTime >= updateTime)
		{
			runningTime = 0.0f;
			frame++;
			if (frame >= maxFrames) frame = 0;
		}
	}


	void draw() const {
		Rectangle source = { frame * width, 0.0f, width, height };
		Rectangle dest = { screenPos.x, screenPos.y, width * scale, height * scale };
		DrawTexturePro(texture_run, source, dest, Vector2{ 0, 0 }, 0.0f, WHITE);
	}

	Rectangle getCollisionRec() const {
		return Rectangle{
			screenPos.x,
			screenPos.y,
			width * scale,
			height * scale
		};
	}

	Vector2 getWorldPos() const { return worldPos; }

	Vector2 getPosition() const { return screenPos; }


	bool isOnGround(int windowHeight) {

		return screenPos.y >= windowHeight - height * scale;
	}

};
