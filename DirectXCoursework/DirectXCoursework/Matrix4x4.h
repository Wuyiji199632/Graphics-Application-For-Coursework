#pragma once
#include "Vector3D.h"

class Vector3D;

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	void setIdentity();
	void setTranslation(const Vector3D& translation);
	void setScale(const Vector3D& scale);
	void operator *=(const Matrix4x4& matrix);
	void setMatrix(const Matrix4x4& matrix);
	void setOrthoLH(float width, float height, float near_plane, float far_plane);

	void setRotationX(float x);

	void setRotationY(float y);

	void setRotationZ(float z);

public:
	float m_mat[4][4] = {};

private:
	friend class Vector3D;
};

