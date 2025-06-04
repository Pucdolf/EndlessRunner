module;
#include "raylib.h"
#include <concepts>
export module CollisionHandlingModule;

// Concept dla obiektów z metod¹ getCollisionRec
export template<typename T>
concept Collidable = requires(T t) {
    { t.getCollisionRec() } -> std::convertible_to<Rectangle>;
};

export template<Collidable T, Collidable U>
bool obstacleCollision(const T& a, const U& b, float padding = 55.0f) {
    Rectangle rectA = a.getCollisionRec();
    Rectangle rectB = b.getCollisionRec();
    rectA.x += padding;
    rectA.y += padding;
    rectA.width -= 2 * padding;
    rectA.height -= 2 * padding;
    return CheckCollisionRecs(rectA, rectB);
}