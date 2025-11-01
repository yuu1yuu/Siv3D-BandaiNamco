
#pragma once

#include "Pizzza.h"

class Fruit
{
private:
	Pizzza* _pOnPizzza;
	Point _position;
	Circle _collider;
	float _size;
public:
	Fruit(Pizzza* pizzza)
	{
		_pOnPizzza = pizzza;
		_position = Point{};
		_collider = Circle();
	};

	//座標のセッターゲッター
	void SetPos(Point pos) { _position = pos; };
	Point GetPos()const { return _position; };

	//コライダーのセッターゲッター
	void SetColl(Circle coll) { _collider = coll; };
	Circle GetColl()const { return _collider; };

	//サイズのセッターゲッター
	void SetSize(float size) { _size = size; };
	float GetSize()const { return _size; };

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Initialize(Point pos, Circle coll) = 0;
	
};

