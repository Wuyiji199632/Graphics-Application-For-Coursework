#pragma once
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x,float y,float z);
	Vector3D(const Vector3D& vector);
	~Vector3D();
	float m_x, m_y, m_z;
	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta);

	Vector3D operator *(float num);

	Vector3D operator +(Vector3D vec);

private:
	
};
