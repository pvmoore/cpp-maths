#pragma once
///
///	A column-major matrix implementation.
///
/// c[0] c[1] c[2] c[3]		
///   0    4    8   12    
///   1    5    9   13  
///   2    6   10   14  
///   3    7   11   15   
namespace maths {

template<typename T>
struct matrix4 final {
    static_assert(std::is_floating_point<T>::value);

    vector4<T> c[4];

    constexpr const T* ptr() { return (T*)&c[0]; }

    constexpr vector4<T>& operator[](unsigned int index) {
        assert(index < 4);
        return c[index];
    }
    constexpr const vector4<T>& operator[](unsigned int index) const {
        assert(index < 4);
        return c[index];
    }

    constexpr static matrix4 columnMajor(std::initializer_list<T> il) {
        assert(il.size() == 16);
        const T* v = il.begin();
        return {
            vector4<T>(v[0], v[1], v[2], v[3]),
            vector4<T>(v[4], v[5], v[6], v[7]),
            vector4<T>(v[8], v[9], v[10], v[11]),
            vector4<T>(v[12], v[13], v[14], v[15])
        };
    }
    constexpr static matrix4 rowMajor(std::initializer_list<T> il) {
        assert(il.size() == 16);
        const T* v = il.begin();
        return {
            vector4<T>(v[0], v[4], v[8], v[12]),
            vector4<T>(v[1], v[5], v[9], v[13]),
            vector4<T>(v[2], v[6], v[10], v[14]),
            vector4<T>(v[3], v[7], v[11], v[15])
        };
    }

    constexpr static matrix4 identity() {
        matrix4 m;
        m[0].x = m[1].y = m[2].z = m[3].w = 1.0f;
        return m;
    }
    constexpr static matrix4 translate(const vector3<T>& v) {
        auto m = identity();
        m[3][0] = v.x;
        m[3][1] = v.y;
        m[3][2] = v.z;
        return m;
    }
    constexpr static matrix4 scale(const vector3<T>& v) {
        matrix4 m;
        m[0][0] = v.x;
        m[1][1] = v.y;
        m[2][2] = v.z;
        m[3][3] = 1;
        return m;
    }
    constexpr static matrix4 rotateX(T radians) {
        auto m = matrix4::identity();
        T C = cos(radians);
        T S = sin(radians);
        m[1][1] = C;
        m[1][2] = S;
        m[2][1] = -S;
        m[2][2] = C;
        return m;
    }
    constexpr static matrix4 rotateY(T radians) {
        auto m = matrix4::identity();
        T C = cos(radians);
        T S = sin(radians);
        m[0][0] = C;
        m[0][2] = -S;
        m[2][0] = S;
        m[2][2] = C;
        return m;
    }
    constexpr static matrix4 rotateZ(T radians) {
        auto m = matrix4::identity();
        T C = cos(radians);
        T S = sin(radians);
        m[0][0] = C;
        m[0][1] = S;
        m[1][0] = -S;
        m[1][1] = C;
        return m;
    }
    constexpr static matrix4 lookAtLH(const vector3<T>& eye, const vector3<T>& target, const vector3<T>& up) {
        auto zaxis = (target - eye).normalised();
        auto xaxis = up.cross(zaxis).normalised();
        auto yaxis = zaxis.cross(xaxis);

        return columnMajor({
            xaxis.x, yaxis.x, zaxis.x, 0.0f,
            xaxis.y, yaxis.y, zaxis.y, 0.0f,
            xaxis.z, yaxis.z, zaxis.z, 0.0f,
            -xaxis.dot(eye), -yaxis.dot(eye), -zaxis.dot(eye), 1.0f
        });
    }
    constexpr static matrix4 lookAtRH(const vector3<T>& eye, const vector3<T>& target, const vector3<T>& up) {
        auto zaxis = (target - eye).normalised();
        auto xaxis = zaxis.cross(up).normalised();
        auto yaxis = xaxis.cross(zaxis);

        return columnMajor({
            xaxis.x, yaxis.x, -zaxis.x, 0.0f,
            xaxis.y, yaxis.y, -zaxis.y, 0.0f,
            xaxis.z, yaxis.z, -zaxis.z, 0.0f,
            -xaxis.dot(eye), -yaxis.dot(eye), zaxis.dot(eye), 1.0f
        });
    }
    constexpr static matrix4 orthoRH(T screenWidth, T screenHeight, T znear, T zfar) {
        T fRange = 1 / (zfar - znear);
        matrix4 m;
        m[0][0] = 2 / screenWidth;
        m[1][1] = 2 / screenHeight;
        m[2][2] = fRange;
        m[3][2] = fRange * znear;
        m[3][3] = 1;
        return m;
    }
    constexpr static matrix4 orthoLH(T screenWidth, T screenHeight, T nearZ, T zfar) {
        T fRange = 1 / (zfar - nearZ);
        matrix4 m;
        m[0][0] = 2 / screenWidth;
        m[1][1] = 2 / screenHeight;
        m[2][2] = fRange;
        m[3][2] = -fRange * nearZ;
        m[3][3] = 1;
        return m;
    }
    constexpr static matrix4 perspectiveFovLH(T fovyRadians, T aspect, T znear, T zfar) {
        T tanHalfFov = tan(fovyRadians / 2.0f);
        T yScale = 1.0f / tanHalfFov;
        T xScale = 1.0f / (aspect * tanHalfFov);

        return columnMajor({
            xScale, 0, 0, 0,
            0, yScale, 0, 0,
            0, 0, zfar / (zfar - znear), 1,
            0, 0, (-znear * zfar) / (zfar - znear), 0
        });
    }
    constexpr static matrix4 perspectiveFovRH(T fovyRadians, T aspect, T znear, T zfar) {
        T tanHalfFov = tan(fovyRadians / 2.0f);
        T yScale = 1.0f / tanHalfFov;
        T xScale = 1.0f / (aspect * tanHalfFov);

        return columnMajor({
            xScale, 0, 0, 0,
            0, yScale, 0, 0,
            0, 0, zfar / (znear - zfar), -1,
            0, 0, (-znear * zfar) / (zfar - znear), 0
        });
    }

