#pragma once
#include "Vector3D.h"
#include "Vector2D.h"
class VertexMesh
{

public:
	VertexMesh();
	VertexMesh(const Vector3D& position, const Vector2D& texcoord, const Vector3D& normal,const Vector3D& tangent, const Vector3D& binormal);
	VertexMesh(const VertexMesh& vertex);
	~VertexMesh();


public:
	Vector3D m_position;
	Vector2D m_texcoord;
	Vector3D m_normal;
	Vector3D m_tangent;
	Vector3D m_binormal;
};

