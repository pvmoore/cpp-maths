#pragma once
///
///	Currently supports float, double, int and unsigned int.
/// Add more types as needed.
///
#include <cstdio>
namespace maths {

template<typename T>
struct vector3 final {
	static_assert(std::is_arithmetic<T>::value);

	T x = 0, y = 0, z = 0;
	vector3() = default;
	constexpr vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	constexpr vector3(const vector3<int>& i) : x(T(i.x)), y(T(i.y)), z(T(i.z)) {}
	constexpr vector3(const vector3<unsigned int>& i) : x(T(i.x)), y(T(i.y)), z(T(i.z)) {}
	constexpr vector3(const vector3<float>& i) : x(T(i.x)), y(T(i.y)), z(T(i.z)) {}
	constexpr vector3(const vector3<double>& i) : x(T(i.x)), y(T(i.y)), z(T(i.z)) {}

	constexpr T& operator[](unsigned int index) {
		assert(index<3);
		T* p = (&x) + index;
		return *p;
	}
	constexpr T operator[](unsigned int index) const {
		assert(index<3);
		const T* p = (&x) + index;
		return *p;
	}

	constexpr vector3 operator-() const {
		return {-x,-y,-z};
	}
	constexpr vector3 operator+(T o) const {
		return {x + o, y + o, z + o};
	}
	constexpr vector3 operator+(const vector3& o) const {
		return {x + o.x, y + o.y, z + o.z};
	}
	constexpr vector3 operator-(T o) const {
		return {x - o, y - o, z - o};
	}
	constexpr vector3 operator-(const vector3& o) const {
		return {x - o.x, y - o.y, z - o.z};
	}
	constexpr vector3 operator*(T o) const {
		return {x*o, y*o, z*o};
	}
	constexpr vector3 operator*(const vector3& o) const {
		return {x*o.x, y*o.y, z*o.z};
	}
	constexpr vector3 operator/(T o) const {
		return {x / o, y / o, z / o};
	}
	constexpr vector3 operator/(const vector3& o) const {
		return {x / o.x, y / o.y, z / o.z};
	}

	constexpr auto& operator+=(T o) {
		x += o; y += o; z += o;
		return *this;
	}
	constexpr auto& operator+=(const vector3& o) {
		x += o.x; y += o.y; z += o.z;
		return *this;
	}
	constexpr auto& operator-=(T o) {
		x -= o; y -= o; z -= o;
		return *this;
	}
	constexpr auto& operator-=(const vector3& o) {
		x -= o.x; y -= o.y; z -= o.z;
		return *this;
	}
	constexpr auto& operator*=(T o) {
		x *= o; y *= o; z *= o;
		return *this;
	}
	constexpr auto& operator*=(const vector3& o) {
		x *= o.x; y *= o.y; z *= o.z;
		return *this;
	}
	constexpr auto& operator/=(T o) {
		x /= o; y /= o; z /= o;
		return *this;
	}
	constexpr auto& operator/=(const vector3& o) {
		x /= o.x; y /= o.y; z /= o.z;
		return *this;
	}

	constexpr bool operator==(const T o) const {
		return x == o && y == o && z == o;
	}
	constexpr bool operator==(const vector3& o) const {
		return x == o.x && y == o.y && z == o.z; 
	}
	constexpr bool operator!=(const T o) const {
		return !operator==(o);
	}
	constexpr bool operator!=(const vector3& o) const {
		return !operator==(o);
	}
	constexpr bool approx(const vector3& o) const {
		return approxEqual(x, o.x) && approxEqual(y, o.y) && approxEqual(z, o.z);
	}

	constexpr bool anyLT(T v) const { return x<v || y<v || z<v; }
	constexpr bool anyLTE(T v) const { return x <= v || y <= v || z <= v; }
	constexpr bool anyGT(T v) const { return x>v || y>v || z>v; }
	constexpr bool anyGTE(T v) const { return x >= v || y >= v || z>= v; }
	constexpr bool anyLT(const vector3& v) const { return x<v.x || y<v.y || z<v.z; }
	constexpr bool anyLTE(const vector3& v) const { return x <= v.x || y <= v.y || z<= v.z; }
	constexpr bool anyGT(const vector3& v) const { return x>v.x || y>v.y || z>v.z; }
	constexpr bool anyGTE(const vector3& v) const { return x >= v.x || y >= v.y || z >= v.z; }

	constexpr bool allLT(T v) const { return x<v && y<v && z<v; }
	constexpr bool allLTE(T v) const { return x <= v && y <= v && z <= v; }
	constexpr bool allGT(T v) const { return x>v && y>v && z>v; }
	constexpr bool allGTE(T v) const { return x >= v && y >= v && z >= v; }
	constexpr bool allLT(const vector3& v) const { return x<v.x && y<v.y && z<v.z; }
	constexpr bool allLTE(const vector3& v) const { return x <= v.x && y <= v.y && z <= v.z; }
	constexpr bool allGT(const vector3& v) const { return x>v.x && y>v.y && z>v.z; }
	constexpr bool allGTE(const vector3& v) const { return x >= v.x && y >= v.y && z >= v.z; }

