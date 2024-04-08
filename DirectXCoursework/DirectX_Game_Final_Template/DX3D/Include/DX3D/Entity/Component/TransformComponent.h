#pragma once
#include <DX3D/Prerequisites.h>
#include <DX3D/Math/Vector2D.h>
#include <DX3D/Math/Vector3D.h>
#include <DX3D/Math/Vector4D.h>
#include <DX3D/Math/Matrix4x4.h>

#include <DX3D/Entity/Component/Component.h>
class Component;
class TransformComponent:public Component
{
public:
	TransformComponent();
	virtual~TransformComponent();


	void setPosition(const Vector3D& position);

	void setRotation(const Vector3D& rotation);

	void setScale(const Vector3D& scale);

	Vector3D getPosition();
	Vector3D getRotation();
	Vector3D getScale();
	void getWorldMatrix(Matrix4x4& mat);
protected:
	void updateWorldMatrix();

protected:
	Vector3D m_position,
		m_rotation,
		m_scale;

	Matrix4x4 m_worldMatrix;
	
};

