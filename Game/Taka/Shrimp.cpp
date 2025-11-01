#include "Shrimp.h"

Shrimp::Shrimp(Pizzza* pizzza)
	:Fruit(pizzza)
{
}

void Shrimp::Initialize(Point pos, Circle coll)
{
	SetPos(pos);
	SetColl(coll);
}

void Shrimp::Update()
{
	_textrue.resized(100 + (10.0f * _size)).rotated(_rot).drawAt(Scene::CenterF());

}

void Shrimp::Draw()
{
}
