module;
#include"raylib.h"

export module DustModule;

export class Dust {
private:
	Texture2D texture{};
	Vector2 screenPos{};
	float width{};
	float height{};
	int frame{};

	const float maxFrames{ 5.f };
	float updateTime{ 1.f / 10.f };
	float runningTime{ 0.f };
	const float scale{ 3.f };
	bool isActive{ true };

public:
	Dust() = default;

	void init(const Texture2D dustTex, float startX, float startY)
	{
		texture = dustTex;
		width = static_cast<float>(dustTex.width / maxFrames);
		height = static_cast<float>(dustTex.height);
		screenPos.x = startX;
		screenPos.y = startY;

		frame = 0;
		runningTime = 0.f;
		isActive = true;

	}

	void update(float deltaTime) {

		if (!isActive) return;

		runningTime += deltaTime;
		if (runningTime >= updateTime) {
			runningTime = 0.f;
			frame++;
			if (frame >= maxFrames) {
				isActive = false;
				frame = maxFrames - 1;
			}
		}
	}

	void draw() const
	{
		if (!isActive) return;

		Rectangle source{ frame * width, 0.f, width, height };
		Rectangle dest{ screenPos.x, screenPos.y, width * scale, height * scale };

		float alpha = (frame < maxFrames - 1) ? 1.f : 1.f - (runningTime / updateTime);
		Color color = { 255,255,255, static_cast<unsigned char>(255 * alpha) };
		DrawTexturePro(texture, source, dest, Vector2{ 0.f,0.f }, 0.f, color);
	}

	bool getIsActive() const { return isActive; }
	const Texture2D& getTexture() const { return texture; }
	int getFrame() const { return frame; }
};