    constexpr matrix4 operator-() const {
        return {-c[0], -c[1], -c[2], -c[3]};
    }
    constexpr matrix4 operator+(T v) const {
        return {c[0] + v, c[1] + v, c[2] + v, c[3] + v};
    }
    constexpr matrix4 operator-(T v) const {
        return {c[0] - v, c[1] - v, c[2] - v, c[3] - v};
    }
    constexpr matrix4 operator*(T v) const {
        return {c[0] * v, c[1] * v, c[2] * v, c[3] * v};
    }
    constexpr matrix4 operator/(T v) const {
        return {c[0] / v, c[1] / v, c[2] / v, c[3] / v};
    }

    constexpr matrix4 operator+(const matrix4& v) const {
        return {c[0] + v.c[0], c[1] + v.c[1], c[2] + v.c[2], c[3] + v.c[3]};
    }
    constexpr matrix4 operator-(const matrix4& v) const {
        return {c[0] - v.c[0], c[1] - v.c[1], c[2] - v.c[2], c[3] - v.c[3]};
    }
    constexpr matrix4 operator/(const matrix4& v) const {
        return operator*(inversed());
    }

    constexpr matrix4 operator*(const matrix4& o) const {
        return {
            c[0] * o.c[0].x + c[1] * o.c[0].y + c[2] * o.c[0].z + c[3] * o.c[0].w,
            c[0] * o.c[1].x + c[1] * o.c[1].y + c[2] * o.c[1].z + c[3] * o.c[1].w,
            c[0] * o.c[2].x + c[1] * o.c[2].y + c[2] * o.c[2].z + c[3] * o.c[2].w,
            c[0] * o.c[3].x + c[1] * o.c[3].y + c[2] * o.c[3].z + c[3] * o.c[3].w
        };
    }
    constexpr vector4<T> operator*(const vector4<T>& v) const {
        return (c[0] * v.x) +
            (c[1] * v.y) +
            (c[2] * v.z) +
            (c[3] * v.w);
    }

