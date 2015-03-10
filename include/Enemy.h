#pragma once

#include <string>
#include "gameobject.h"
#include "player.h"

using namespace std;

class Enemy : public GameObject
{
public:
	Enemy(void);
	Enemy(string enemyName, int enemyHealth, Player target, Texture* deadTex);
	~Enemy(void);
	
	virtual void VUpdate(float dt) override;
	virtual void VRender(GLRenderer* renderer, float dt) override;
	const bool         IsAlive() const;
	//void observe();
	//void determineAction();
	//void move();
	//void destroy();
	void explode();
	void revive();
	void seekPlayer(Player target);

	Vector2 GetVelocity();
	float   GetMaxForce();

	static const int MOVE_SPEED = 75;
	
private:
	Texture*   deadTexture;
	string	   name;
	int		   health;
	bool	   alive;
	Vector2    velocity;
	Vector2    acceleration;
	float      maxForce;
	float      maxSpeed;
};