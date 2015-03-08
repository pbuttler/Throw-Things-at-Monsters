#include "player.h"

Player::Player()
	: GameObject()
{
	m_velocity = Vector2::Zero;
}

void Player::VUpdate(float dt)
{
	
	m_position += m_velocity * Vector2(cos(m_rotation*0.0174532925), sin(m_rotation*0.0174532925)) * dt * MOVE_SPEED;
	m_velocity = Vector2::Zero;
}


void Player::VHandleInput(SDLKeyboardState* kb, SDLMouseState* ms)
{
	
	if(kb->KeyPress(IKEY::W)) {
		m_velocity.x = 1;
		m_velocity.y = 1;
	}
	if(kb->KeyPress(IKEY::S)) {
		m_velocity.x = -1;
		m_velocity.y = -1;
	}

	float dx = ms->X() - m_position.x;
	float dy = ms->Y() - m_position.y;

	m_rotation = atan2(dy,dx) * (180/PI);
}