#include "Shrimp.h"

Shrimp::Shrimp(Pizzza* pizzza)
	:Fruit(pizzza)
{
}

void Shrimp::Initialize(Point pos, Circle coll)
{
	SetInitialPos(pos);
	SetPos(pos);
	SetColl(coll);
	SetRot(0.0f);
	_textrue = Texture{ U"../Resources/Textures/Kinoko.png" };
}

void Shrimp::Update(float rot)
{
	SetRot(GetRot()+(rot));
}

void Shrimp::Draw(float rot)
{

	Vec2 newPos = Vec2((float)GetInitialPos().x - Scene::CenterF().x, (float)GetInitialPos().y - Scene::CenterF().y);
	newPos.rotate(GetRot());
	newPos += Scene::CenterF();


	_textrue.resized(100 + (10.0f * GetSize())).rotated(GetRot()).drawAt(newPos);

}
