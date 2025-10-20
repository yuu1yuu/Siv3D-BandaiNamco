#pragma once

namespace Game
{
	class GameScene : public SceneBase
	{
	public:
		void Initialize() override;


		void Update() override;

		void Draw() const override;
	};
}
