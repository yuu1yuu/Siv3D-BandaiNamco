#pragma once
#include "SceneBase.h"
#include"SceneManager.h"
namespace Game
{
	class TitleScene : public SceneBase
	{
	public:
		void Initialize() override;

		void Update() override;

		void Draw() const override;
	private:

		Texture m_backTexture;
		Texture m_pizzaTexture;
		float m_rot;
	};

}
