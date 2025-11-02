#pragma once

namespace Game
{
	class ResultScene : public SceneBase
	{
	private :
		Texture _backTex;


		bool m_buttonClicked;

	public:
		void Initialize() override;

		void Update() override;

		void Draw()  override;
	};
}
