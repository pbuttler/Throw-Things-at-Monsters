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

	virtual void VUpdate(float dt) override;
	virtual void VHandleInput(SDLKeyboardState* kb, SDLMouseState* ms, float dt);

	const float GetThrowPower() const;

	static const int MOVE_SPEED = 200;
private:
	Vector2  m_velocity;
	float    m_throwPower;
	Item*    m_item;
};

#endif