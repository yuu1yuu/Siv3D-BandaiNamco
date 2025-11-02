#include "ResultScene.h"

void Game::ResultScene::Initialize()
{
	Print << U"Result Scene Entered";

	_backTex = Texture{ U"../Resources/Textures/Result.jpg" };

}

void Game::ResultScene::Update()
{
	if (KeyEnter.down())
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Title");
	}

	if (m_buttonClicked)
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Title");
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
