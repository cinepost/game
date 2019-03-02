#ifndef VEC3__H
#define VEC3__H

#include <cmath>

namespace svq { namespace math {

template <class T>
class Vec3 {
public:
	T x, y, z;
	
	Vec3() :x(0), y(0), z(0) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}

	Vec3& operator=(const Vec3& v) {
		x = v.x; y = v.y; z = v.z;
		return *this;
	}
	
	Vec3 operator+(Vec3& v) {
		return Vec3(x + v.x, y + v.y, z + v.z);
	}
	Vec3 operator-(Vec3& v) {
		return Vec3(x - v.x, y - v.y, z - v.z);
	}
	
	Vec3& operator+=(Vec3& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	Vec3& operator-=(Vec3& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	
	Vec3 operator+(double s) {
		return Vec3(x + s, y + s, z + s);
	}
	
	Vec3 operator-(double s) {
		return Vec3(x - s, y - s, z - s);
	}
	
	Vec3 operator*(double s) {
		return Vec3(x * s, y * s, z * s);
	}

	Vec3 operator/(double s) {
		return Vec3(x / s, y / s, z / s);
	}
	
	Vec3& operator+=(double s) {
		x += s; y += s; z += s;
		return *this;
	}

	Vec3& operator-=(double s) {
		x -= s; y -= s; z -= s;
		return *this;
	}
	
	Vec3& operator*=(double s) {
		x *= s; y *= s; z *= s;
		return *this;
	}
	
	Vec3& operator/=(double s) {
		x /= s; y /= s; z /= s;
		return *this;
	}
	
	void set(T x, T y, T z) {
		this->x = x; this->y = y; this->z = z;
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
	
	Vec3& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}
	
	float dist(Vec3 v) const {
		Vec3 d(v.x - x, v.y - y, v.z - z);
		return d.length();
	}
	float length() const {
		return std::sqrt(x * x + y * y + z * z);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}
	
	
	static float dot(Vec3 v1, Vec3 v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	static Vec3 cross(Vec3 v1, Vec3 v2) {
		return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}
	
};

typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

} }

#endif // VEC3__H