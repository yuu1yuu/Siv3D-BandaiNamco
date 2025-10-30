# include "stdafx.h"
#include "Game/Scene/TitleScene.h"
#include "Game/Scene/GameScene.h"
#include "Game/Scene/ResultScene.h"

void Main()
{
	Window::Resize(1280, 720);
	// フォント登録
	FontAsset::Register(U"TitleFont", 60, Typeface::Bold);
	FontAsset::Register(U"GameFont", 50, Typeface::Bold);
	FontAsset::Register(U"ResultFont", 50, Typeface::Bold);
	FontAsset::Register(U"MenuFont", 30);

	Game::SceneManager& sceneManager = Game::SceneManager::GetInstance();

	Game::GameData& data = Game::GameData::GetInstance();

	Game::InputManager& inputManager = Game::InputManager::GetInstance();


	inputManager.BindKey("JUMP", 'w');
	inputManager.BindAction("JUMP", Game::InputEventType::Down, [] { Print << U"JUMP!"; });

	inputManager.BindKey("Save", 's');
	inputManager.BindAction("Save", Game::InputEventType::Down, [&] { Print << U"save"; data.Save(U"save.json"); });



	// シーン登録
	sceneManager.Register<Game::TitleScene>("Title");
	sceneManager.Register<Game::GameScene>("Game");
	sceneManager.Register<Game::ResultScene>("Result");
	
	// 最初のシーン
	sceneManager.ChangeScene("Title");

	while (System::Update())
	{
		Game::InputManager::GetInstance().Update();
		sceneManager.Update();
		sceneManager.Draw();
	}
}
