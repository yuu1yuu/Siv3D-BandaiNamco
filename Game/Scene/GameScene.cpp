#include "GameScene.h"

void Game::GameScene::Initialize()
{
	Print << U"Game Scene Entered";
	m_pizzza.Initialize();
	m_camera.setCenter(Scene::CenterF());
	m_camera.setTargetCenter(Scene::CenterF());
}

void Game::GameScene::Update()
{
	if (KeySpace.down())
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Result");
	}

	m_camera.update();
	m_camera.setCenter(Scene::CenterF());


	m_pizzza.Update();

}

void Game::GameScene::Draw() const
{
	{
		auto t = m_camera.createTransformer();
		m_pizzza.Render();
	}
	//m_camera.draw(Palette::Orange);
}
