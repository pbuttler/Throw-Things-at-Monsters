#pragma once

#include <string>
#include "gameobject.h"
#include "player.h"

using namespace std;

class Enemy : public GameObject
{
public:
	Enemy(void);
	Enemy(string enemyName, int enemyHealth, Player target);
	~Enemy(void);
	
	virtual void VUpdate(float dt) override;
	//void observe();
	//void determineAction();
	//void move();
	//void destroy();
	void seekPlayer(Player target);
	
private:
	string name;
	int health;
	bool alive;
	static const int MOVE_SPEED = 75;
	Vector2 velocity;
};