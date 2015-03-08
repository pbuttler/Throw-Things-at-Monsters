#include "Item.h"


Item::Item(void)
{
}
Item::Item(char* n, float w, float s, float d)
{
	name = n;
	weight = w;
	speed = s;
	damage = d;
	active = false;
}

Item::~Item(void)
{
}
//Setters
void Item::SetName(char* n){
	name = n;
}
void Item::SetWeight(float w){
	weight = w;
}
void Item::SetSpeed(float s){
	speed = s;
}
void Item::SetDamage(float d){
	damage = d;
}
void Item::SetOwner(GameObject* g){
	owner = g;
}
void Item::SetActive(bool a){
	active = a;
}
//Getters
const char* Item::GetName() const{
	return name;
}
const float Item::GetWeight() const{
	return weight;
}
const float Item::GetSpeed() const{
	return speed;
}
const float Item::GetDamage() const{
	return damage;
}
const GameObject* Item::GetOwner() const{
	return owner;
}
const bool Item::GetActive() const{
	return active;
}
//Special functions
void Item::PickUp(GameObject* o){
	//method called when the player steps on an item that is just sitting in the world
	//set owner to have this item
	//set this item to have this owner
	//set active to false(so we don't draw it while the player holds it)
}
void Item::ThrowItem(){
	//function called whenever the owning player throws it
}
void Item::DestroyItem(){
	//function called when the item needs to be destructed
}