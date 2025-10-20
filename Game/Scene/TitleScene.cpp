#include "TitleScene.h"

void Game::TitleScene::Initialize()
{
	Print << U"Title Scene Entered";
}

void Game::TitleScene::Update()
{
	if (KeyEnter.down())
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Game");
	}
	
}

void Game::TitleScene::Draw() const
{
	FontAsset(U"TitleFont")(U"Title Scene").drawAt(Scene::Center(), Palette::White);
	FontAsset(U"MenuFont")(U"[Enter] Start Game").drawAt(Scene::Center().movedBy(0, 60), Palette::Yellow);
}
