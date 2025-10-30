#include "stdafx.h"
#include "Pizzza.h"



void Pizzza::SetPosition(Point pos)
{
	_position = pos;
}

void Pizzza::Initialize()
{
	_textrue = Texture{ U"../Resources/Pizzza.png" };
	_textrue.resized(100);

	_currentMousePoint = Point(0,0);
	_lastMousePoint = Point(0,0);

}

void Pizzza::Update()
{
	bool con = MouseL.pressed();

	//現在のマウスのスクリーン座標を取得
	_currentMousePoint = Cursor::Pos();

	
	Point p = _currentMousePoint - _position - Scene::Center();

	//ピザの中心から現在のマウスの位置に向かってのベクトル
	Vector2D PToC = Vector2D(p.x,p.y);

	p = _lastMousePoint - _position - Scene::Center();

	//ピザの中心からひとつ前のマウスの位置に向かってのベクトル
	Vector2D PToL = Vector2D(p.x, p.y);

	//PToC.normalize();
	//PToL.normalize();



	if (MouseL.pressed())
	{


		if (PToC.cross(PToL) >= 0.5f)
		{
			_speed += (60_deg * Scene::DeltaTime() * 0.01f);
			_rotSpeed = _speed;

		}
		else if (PToC.cross(PToL) <= -0.5f)
		{
			_speed += (60_deg * Scene::DeltaTime() * 0.01f);
			_rotSpeed =-_speed;

		}
	}
	else
	{
		_speed *= 0.9f;
		_rotSpeed *= 0.89f;
	}

	_rot -= _rotSpeed;
	_size += _speed;

	_lastMousePoint = _currentMousePoint;

	

}

void Pizzza::Render() const
{
	//Circle(300, 200, 150).draw();

		// テクスチャを描く | Draw the texture
	_textrue.resized(100 + (10.0f * _size)).rotated(_rot).drawAt(1280 / 2, 720 / 2);

	FontAsset(U"TitleFont")(U"%f",_lastMousePoint.x).drawAt(Point(20,0), Palette::White);
	FontAsset(U"MenuFont")(U"").drawAt(Point(20,80).movedBy(0, 60), Palette::Yellow);

}

void Pizzza::Finalize()
{

}
