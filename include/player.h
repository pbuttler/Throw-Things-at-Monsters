#ifndef PLAYER_H
#define PLAYER_H

#include <vix_sdlinput.h>
#include "gameobject.h"
#include "Item.h"


class Player : public GameObject
{
public:
	Player();

	void PickUpItem(Item* item);
	void ThrowItem();
	void TakeDamage();
	void SetHP(int hp);
	void Revive();
	void Die();

	virtual void VUpdate(float dt) override;
	virtual void VHandleInput(SDLKeyboardState* kb, SDLMouseState* ms, float dt);
	virtual void VRender(GLRenderer* renderer, float dt);

	const float GetThrowPower() const;
	const int   GetHP() const;
	Item* GetLastThrownItem() const;

	static const int MOVE_SPEED = 200;
private:
	Vector2  m_velocity;
	float    m_throwPower;
	Item*    m_item;
	Item*    m_prevThrownItem;
	int      m_hp;
	bool     m_alive;
};

#endif