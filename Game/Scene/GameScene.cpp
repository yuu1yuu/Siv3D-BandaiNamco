#include "GameScene.h"

void Game::GameScene::Initialize()
{
	Print << U"Game Scene Entered";
}

void Game::GameScene::Update()
{
	if (KeySpace.down())
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Result");
	}
}

void Game::GameScene::Draw() const
{
	FontAsset(U"GameFont")(U"Game Scene").drawAt(Scene::Center(), Palette::Green);
	FontAsset(U"MenuFont")(U"[Space] Go to Result").drawAt(Scene::Center().movedBy(0, 60), Palette::Yellow);
	FontAsset(U"MenuFont")(U"たかちゃ").drawAt(Scene::Center().movedBy(0, 90), Palette::Yellow);

}
