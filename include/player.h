#ifndef PLAYER_H
#define PLAYER_H

#include <vix_sdlinput.h>
#include "gameobject.h"

class Player : public GameObject
{
public:
	Player();

	virtual void VUpdate(float dt) override;
	virtual void VHandleInput(SDLKeyboardState* kb, SDLMouseState* ms);


	static const int MOVE_SPEED = 200;
private:
	Vector2  m_velocity;
};

#endif