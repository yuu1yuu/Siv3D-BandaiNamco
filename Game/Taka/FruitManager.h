#pragma once
#include "Pizzza.h"
#include "Fruit.h"

class FruitManager
{
private:
	Pizzza* _pizzza;
	std::vector<Fruit*> _fruits;
	

public:
	FruitManager(Pizzza* pizzza)
		:_fruits{}
	{
		_pizzza = pizzza;
	};


	void Update(float zoom);

	void Render();

	void Finalize();

	std::vector<Fruit*> GetFruits()
	{
		return _fruits;
	};



};
