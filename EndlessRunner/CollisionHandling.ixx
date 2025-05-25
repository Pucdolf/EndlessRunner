module;
#include "raylib.h"
export module CollisionHandlingModule;

//import UtilitiesModule;
import <raylib.h>;

export bool obstacleCollision(const Rectangle& a, const Rectangle& rectB, float padding = 60.0f)
{
	Rectangle rectA = {
	  a.x + padding,
	  a.y + padding,
	  a.width - 2 * padding,
	  a.height - 2 * padding
	};

	return CheckCollisionRecs(rectA, rectB);
}
