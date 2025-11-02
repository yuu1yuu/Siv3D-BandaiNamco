#include "ResultScene.h"

void Game::ResultScene::Initialize()
{
	Print << U"Result Scene Entered";
}

void Game::ResultScene::Update()
{
	if (KeyEnter.down())
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Title");
	}
}

void Game::ResultScene::Draw() 
{
	FontAsset(U"ResultFont")(U"Result Scene").drawAt(Scene::Center(), Palette::Red);
	FontAsset(U"MenuFont")(U"[Enter] Back to Title").drawAt(Scene::Center().movedBy(0, 60), Palette::Yellow);

	float score;
	score = GameData::GetInstance().Get<float>("Score");
	FontAsset(U"MenuFont")(U"", (int)score).drawAt(Point(100, 100));
}
