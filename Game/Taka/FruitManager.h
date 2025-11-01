#pragma once
#include "Pizzza.h"
#include "Fruit.h"

class FruitManager
{
private:
	Pizzza* _pizzza;
	std::vector<std::unique_ptr<Fruit>> _fruits;
	

public:
	FruitManager(Pizzza* pizzza)
		:_fruits{}
	{
		_pizzza = pizzza;
	};


	void Update(float zoom);

	void Render();

};
