#pragma once
///
///	Currently supports float, double, int and unsigned int.
/// Add more types as needed.
///
namespace maths {

template<typename T>
struct vector2 final {
	static_assert(std::is_arithmetic<T>::value);

	T x = 0, y = 0;
	vector2() = default;
	constexpr vector2(T x, T y) : x(x), y(y) {}
	constexpr vector2(const vector2<int>& i) : x(T(i.x)), y(T(i.y)) {}
	constexpr vector2(const vector2<unsigned int>& i) : x(T(i.x)), y(T(i.y)) {}
	constexpr vector2(const vector2<float>& i) : x(T(i.x)), y(T(i.y)) {}
	constexpr vector2(const vector2<double>& i) : x(T(i.x)), y(T(i.y)) {}

	constexpr T& operator[](unsigned int index) {
		assert(index<2);
		return index == 0 ? x : y;
	}
	constexpr T operator[](unsigned int index) const {
		assert(index<2);
		return index==0 ? x : y;
	}

	constexpr vector2 operator-() const {
		return {-x, -y};
	}
	constexpr vector2 operator+(T o) const {
		return {x + o, y + o};
	}
	constexpr vector2 operator+(const vector2& o) const {
		return {x + o.x, y + o.y};
	}
	constexpr vector2 operator-(T o) const {
		return {x - o, y - o};
	}
	constexpr vector2 operator-(const vector2& o) const {
		return {x - o.x, y - o.y};
	}
	constexpr vector2 operator*(T o) const {
		return {x*o, y*o};
	}
	constexpr vector2 operator*(const vector2& o) const {
		return {x*o.x, y*o.y};
	}
	constexpr vector2 operator/(T o) const {
		return {x / o, y / o};
	}
	constexpr vector2 operator/(const vector2& o) const {
		return {x / o.x, y / o.y};
	}

	constexpr auto& operator+=(T o) {
		x += o; y += o;
		return *this;
	}
	constexpr auto& operator+=(const vector2& o) {
		x += o.x; y += o.y;
		return *this;
	}
	constexpr auto& operator-=(T o) {
		x -= o; y -= o;
		return *this;
	}
	constexpr auto& operator-=(const vector2& o) {
		x -= o.x; y -= o.y;
		return *this;
	}
	constexpr auto& operator*=(T o) {
		x *= o; y *= o;
		return *this;
	}
	constexpr auto& operator*=(const vector2& o) {
		x *= o.x; y *= o.y;
		return *this;
	}
	constexpr auto& operator/=(T o) {
		x /= o; y /= o;
		return *this;
	}
	constexpr auto& operator/=(const vector2& o) {
		x /= o.x; y /= o.y;
		return *this;
	}

	constexpr bool operator==(const T o) const {
		return x == o && y == o;
	}
	constexpr bool operator==(const vector2& o) const {
		return x==o.x && y==o.y;
	}
	constexpr bool operator!=(const T o) const {
		return !operator==(o);
	}
	constexpr bool operator!=(const vector2& o) const {
		return !operator==(o);
	}
	constexpr bool approx(const vector2& o) const {
		return approxEqual(x, o.x) && approxEqual(y, o.y);
	}

	constexpr bool anyLT(T v) const { return x<v || y<v; }
	constexpr bool anyLTE(T v) const { return x <= v || y <= v; }
	constexpr bool anyGT(T v) const { return x>v || y>v; }
	constexpr bool anyGTE(T v) const { return x >= v || y >= v; }
	constexpr bool anyLT(const vector2& v) const { return x<v.x || y<v.y; }
	constexpr bool anyLTE(const vector2& v) const { return x <= v.x || y <= v.y; }
	constexpr bool anyGT(const vector2& v) const { return x>v.x || y>v.y; }
	constexpr bool anyGTE(const vector2& v) const { return x >= v.x || y >= v.y; }

	constexpr bool allLT(T v) const { return x<v && y<v; }
	constexpr bool allLTE(T v) const { return x <= v && y <= v; }
	constexpr bool allGT(T v) const { return x>v && y>v; }
	constexpr bool allGTE(T v) const { return x >= v && y >= v; }
	constexpr bool allLT(const vector2& v) const { return x<v.x && y<v.y; }
	constexpr bool allLTE(const vector2& v) const { return x <= v.x && y <= v.y; }
	constexpr bool allGT(const vector2& v) const { return x>v.x && y>v.y; }
	constexpr bool allGTE(const vector2& v) const { return x >= v.x && y >= v.y; }

	constexpr T hadd() const { return x + y; }
	constexpr T hmul() const { return x * y; }

	vector2 floor() const {
		return { (T)::floor(x), (T)::floor(y) };
	}
	vector2 ceil() const {
		return { (T)::ceil(x), (T)::ceil(y) };
	}

	T min() const { return x<y ? x : y; }
	T max() const { return x>y ? x : y; }

	vector2 min(const vector2& o) const {
		return {x<o.x ? x : o.x, y<o.y ? y : o.y };
	}
	vector2 max(const vector2& o) const {
		return {x>o.x ? x : o.x, y>o.y ? y : o.y};
	}

	T dot(const vector2& o) const {
		return {x*o.x + y*o.y};
	}

	T length() const {
		return sqrt(lengthSquared());
	}
	T lengthSquared() const {
		return x*x + y*y;
	}
	T invLength() const {
		return 1 / length();
	}

	auto& normalise() {
		operator*=(invLength());
		return *this;
	}
	vector2 normalised() const {
		return operator*(invLength());
	}

	/// Returns 1/this
	vector2 reciprocal() const {
		return  {1 / x, 1 / y};
	}

	vector2 abs() const {
		return {std::abs(x), std::abs(y)};
	}

	/// Return the angle between this and vector v in radians.
	/// rad = acos(|v1|.|v2|)
	T angleTo(const vector2& v) const {
		return (T)acos(normalised().dot(v.normalised()));
	}

	/// returns a new vector2 which is perpendicular to this one (pointing to the left)
	vector2 left() const {
		return {-y, x};
	}
	vector2 right() const {
		return {y,-x};
	}

	std::string toString() const {
		char buf[64];
		const char* fmt = nullptr;
		if constexpr(std::is_floating_point<T>::value) {
			fmt = "[%.3f, %.3f]";
		} else if constexpr(std::is_signed<T>::value) {
			if constexpr(sizeof(T) == 8) {
				fmt = "[%lld, %lld]";
			} else {
				fmt = "[%d, %d]";
			}
		} else if constexpr(sizeof(T) == 8) {
			fmt = "[%llu, %llu]";
		} else {
			fmt = "[%u, %u]";
		}
		sprintf_s(buf, fmt, x, y);
		return std::string(buf);
	}
};

typedef vector2<int> int2;
typedef vector2<unsigned int> uint2;
typedef vector2<float> float2;
typedef vector2<double> double2;

}