	constexpr T hadd() const { return x + y + z; }
	constexpr T hmul() const { return x * y * z; }

	vector3 floor() const {
		return {(T)::floor(x), (T)::floor(y), (T)::floor(z)};
	}
	vector3 ceil() const {
		return {(T)::ceil(x), (T)::ceil(y), (T)::ceil(z)};
	}

	T min() const { return std::min({x, y, z}); }
	T max() const { return std::max({x, y, z}); }

	vector3 min(const vector3& o) const {
		return {std::min(x, o.x), std::min(y, o.y), std::min(z, o.z)};
	}
	vector3 max(const vector3& o) const {
		return {std::max(x, o.x), std::max(y, o.y), std::max(z, o.z)};
	}

	T dot(const vector3& o) const {
		return {x*o.x + y*o.y + z*o.z};
	}
	T length() const {
		return sqrt(lengthSquared());
	}
	T lengthSquared() const {
		return x * x + y * y + z * z;
	}
	T invLength() const {
		return 1 / length();
	}

	auto& normalise() {
		operator*=(invLength());
		return *this;
	}
	vector3 normalised() const {
		return operator*(invLength());
	}

	/// Returns 1/this
	vector3 reciprocal() const {
		return  {1 / x, 1 / y, 1 / z};
	}

	/// U.cross(V).length == U.length * V.length * sin(a)
	/// where a is the angle between U amd V
	vector3 cross(const vector3& rhs) const {
		return {y*rhs.z - z*rhs.y,
				z*rhs.x - x*rhs.z,
				x*rhs.y - y*rhs.x};
	}
	/// Scalar triple product (this cross a) dot b
	T tripleProduct(const vector3& a, const vector3& b) const {
		return cross(a).dot(b);
	}

	vector3 abs() const {
		return {std::abs(x), std::abs(y), std::abs(z)};
	}

	///  True if this vector is approx parallel to rhs.
	///  Assumes this and rhs are unit vectors.
	bool isParallelTo(const vector3& rhs) {
		assert(approxEqual(length(), 1) && "Must be a unit vector");
		assert(approxEqual(rhs.length(), 1) && "rhs must be a unit vector");
		T d = dot(rhs);
		return approxEqual(d,1) || approxEqual(d, -1);
	}

	/// Return the angle between this and vector v in radians.
	/// v1.v2 / (|v1|.|v2|)
	T angleTo(const vector3& v) const {
		return (T)acos((dot(v) / (length() * v.length())));
	}

	/// Rotate by radians toward vector v
	void rotateTowards(const vector3& v, T radians) {
		this = rotatedTowards(v, radians);
	}
	/// Returns new vector3 rotated by radians toward vector v
	vector3 rotatedTowards(const vector3& v, T radians) const {
		auto v1 = left(v);
		auto v2 = cross(v1);
		auto v3 = normalised() * (T)cos(radians) +
			   v2.normalised() * (T)sin(radians);
		return v3 * length();
	}

	///  Assumes this, v1 and v2 all have the
	///  same origin ie (0,0,0).
	///  If result is positive then point is in front of
	///  the plane else it is behind it.
	T distanceFromPlane(const vector3& v1, const vector3& v2) const {
		const auto normal = v2.cross(v1).normalised();
		return normal.dot(*this);
	}

	vector3 rotatedAroundX(T radians) const {
		auto c = cos(radians);
		auto s = sin(radians);
		auto yy = y;
		auto zz = z;
		return {x, (T)(yy*c - zz * s), (T)(yy*s + zz * c)};
	}
	vector3 rotatedAroundY(T radians) const {
		auto c = cos(radians);
		auto s = sin(radians);
		auto xx = x;
		auto zz = z;
		return {(T)(xx*c + zz * s), y, (T)(-xx * s + zz * c)};
	}
	vector3 rotatedAroundZ(T radians) const {
		auto c = cos(radians);
		auto s = sin(radians);
		auto xx = x;
		auto yy = y;
		return {(T)(xx*c - yy * s), (T)(xx*s + yy * c), z};
	}

	/// Returns a new vector3 which is perpendicular to this and a.
	vector3 left(const vector3& a) const {
		return -cross(a);
	}
	/// Returns a new vector3 which is perpendicular to this and a (opposite to left).
	vector3 right(const vector3& a) const {
		return cross(a);
	}

	std::string toString(const char* fmt=nullptr) const {
		char buf[64];
		const char* format = nullptr;

		if constexpr(std::is_floating_point<T>::value) {
            format = "%.3f";
		} else if constexpr(std::is_signed<T>::value) {
			if constexpr(sizeof(T) == 8) {
                format = "%lld";
			} else {
                format = "%d";
			}
		} else if constexpr(sizeof(T) == 8) {
            format = "%llu";
		} else {
            format = "%u";
		}
        if(fmt) format = fmt;

        char fmtbuf[64];
        sprintf_s(fmtbuf, "[%s, %s, %s]", format, format, format);

		sprintf_s(buf, fmtbuf, x, y, z);
		return std::string(buf);
	}
};

typedef vector3<int> int3;
typedef vector3<unsigned int> uint3;
typedef vector3<float> float3;
typedef vector3<double> double3;

}