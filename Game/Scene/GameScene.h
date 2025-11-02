#pragma once

#include "../../Game/Taka/Pizzza.h"

#include "../../Game/Taka/FruitManager.h"

class FruitManager;

namespace Game
{
	class GameScene : public SceneBase
	{
	private:
		Pizzza m_pizzza;

		Camera2D m_camera;
		double zoom = 1.0;                   // 現在のズーム値
		const double zoomOutSpeed = 0.035;     // ズームアウト速度（1秒あたりどれくらい引くか）
		const double minZoom = 0.01;          // ズームアウトの下限
		std::unique_ptr<FruitManager> _fruitManager;

		float _score;

		Texture _backTex;

		double _startTime;
	public:
		void Initialize() override;

		void Update() override;

		void Draw()  override;

		void AddScore(float as)
		{
			_score += as;
		};
		void SetScore(float score)
		{
			_score = score;
		};
		float GetScore()const
		{
			return _score;
		};

	};
}
