#pragma once
class Pizzza
{
private:

	//テクスチャ
	Texture _textrue;

	//現在の回転
	float _rot;
	//大きさ
	float _size;

	//現在の回転量
	float _speed;
	float _rotSpeed;

	//前のフレームでのマウスの座標
	Point _lastMousePoint;

	//今のフレームのマウスの座標
	Point _currentMousePoint;


	Vector2D<double> _lastPadStickVec;
	Vector2D<double> _currentPadStickVec;

	Point _position;

	Circle _collider;

public:

	Pizzza()
	{
		_rot = 0.0f;
		_size = 0.0f;
		_speed = 0.0f;
		_rotSpeed = 0.0f;
	};

	void SetPosition(Point pos);

	void Initialize();

	void Update();

	void Render() const;

	void Finalize();

	//サイズの取得
	float GetSize() const
	{
		return _size;
	};

	//現在の回転を取得
	float GetRot() const
	{
		return _rot;
	};

	//現在の回転量を取得
	float GetRotSpeed() const
	{
		return _rotSpeed;
	}

	//当たり判定の円を取得
	Circle GetCollider() const
	{
		return _collider;
	}
};

