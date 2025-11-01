#pragma once

#include "../../Game/Taka/Pizzza.h"

namespace Game
{
	class GameScene : public SceneBase
	{
	private:
		Pizzza m_pizzza;

		Camera2D m_camera;


	public:
		void Initialize() override;


		void Update() override;

		void Draw() const override;
	};
}
