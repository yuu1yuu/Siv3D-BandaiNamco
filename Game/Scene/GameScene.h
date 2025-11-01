#pragma once

#include "../../Game/Taka/Pizzza.h"
#include "../../Game/Taka/FruitManager.h"

namespace Game
{
	class GameScene : public SceneBase
	{
	private:
		Pizzza m_pizzza;

		Camera2D m_camera;

		std::unique_ptr<FruitManager> _fruitManager;

	public:
		void Initialize() override;




		void Update() override;

		void Draw() const override;
	};
}
