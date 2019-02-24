#pragma once

template<typename T>
struct Vector2 {
	T x, y;

	Vector2<T> operator=(const Vector2<T> &other) {
		if(this == &other)
			return *this;
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	bool operator==(const Vector2<T> &other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const Vector2<T> &other) const {
		return !(*this == other);
	}

	Vector2<T> operator*(const T &other) const {
		return Vector2<T>(this->x * other, this->y * other);
	}

	Vector2<T> operator/(const T &other) const {
		return Vector2<T>(this->x / other, this->y / other);
	}
	template<typename OT>
	Vector2<T> operator/(const OT &other) const {
		return Vector2<T>(this->x / other, this->y / other);
	}
	template<typename OT>
	Vector2<T> operator/(const Vector2<OT> &other) const {
		return Vector2<T>(this->x / other.x, this->y / other.y);
	}

	Vector2<T> operator-(const T &other) const {
		return Vector2<T>(this->x - other, this->y - other);
	}
	Vector2<T> operator-(const Vector2<T> &other) const {
		return Vector2<T>(this->x - other.x, this->y - other.y);
	}
	
	Vector2<T> operator+(const T &other) const {
		return Vector2<T>(this->x + other, this->y + other);
	}
	Vector2<T> &operator+=(const T &other) {
		return *this += Vector2<T>(other, other);
	}
	Vector2<T> operator+(const Vector2<T> &other) const {
		return Vector2<T>(this->x + other.x, this->y + other.y);
	}
	Vector2<T> &operator+=(const Vector2<T> &other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	template<typename OT>
	Vector2<T> operator+(const OT &other) const {
		return *this + Vector2<T>(other, other);
	}
	template<typename OT>
	Vector2<T> &operator+=(const OT &other) {
		this->x += (T)other;
		this->y += (T)other;
		return *this;
	}
	template<typename OT>
	Vector2<T> operator+(const Vector2<OT> &other) const {
		return *this + (Vector2<T>)other;
	}
	template<typename OT>
	Vector2<T> &operator+=(const Vector2<OT> &other) {
		return *this += (Vector2<T>)other;
	}

	template<typename OT>
	explicit operator Vector2<OT>() const {
		return Vector2<OT>((OT)this->x, (OT)this->y);
	}

	Vector2(T x, T y)
		: x(x), y(y)
	{}
};