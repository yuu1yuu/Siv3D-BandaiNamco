#include "FruitManager.h"

void FruitManager::Update(float zoom)
{
	if (MouseR.down())
	{
		Vec2 pos = Cursor::PosF() - Scene::CenterF();
		pos *= zoom;

		pos = Scene::CenterF() + pos;

		_fruits.emplace_back(new Fruit (_pizzza));
		//-------------------------------------------------------ここのCircleの右側で当たり判定の半径きめる
		_fruits.back()->Initialize(Point((int)pos.x,(int)pos.y), Circle(pos,zoom * 3.0f));
		_fruits.back()->SetSize(zoom * 3.0f);
	}
	for (int i = 0; i < _fruits.size(); i++)
	{
		_fruits[i]->Update();
	}
}


void FruitManager::Render()
{
	for (int i = 0; i < _fruits.size(); i++)
	{
		_fruits[i]->Draw();
	}
}

void FruitManager::Finalize()
{
	for (int i = 0; i < _fruits.size(); i++)
	{
		delete _fruits[i];
		_fruits[i] = nullptr;
	}

	_fruits.clear();
}

