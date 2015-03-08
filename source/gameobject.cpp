#include "gameobject.h"

GameObject::GameObject(void)
{
	m_texture = nullptr;
	m_position = Vector2::Zero;
	m_origin = Vector2::Zero;
	m_rotation = 0.0f;
}

GameObject::~GameObject(void)
{

}

void GameObject::VUpdate(float dt)
{
	m_position.x += dt * 25.0f;
}

void GameObject::VRender(GLRenderer* renderer, float dt)
{
	if(m_texture)
		renderer->Render2DTexture((GLTexture*)m_texture, m_position, Rect::EMPTY, m_origin, Vector2::Unit,
			m_rotation, Colors::White, 0.0f);
}

/*SETTERS*/

void GameObject::SetTexture(Texture* texture)
{
	m_texture = texture;
}

void GameObject::SetPosition(Vector2 position)
{
	m_position = position;
}

void GameObject::SetOrigin(Vector2 origin)
{
	m_origin = origin;
}

void GameObject::SetRotation(float rotation)
{
	m_rotation = rotation;
}

/*GETTERS*/

const Texture* GameObject::GetTexture() const
{
	return m_texture;
}

const Vector2& GameObject::GetPosition() const
{
	return m_position;
}

const Vector2& GameObject::GetOrigin() const
{
	return m_origin;
}

const float GameObject::GetRotation() const
{
	return m_rotation;
}




