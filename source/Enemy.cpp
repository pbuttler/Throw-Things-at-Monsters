#include "Enemy.h"

Enemy::Enemy() : GameObject()
{
	name = "";
	health = 1;
	alive = true;
	velocity = Vector2::Zero;
}

Enemy::Enemy(string enemyName, int enemyHealth, Player target, Texture* deadTex) : GameObject()
{
	name = enemyName;
	health = enemyHealth;
	deadTexture = deadTex;
	alive = true;
	velocity = Vector2::Zero;
	seekPlayer(target);
}

Enemy::~Enemy(void)
{
}

void Enemy::explode()
{
	alive = false;
}

const bool Enemy::IsAlive() const
{
	return alive;
}

void Enemy::VUpdate(float dt)
{
	m_position += velocity * Vector2(cos(m_rotation*0.0174532925f), sin(m_rotation*0.0174532925f)) * dt * MOVE_SPEED;

	m_bounds.x = m_position.x;
	m_bounds.y = m_position.y;
}

void Enemy::VRender(GLRenderer* renderer, float dt)
{
	if(alive) {
		GameObject::VRender(renderer, dt);
	}
	else {
		renderer->Render2DTexture((GLTexture*)deadTexture, m_position, Rect::EMPTY, m_origin, Vector2::Unit, m_rotation, Colors::White, 0.0f);
	}
}

void Enemy::seekPlayer(Player target)
{
	velocity.x = 1.0;
	velocity.y = 1.0;
	
	float dx = target.GetPosition().x - m_position.x;
	float dy = target.GetPosition().y - m_position.y;

	m_rotation = atan2(dy, dx) * (180 / PI);
}