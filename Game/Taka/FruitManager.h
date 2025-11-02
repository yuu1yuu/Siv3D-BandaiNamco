#pragma once

#include "Pizzza.h"
#include "Fruit.h"

namespace Game
{
	class GameScene;
}
class FruitManager
{
private:
	Pizzza* _pizzza;
	std::vector<Fruit*> _fruits;
	
	float _curSize;

	Game::GameScene* _pScene;

public:
	FruitManager(Game::GameScene* pScene,Pizzza* pizzza)
		:_fruits{}
	{
		_pizzza = pizzza;
		_pScene = pScene;
	};


	void Update(float zoom);

	void Render();

	void Finalize();

	std::vector<Fruit*> GetFruits()
	{
		return _fruits;
	};



};
