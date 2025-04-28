#include "raylib.h"
export module UtilitiesModule;

export struct AnimData
{
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};

//export bool isOnGround(const AnimData& data, int windowHeight)
//{
//	return data.pos.y >= windowHeight - data.rec.height;
//}

export AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
	data.runningTime += deltaTime;
	if (data.runningTime >= data.updateTime)
	{
		data.runningTime = 0.0f;
		data.rec.x = data.frame * data.rec.width;
		data.frame = (data.frame > maxFrame) ? 0 : data.frame + 1;
	}
	return data;
}
