module;
#include "raylib.h"
export module ObstacleModule;

export class Obstacle {

protected:
	Texture2D texture;
	Vector2 screenPos;

	float width{};
	float height{};

	const float scale{ 1.0f };
	int velocity{ -200 };

public:
	Obstacle() :velocity(-200), scale(1.f) {}
	virtual ~Obstacle() = default;
	virtual void init(const Texture2D& tex, float startX, float startY) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() const = 0;
	virtual Rectangle getColissionRec() const = 0;
	virtual float getPositionX() const = 0;



};