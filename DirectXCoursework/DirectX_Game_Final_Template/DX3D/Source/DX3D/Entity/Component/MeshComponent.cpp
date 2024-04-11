#include <DX3D/Entity/Component/MeshComponent.h>

MeshComponent::MeshComponent()
{
}

MeshComponent::~MeshComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void MeshComponent::setMesh(const MeshPtr& mesh)
{
	m_mesh = mesh;
}

const MeshPtr& MeshComponent::getMesh()
{
	return m_mesh;
}

void MeshComponent::addMaterial(const MaterialPtr& material)
{
	m_materials.push_back(material);
}

void MeshComponent::removeMaterial(unsigned int index)
{
	if (index >= m_materials.size()) {

		return;
	}

	m_materials.erase(m_materials.begin() + index);
}

const std::vector<MaterialPtr>& MeshComponent::getMaterials()
{
	return m_materials;
}

void MeshComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}
