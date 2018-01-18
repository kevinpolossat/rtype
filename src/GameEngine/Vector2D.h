#ifndef VEC2D_HPP
#define VEC2D_HPP

#include <cmath>

namespace ge {
	template <class T>
	class Vector2D {
	public:
		explicit Vector2D(T x = 0, T y = 0) : x(x), y(y) {}
		~Vector2D() = default;

		Vector2D<T> operator+(Vector2D<T> const & other) const {
			return Vector2D<T>(x + other.x, y + other.y);
		}

		Vector2D<T> operator-(Vector2D<T> const & other) const {
			return Vector2D<T>(x - other.x, y - other.y);
		}

		Vector2D<T> operator*(Vector2D<T> const & other) const {
			return Vector2D<T>(x * other.x, y * other.y);
		}

		Vector2D<T> operator*(T const other) const {
			return Vector2D<T>(x * other, y * other);
		}

		Vector2D<T> operator/(Vector2D<T> const & other) const {
			return Vector2D<T>(x / other.x, y / other.y);
		}

		Vector2D<T> operator/(T const other) const {
			return Vector2D<T>(x / other, y / other);
		}

		Vector2D<T> & operator=(Vector2D<T> const & other) {
			x = other.x;
			y = other.y;
			return (*this);
		}

		T length() const {
			return (std::sqrt((x * x) + (y * y)));
		}

		T dotProduct(Vector2D const & other) const {
			return ((x * other.x) + (this->y * other.y));
		}

		Vector2D<T> normalize() {
			x /= this->length();
			y /= this->length();
			return (*this);
		}

		T x;
		T y;
	};

	template<class T>
	bool operator==(Vector2D<T> const & lhs, Vector2D<T> const & rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
}

#endif
