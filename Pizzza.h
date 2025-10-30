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

	Point _position;

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


};

