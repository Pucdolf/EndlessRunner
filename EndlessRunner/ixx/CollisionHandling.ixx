/**
 * @file CollisionHandling.ixx
 * @brief Modu³ obs³uguj¹cy wykrywanie kolizji w grze.
 *
 * Zawiera generyczn¹ funkcjê do sprawdzania kolizji miêdzy prostok¹tami z opcjonalnym paddingiem oraz koncept dla obiektów kolizyjnych.
 */

module;
#include "raylib.h"
#include <concepts>
export module CollisionHandlingModule;

/**
 * @concept Collidable
 * @brief Koncept dla obiektów, które dostarczaj¹ prostok¹t kolizji.
 *
 * Obiekty spe³niaj¹ce ten koncept musz¹ posiadaæ metodê `getCollisionRec`, która zwraca prostok¹t (`Rectangle`) reprezentuj¹cy obszar kolizji.
 * @tparam T Typ obiektu do sprawdzenia.
 */
export template<typename T>
concept Collidable = requires(T t) {
    { t.getCollisionRec() } -> std::convertible_to<Rectangle>;
};

/**
 * @brief Sprawdza kolizjê miêdzy dwoma obiektami kolizyjnymi z opcjonalnym paddingiem.
 * @tparam T Pierwszy typ obiektu (musi spe³niaæ koncept Collidable).
 * @tparam U Drugi typ obiektu (musi spe³niaæ koncept Collidable).
 * @param a Pierwszy obiekt kolizyjny (np. przeszkoda).
 * @param b Drugi obiekt kolizyjny (np. gracz).
 * @param padding Odstêp (padding) zmniejszaj¹cy obszar kolizji prostok¹ta pierwszego obiektu (domyœlnie 55.0f pikseli).
 * @return True, jeœli prostok¹ty kolizji (z uwzglêdnieniem paddingu) siê pokrywaj¹; false w przeciwnym razie.
 */
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