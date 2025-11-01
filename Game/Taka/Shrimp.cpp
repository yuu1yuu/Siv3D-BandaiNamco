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

}

void Shrimp::Draw()
{
	_textrue.resized(100 + (10.0f * GetSize())).rotated(GetRot()).drawAt(GetPos());

}
