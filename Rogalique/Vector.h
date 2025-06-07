#pragma once

namespace Rogalique {
template <typename T>
struct Vector2D {
    T x = (T)0;
    T y = (T)0;

    float GetVectorLength() { return sqrtf(x * x + y * y); }

    float DotProduct(const Vector2D<T>& vector) {
        return x * vector.x + y * vector.y;
    }
};

using Vector2Df = Vector2D<float>;
using Vector2Di = Vector2D<int>;
using Position = Vector2Df;

template <typename T>
Vector2D<T> operator+(const Vector2D<T>& left, const Vector2D<T>& right) {
    return {left.x + right.x, left.y + right.y};
}

template <typename T>
Vector2D<T> operator-(const Vector2D<T>& left, const Vector2D<T>& right) {
    return {left.x - right.x, left.y - right.y};
}

template <typename T>
Vector2D<T> operator-(const Vector2D<T>& left) {
    return {-left.x, -left.y};
}

template <typename T>
Vector2D<T> operator*(const Vector2D<T>& left, const Vector2D<T>& right) {
    return {left.x * right.x, left.y * right.y};
}

template <typename T>
Vector2D<T> operator*(const T scalar, const Vector2D<T>& right) {
    return {scalar * right.x, scalar * right.y};
}

template <typename T>
Vector2D<T> operator*(const Vector2D<T>& left, const T scalar) {
    return {left.x * scalar, left.y * scalar};
}

template <typename T>
bool operator==(const Vector2D<T>& left, const Vector2D<T>& right) {
    return left.x == right.x && left.y == right.y;
}

template <typename U, typename V>
U Convert(const V& v) {
    return {static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y)};
}
}  // namespace Rogalique
