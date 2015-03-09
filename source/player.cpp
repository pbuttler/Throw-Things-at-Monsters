#include "player.h"

Player::Player()
	: GameObject()
{
	m_velocity = Vector2::Zero;
	m_throwPower = 0.0f;
	m_hp = 3;
	m_prevThrownItem = NULL;
	m_item = NULL;
}

const float Player::GetThrowPower() const
{
	return m_throwPower;
}

Item* Player::GetLastThrownItem() const
{
	return m_prevThrownItem;
}

const int Player::GetHP() const
{
	return m_hp;
}

void Player::PickUpItem(Item* item)
{
	item->SetActive(false);
	item->SetOnGround(false);
	item->SetOwned(true);
	item->SetOwner(this);
	m_item = item;
	m_prevThrownItem = item;
}

void Player::ThrowItem()
{
	m_item->SetActive(true);
	m_item->SetInAir(true);
	m_item->SetDirection(m_rotation);
	m_item->SetOwned(false);
	m_item->SetOwner(NULL);
	m_item->SetSpeed(m_throwPower);
	m_item = NULL;
}

void Player::VUpdate(float dt)
{
	
	m_position += m_velocity * Vector2(cos(m_rotation*0.0174532925), sin(m_rotation*0.0174532925)) * dt * MOVE_SPEED;
	m_velocity = Vector2::Zero;
	if(m_item) {
		m_item->SetPosition(m_position);
	}

	m_bounds.x = m_position.x;
	m_bounds.y = m_position.y;
}

void Player::TakeDamage()
{
	m_hp--;
}


void Player::VHandleInput(SDLKeyboardState* kb, SDLMouseState* ms, float dt)
{
	
	if(kb->KeyPress(IKEY::W)) {
		m_velocity.x = 1;
		m_velocity.y = 1;
	}
	if(kb->KeyPress(IKEY::S)) {
		m_velocity.x = -1;
		m_velocity.y = -1;
	}

	if(ms->ButtonPress(MOUSECS_LEFT)) {
		if(m_item) {
				if(m_throwPower < 1.0f) {
				m_throwPower += dt;
			}
		}
		
	} else if(ms->ButtonRelease(MOUSECS_LEFT)){
		if(m_item) {
			ThrowItem();
			m_throwPower = 0.0f;
		}
		m_throwPower = 0.0f;
	}

	float dx = ms->X() - m_position.x;
	float dy = ms->Y() - m_position.y;

	m_rotation = atan2(dy,dx) * (180/PI);
}