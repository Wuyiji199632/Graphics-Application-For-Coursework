#include <DX3D/Entity/Component/CameraComponent.h>
#include <DX3D/Entity/Component/CameraComponent.h>
#include <DX3D/Entity/Component/TransformComponent.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Graphics/GraphicsEngine.h>

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void CameraComponent::getViewMatrix(Matrix4x4& view)
{
	m_entity->getTransform()->getWorldMatrix(view);
	view.inverse();
}

void CameraComponent::getProjectionMatrix(Matrix4x4& proj)
{
	proj = m_projection;
}

void CameraComponent::setFarPlane(float farPlane)
{
	m_farPlane = farPlane;
	computeProjectionMatrix();
}

float CameraComponent::getFarPlane()
{
	return m_farPlane;
}

void CameraComponent::setNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane;
	computeProjectionMatrix();
}

float CameraComponent::getNearPlane()
{
	return m_nearPlane;
}

void CameraComponent::setFieldOfView(float fieldOfView)
{
	m_fieldOfView = fieldOfView;
	computeProjectionMatrix();
}

float CameraComponent::getFieldOfView()
{
	return 0.0f;
}

void CameraComponent::setType(const CameraType& type)
{
	m_type = type;
	computeProjectionMatrix();
}

CameraType CameraComponent::getType()
{
	return m_type;
}

void CameraComponent::setScreenArea(const Rect& area)
{
	m_screenArea = area;
	computeProjectionMatrix();
}

Rect CameraComponent::getScreenArea()
{
	return m_screenArea;;
}

void CameraComponent::computeProjectionMatrix()
{
	if (m_type == CameraType::Perspective)
		m_projection.setPerspectiveFovLH(m_fieldOfView, (float)m_screenArea.width / (float)m_screenArea.height,
			m_nearPlane, m_farPlane);
	else if (m_type == CameraType::Orthogonal)
		m_projection.setOrthoLH((float)m_screenArea.width, (float)m_screenArea.height, m_nearPlane, m_farPlane);
}

void CameraComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
}
