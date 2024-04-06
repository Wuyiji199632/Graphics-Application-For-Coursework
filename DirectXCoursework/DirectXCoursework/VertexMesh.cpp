#include "VertexMesh.h"

VertexMesh::VertexMesh() :m_position(), m_texcoord(),m_normal()
{
}

VertexMesh::VertexMesh(const Vector3D& position, 
	const Vector2D& texcoord, const Vector3D& normal,
	const Vector3D& tangent, 
	const Vector3D& binormal) :m_position(position),
	m_texcoord(texcoord),
	m_normal(normal),
	m_tangent(tangent),
	m_binormal(binormal)
{
}

VertexMesh::VertexMesh(const VertexMesh& vertex) :
m_position(vertex.m_position),
m_texcoord(vertex.m_texcoord),
m_normal(vertex.m_normal),
m_tangent(vertex.m_tangent),
m_binormal(vertex.m_binormal)

{
}

VertexMesh::~VertexMesh()
{
}
