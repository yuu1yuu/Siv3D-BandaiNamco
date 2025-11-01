
#pragma once

#include "Pizzza.h"

class Fruit
{
private:
	Pizzza* _pOnPizzza;
	Point _position;
	Point _initialPos;
	Circle _collider;
	float _size;
	float _rot;
	Texture _texture;
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

	//サイズのセッターゲッター
	void SetRot(float rot) { _rot = rot; };
	float GetRot()const { return _rot; };

	void SetInitialPos(Point pos) { _initialPos = pos; };
	Point GetInitialPos()const { return _initialPos; };

	Pizzza* GetPizzza()const { return _pOnPizzza; };


	virtual void Update() ;
	virtual void Draw() ;
	virtual void Initialize(Point pos, Circle coll);
	
};

