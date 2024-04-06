#pragma once
#include <cmath>
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x,float y,float z);
	Vector3D(const Vector3D& vector);
	~Vector3D();
	float m_x, m_y, m_z;
	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta);

	Vector3D operator *(float num)const;

	Vector3D operator +(const Vector3D& vec) const;

	Vector3D operator -(const Vector3D& vec) const;

	static Vector3D normalize(const Vector3D& vec);

	static Vector3D cross(const Vector3D& v1, const Vector3D& v2);

private:
	
};

