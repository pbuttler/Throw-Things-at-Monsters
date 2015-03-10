#include "Steer.h"

Steer::Steer(void)
{
}


Steer::~Steer(void)
{
}

Vector2 Steer::Seek( Vector2 target, Enemy& e )
{
	Vector2 dv = target - e.GetPosition();
	Vector2 dvNorma = dv.Normalize();
	dvNorma *= e.GetMaxForce();
	Vector2 steerForce = dvNorma - e.GetVelocity();
	return steerForce;
}

Vector2 Steer::Separate( std::vector<Enemy*>& others, Enemy& e, float separation )
{
	//Steer force
	Vector2 steerForce = Vector2::Zero;

	for(Enemy* &b : others)
	{
		float distance = e.GetPosition().Distance(b->GetPosition());

		if ((distance > 0) && (distance < separation))
		{
			//Calculate vector pointing away
			Vector2 diff = b->GetPosition() - e.GetPosition();
			diff.Normalize();
			diff *= -1;
			steerForce += diff * 1.0f / distance;
		}
	}

	//normalize and limit force by max force
	if (steerForce.Length() > 0)
	{
		steerForce.Normalize();
		steerForce *= e.GetMaxForce();
		steerForce -= e.GetVelocity();
	}

	return steerForce;
}

Vector2 Steer::Align( std::vector<Enemy*>& others, Enemy& e, float dist )
{
	Vector2 steerForce = Vector2::Zero;

	Vector2 sumVel = Vector2::Zero;
	int count = 0;

	for(Enemy* &b : others)
	{
		float d = b->GetPosition().Distance(e.GetPosition());
		if ((d > 0) && (d < dist))
		{
			sumVel += b->GetVelocity();
			count++;
		}
	}

	if (count > 0)
	{
		sumVel /= (float)count;
		sumVel.Normalize();
		sumVel *= e.GetMaxForce();

		steerForce = sumVel - e.GetVelocity();
		return steerForce;
	}

	return steerForce;
}