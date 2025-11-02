#include "Fruit.h"

#include "ToppingResources.h"

void Fruit::Initialize(Point pos, Circle coll)
{
	SetInitialPos(pos);
	SetPos(pos);
	SetColl(coll);
	SetRot(0.0f);
	_texture = ToppingResources::GetRandomTexture();

	_collider.setPos(_position);
	_collider.r = (100 + (10.0f * GetSize())) / 2.0f;


}

void Fruit::Update()
{
	float rot = -GetPizzza()->GetRotSpeed();
	SetRot(GetRot() + (rot));

	Vec2 newPos = Vec2((float)GetInitialPos().x - Scene::CenterF().x, (float)GetInitialPos().y - Scene::CenterF().y);
	newPos.rotate(GetRot());
	newPos += Scene::CenterF();

	SetPos(Point((int)newPos.x, (int)newPos.y));

	_collider.setPos(_position);
	_collider.r = (100 + (10.0f * GetSize())) / 2.0f;

}

void Fruit::Draw()
{
	//_collider.draw();

	_texture.resized(100 + (10.0f * GetSize())).rotated(GetRot()).drawAt(GetPos());
}
