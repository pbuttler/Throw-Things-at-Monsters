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

	virtual void VUpdate(float dt) override;
	virtual void VHandleInput(SDLKeyboardState* kb, SDLMouseState* ms, float dt);

	const float GetThrowPower() const;
	const int   GetHP() const;

	static const int MOVE_SPEED = 200;
private:
	Vector2  m_velocity;
	float    m_throwPower;
	Item*    m_item;
	int      m_hp;
};

#endif