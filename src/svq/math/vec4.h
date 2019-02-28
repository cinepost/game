#ifndef VEC4__H
#define VEC4__H

#include <cmath>

namespace svq { namespace math {

template <class T>
class Vec4 {
public:
	T x, y, z, w;
	
	Vec4() :x(0), y(0), z(0), w(0) {}
	Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	
	Vec4& operator=(const Vec4& v) {
		x = v.x; y = v.y; z = v.z; w = v.w;
		return *this;
	}
	
	Vec4 operator+(Vec4& v) {
		return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	Vec4 operator-(Vec4& v) {
		return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	
	Vec4& operator+=(Vec4& v) {
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}
	Vec4& operator-=(Vec4& v) {
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;
		return *this;
	}
	
	Vec4 operator+(double s) {
		return Vec4(x + s, y + s, z + s, w + s);
	}
	
	Vec4 operator-(double s) {
		return Vec4(x - s, y - s, z - s, w - s);
	}
	
	Vec4 operator*(double s) {
		return Vec4(x * s, y * s, z * s, w * s);
	}

	Vec4 operator/(double s) {
		return Vec4(x / s, y / s, z / s, w / s);
	}
	
	Vec4& operator+=(double s) {
		x += s; y += s; z += s; w += s;
		return *this;
	}

	Vec4& operator-=(double s) {
		x -= s; y -= s; z -= s; w -= s;
		return *this;
	}
	
	Vec4& operator*=(double s) {
		x *= s; y *= s; z *= s; w *= s;
		return *this;
	}
	
	Vec4& operator/=(double s) {
		x /= s; y /= s; z /= s; w /= s;
		return *this;
	}
	
	void set(T x, T y, T z) {
		this->x = x; this->y = y; this->z = z; this->w = w;
	}
	
	void rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}
	
	Vec4& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}
	
	float dist(Vec4 v) const {
		Vec4 d(v.x - x, v.y - y, v.z - z, v.w - w);
		return d.length();
	}
	float length() const {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}
	
	
	static float dot(Vec4 v1, Vec4 v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}
	
};

typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;

} }

#endif // VEC4__H