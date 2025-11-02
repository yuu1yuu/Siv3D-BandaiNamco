#include "FruitManager.h"
#include "../../Game/Scene/GameScene.h"



void FruitManager::Update(float zoom)
{
	if (MouseR.down() && abs(_pizzza->GetRotSpeed()) >= 0.00001f)
	{
		Vec2 pos = Cursor::PosF() - Scene::CenterF();
		pos *= zoom;

		pos = Scene::CenterF() + pos;

		_fruits.emplace_back(new Fruit (_pizzza));
		//-------------------------------------------------------
		_fruits.back()->Initialize(Point((int)pos.x,(int)pos.y), Circle());
		_fruits.back()->SetSize(zoom * 3.0f);

		Circle pColl = _pizzza->GetCollider();
		Circle fColl = _fruits.back()->GetColl();

		if (!pColl.contains(fColl))
		{
			delete _fruits.back();
			_fruits.pop_back();
		}
		else
		{
			_pScene->AddScore(5.0f);
		}

		if(_fruits.size() >= 2)
		for (int i = 0; i < _fruits.size() - 1; i++)
		{
			Circle fColl2 = _fruits[i]->GetColl();
			if (fColl.intersects(fColl2))
			{
				_pScene->SetScore(_pScene->GetScore() / 2.0f);
			}

		}

	}
	for (int i = 0; i < _fruits.size(); i++)
	{
		_fruits[i]->Update();
		
	}

	_curSize = (100 + (10.0f * 3.0f * zoom)) / 2.0f;

}


void FruitManager::Render()
{
	for (int i = 0; i < _fruits.size(); i++)
	{
		_fruits[i]->Draw();
	}

	Circle circle(Cursor::Pos(),_curSize);
	circle.draw(ColorF(0,0,0,0.3f));

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

