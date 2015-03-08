#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//VIXEN INCLUDES
#include <vix_glrenderer.h>
#include <vix_rectangle.h>
#include <vix_vector2.h>

using namespace Vixen;

class GameObject
{
public:
	GameObject(void);

	~GameObject(void);

	/*SETTERS*/
	void SetTexture(Texture* texture);
	void SetPosition(Vector2 position);
	void SetOrigin(Vector2 origin);
	void SetRotation(float rotation);

	/*GETTERS*/
	const Texture* GetTexture()		const;
	const Vector2& GetPosition()	const;
	const Vector2& GetOrigin()		const;
	const float    GetRotation()	const;
	Rect&    GetBounds();

	/*Updated GameObject (AI, etc.)*/
	virtual void VUpdate(float dt);

	/*Render GameObject*/
	virtual void VRender(GLRenderer* renderer, float dt);

protected:
	Texture* m_texture;  //GameObject sprite image
	Vector2  m_position; //GameObject 2D screen position (in PIXELS)
	Vector2  m_origin;   //GameObject origin (used for rotation)
	float    m_rotation; //GameObject rotation
	Rect     m_bounds;
};

#endif