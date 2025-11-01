#include "GameScene.h"

void Game::GameScene::Initialize()
{
	Print << U"Game Scene Entered";
	m_pizzza.Initialize();
	m_camera.setCenter(Scene::CenterF());
	m_camera.setTargetCenter(Scene::CenterF());

	_fruitManager = std::make_unique<FruitManager>(&m_pizzza);

}

void Game::GameScene::Update()
{
	if (KeySpace.down())
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Result");
	}

	m_camera.update();
	m_camera.setCenter(Scene::CenterF());

	_fruitManager->Update(1.0f / m_camera.getScale());

	m_pizzza.Update();

	
}

void Game::GameScene::Draw() 
{
	{
		auto t = m_camera.createTransformer();
		m_pizzza.Render();
		_fruitManager->Render();

	}
}
