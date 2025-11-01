#pragma once
#include "Fruit.h"
class Shrimp : public Fruit
{
private:
	Texture _textrue;


public:
	Shrimp(Pizzza* pizzza);

	void Initialize(Point pos, Circle coll) override;
	void Update(float rot)override;
	void Draw(float rot)override;

};

