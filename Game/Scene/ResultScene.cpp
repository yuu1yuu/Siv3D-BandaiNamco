#include "ResultScene.h"

void Game::ResultScene::Initialize()
{

	_backTex = Texture{ U"../Resources/Textures/Result.jpg" };


	//Audio
	AudioManager::Instance().Load(U"ResultBGM", U"../Resources/Sounds/ResultBGM.mp3");
	AudioManager::Instance().Play(U"ResultBGM");
	AudioManager::Instance().Load(U"ResultSE", U"../Resources/Sounds/wow-pizza-arrived-170930.mp3");
	AudioManager::Instance().Play(U"ResultSE", 2.35);

}

void Game::ResultScene::Update()
{


	if (m_buttonClicked)
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Title");
		AudioManager::Instance().FadeOut(U"ResultBGM", 2.0);
	}
}

void Game::ResultScene::Draw() 
{

	_backTex.resized(1300).drawAt(Scene::Center());

	if (SimpleGUI::Button(U"Return Title", Vec2(120, 500),120))
	{
		m_buttonClicked = true;
	}


	float score;
	score = GameData::GetInstance().Get<float>("Score");
	
	FontAsset(U"ResultFont")(U"SCORE:", (int)score).drawAt(150, 450 + sinf(Scene::Time() * 3) * 10);
}
