#pragma once
class Pizzza
{
private:

	Texture _textrue;

	float _rot;
	float _size;
	float _speed;

	float _rotSpeed;

	Point _lastMousePoint;

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

	float GetSize() const
	{
		return _size;
	};

	float GetRot() const
	{
		return _rot;
	};

	float GetRotSpeed() const
	{
		return _rotSpeed;
	}


};

