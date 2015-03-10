#ifndef STEER_H
#define STEER_H

#include <vix_vector2.h>
#include "Enemy.h"

class Steer
{
public:
	Steer(void);
	~Steer(void);

	//seek target vector
	static Vector2 Seek(Vector2 target, Enemy& boid);
	//calculate separation force based on nearby boids
	static Vector2 Separate(std::vector<Enemy*>& others, Enemy& boid, float separation);
	//calculate alignment force based on nearby boids
	static Vector2 Align(std::vector<Enemy*>& others, Enemy& boid, float dist);

	//collection of boids (member of Steer for utility and ease of access)
	static std::vector<Enemy*> Boids;
};



#endif