    constexpr matrix4 transposed() const {
        return matrix4::rowMajor({
            c[0][0], c[0][1], c[0][2], c[0][3],
            c[1][0], c[1][1], c[1][2], c[1][3],
            c[2][0], c[2][1], c[2][2], c[2][3],
            c[3][0], c[3][1], c[3][2], c[3][3]
        });
    }

    constexpr T determinant() const {
        return c[0][0] * c[1][1] * c[2][2] * c[3][3] - c[0][0] * c[1][1] * c[3][2] * c[2][3] + c[0][0] * c[2][1] * c[3][2] * c[1][3] - c[0][0] * c[2][1] * c[1][2] * c[3][3] +
            c[0][0] * c[3][1] * c[1][2] * c[2][3] - c[0][0] * c[3][1] * c[2][2] * c[1][3] - c[1][0] * c[2][1] * c[3][2] * c[0][3] + c[1][0] * c[2][1] * c[0][2] * c[3][3] -
            c[1][0] * c[3][1] * c[0][2] * c[2][3] + c[1][0] * c[3][1] * c[2][2] * c[0][3] - c[1][0] * c[0][1] * c[2][2] * c[3][3] + c[1][0] * c[0][1] * c[3][2] * c[2][3] +
            c[2][0] * c[3][1] * c[0][2] * c[1][3] - c[2][0] * c[3][1] * c[1][2] * c[0][3] + c[2][0] * c[0][1] * c[1][2] * c[3][3] - c[2][0] * c[0][1] * c[3][2] * c[1][3] +
            c[2][0] * c[1][1] * c[3][2] * c[0][3] - c[2][0] * c[1][1] * c[0][2] * c[3][3] - c[3][0] * c[0][1] * c[1][2] * c[2][3] + c[3][0] * c[0][1] * c[2][2] * c[1][3] -
            c[3][0] * c[1][1] * c[2][2] * c[0][3] + c[3][0] * c[1][1] * c[0][2] * c[2][3] - c[3][0] * c[2][1] * c[0][2] * c[1][3] + c[3][0] * c[2][1] * c[1][2] * c[0][3];
    }

