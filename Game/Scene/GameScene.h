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

		std::unique_ptr<FruitManager> _fruitManager;

		float _score;

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
