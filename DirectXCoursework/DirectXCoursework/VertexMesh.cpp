#include "VertexMesh.h"

VertexMesh::VertexMesh() :m_position(), m_texcoord(),m_normal()
{
}

VertexMesh::VertexMesh(Vector3D position, Vector2D texcoord,Vector3D normal) :m_position(position), m_texcoord(texcoord),m_normal(normal)
{
}

VertexMesh::VertexMesh(const VertexMesh& vertex) :m_position(vertex.m_position), m_texcoord(vertex.m_texcoord), m_normal(vertex.m_normal)
{
}

VertexMesh::~VertexMesh()
{
}