    constexpr matrix4 inversed() const {
        T det = determinant();
        if(det == 0) det = 1; /// this matrix has no inverse
        T d = 1 / det;
        matrix4 result;
        result.c[0][0] = d * (c[1][1] * (c[2][2] * c[3][3] - c[3][2] * c[2][3]) + c[2][1] * (c[3][2] * c[1][3] - c[1][2] * c[3][3]) + c[3][1] * (c[1][2] * c[2][3] - c[2][2] * c[1][3]));
        result.c[0][1] = -d * (c[0][1] * (c[2][2] * c[3][3] - c[3][2] * c[2][3]) + c[2][1] * (c[3][2] * c[0][3] - c[0][2] * c[3][3]) + c[3][1] * (c[0][2] * c[2][3] - c[2][2] * c[0][3]));
        result.c[0][2] = d * (c[0][1] * (c[1][2] * c[3][3] - c[3][2] * c[1][3]) + c[1][1] * (c[3][2] * c[0][3] - c[0][2] * c[3][3]) + c[3][1] * (c[0][2] * c[1][3] - c[1][2] * c[0][3]));
        result.c[0][3] = -d * (c[0][1] * (c[1][2] * c[2][3] - c[2][2] * c[1][3]) + c[1][1] * (c[2][2] * c[0][3] - c[0][2] * c[2][3]) + c[2][1] * (c[0][2] * c[1][3] - c[1][2] * c[0][3]));
        result.c[1][0] = -d * (c[1][0] * (c[2][2] * c[3][3] - c[3][2] * c[2][3]) + c[2][0] * (c[3][2] * c[1][3] - c[1][2] * c[3][3]) + c[3][0] * (c[1][2] * c[2][3] - c[2][2] * c[1][3]));
        result.c[1][1] = d * (c[0][0] * (c[2][2] * c[3][3] - c[3][2] * c[2][3]) + c[2][0] * (c[3][2] * c[0][3] - c[0][2] * c[3][3]) + c[3][0] * (c[0][2] * c[2][3] - c[2][2] * c[0][3]));
        result.c[1][2] = -d * (c[0][0] * (c[1][2] * c[3][3] - c[3][2] * c[1][3]) + c[1][0] * (c[3][2] * c[0][3] - c[0][2] * c[3][3]) + c[3][0] * (c[0][2] * c[1][3] - c[1][2] * c[0][3]));
        result.c[1][3] = d * (c[0][0] * (c[1][2] * c[2][3] - c[2][2] * c[1][3]) + c[1][0] * (c[2][2] * c[0][3] - c[0][2] * c[2][3]) + c[2][0] * (c[0][2] * c[1][3] - c[1][2] * c[0][3]));
        result.c[2][0] = d * (c[1][0] * (c[2][1] * c[3][3] - c[3][1] * c[2][3]) + c[2][0] * (c[3][1] * c[1][3] - c[1][1] * c[3][3]) + c[3][0] * (c[1][1] * c[2][3] - c[2][1] * c[1][3]));
        result.c[2][1] = -d * (c[0][0] * (c[2][1] * c[3][3] - c[3][1] * c[2][3]) + c[2][0] * (c[3][1] * c[0][3] - c[0][1] * c[3][3]) + c[3][0] * (c[0][1] * c[2][3] - c[2][1] * c[0][3]));
        result.c[2][2] = d * (c[0][0] * (c[1][1] * c[3][3] - c[3][1] * c[1][3]) + c[1][0] * (c[3][1] * c[0][3] - c[0][1] * c[3][3]) + c[3][0] * (c[0][1] * c[1][3] - c[1][1] * c[0][3]));
        result.c[2][3] = -d * (c[0][0] * (c[1][1] * c[2][3] - c[2][1] * c[1][3]) + c[1][0] * (c[2][1] * c[0][3] - c[0][1] * c[2][3]) + c[2][0] * (c[0][1] * c[1][3] - c[1][1] * c[0][3]));
        result.c[3][0] = -d * (c[1][0] * (c[2][1] * c[3][2] - c[3][1] * c[2][2]) + c[2][0] * (c[3][1] * c[1][2] - c[1][1] * c[3][2]) + c[3][0] * (c[1][1] * c[2][2] - c[2][1] * c[1][2]));
        result.c[3][1] = d * (c[0][0] * (c[2][1] * c[3][2] - c[3][1] * c[2][2]) + c[2][0] * (c[3][1] * c[0][2] - c[0][1] * c[3][2]) + c[3][0] * (c[0][1] * c[2][2] - c[2][1] * c[0][2]));
        result.c[3][2] = -d * (c[0][0] * (c[1][1] * c[3][2] - c[3][1] * c[1][2]) + c[1][0] * (c[3][1] * c[0][2] - c[0][1] * c[3][2]) + c[3][0] * (c[0][1] * c[1][2] - c[1][1] * c[0][2]));
        result.c[3][3] = d * (c[0][0] * (c[1][1] * c[2][2] - c[2][1] * c[1][2]) + c[1][0] * (c[2][1] * c[0][2] - c[0][1] * c[2][2]) + c[2][0] * (c[0][1] * c[1][2] - c[1][1] * c[0][2]));
        return result;
    }

    std::string toString() const {
        char buf[256];
        sprintf_s(buf, "%5.2f %5.2f %5.2f %5.2f\n%5.2f %5.2f %5.2f %5.2f\n%5.2f %5.2f %5.2f %5.2f\n%5.2f %5.2f %5.2f %5.2f",
                  c[0].x, c[1].x, c[2].x, c[3].x,
                  c[0].y, c[1].y, c[2].y, c[3].y,
                  c[0].z, c[1].z, c[2].z, c[3].z,
                  c[0].w, c[1].w, c[2].w, c[3].w);
        return std::string(buf);
    }
};

typedef matrix4<float> matrix;
typedef matrix4<double> dmatrix;

}