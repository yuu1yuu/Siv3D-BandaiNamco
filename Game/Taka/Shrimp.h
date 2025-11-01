#pragma once
#include "Fruit.h"
class Shrimp : public Fruit
{
private:
	Texture _texture;


public:
	Shrimp(Pizzza* pizzza);

	void Initialize(Point pos, Circle coll) override;
	void Update()override;
	void Draw()override;

};

