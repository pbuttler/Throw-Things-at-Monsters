#pragma once
#include "gameobject.h"

class Item: public GameObject
{
public:
	Item(void);
	Item(char* n, float w, float s, float d);
	~Item(void);

	//setters
	void SetName(char* n);
	void SetWeight(float w);
	void SetSpeed(float s);
	void SetDamage(float d);
	void SetOwner(GameObject* o);
	void SetActive(bool a);
	void SetOwned(bool o);
	void SetInAir(bool a);
	void SetOnGround(bool g);
	void SetDirection(float dir);
	//getters
	const char* GetName() const;
	const float GetWeight() const;
	const float GetSpeed() const;
	const float GetDamage() const;
	const GameObject* GetOwner() const;
	const bool GetActive() const;
	const bool GetOwned() const;
	const bool GetInAir() const;
	const bool GetOnGround() const;
	const float GetDirection() const;
	//specific functions
	void PickUp(GameObject* player);
	void ThrowItem();
	void DestroyItem();

	virtual void VUpdate(float dt) override;
	virtual void VRender(GLRenderer* renderer, float dt) override;
protected:
	char* name;
	float weight;
	float speed;
	float damage;
	float direction;
	GameObject* owner;
	bool active;
	bool owned;
	bool inAir;
	bool onGround;
	Vector2 velocity;
	Vector2 acceleration;
};

