#pragma once

template<typename T>
struct Vector2 {
	T x, y;

	bool operator==(const Vector2<T>& other) {
		return this->x == other.x && this->y == other.y;
	}
	bool operator!=(const Vector2<T>& other) {
		return !(*this == other);
	}
};