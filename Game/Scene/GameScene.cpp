#include "GameScene.h"




void Game::GameScene::Initialize()
{
	Print << U"Game Scene Entered";
	m_pizzza.Initialize();
	m_camera.setCenter(Scene::CenterF());
	m_camera.setTargetCenter(Scene::CenterF());

	_score = 0.0f;

	_fruitManager = std::make_unique<FruitManager>(this,&m_pizzza);
	Cursor::RequestStyle(CursorStyle::Hidden);
	_backTex = Texture{ U"../Resources/Textures/background.png" };

}

void Game::GameScene::Update()
{
	Cursor::RequestStyle(CursorStyle::Hidden);

	if (KeySpace.down())
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Result");
	}

	// 経過時間をもとにズーム値を減らす
	zoom -= zoomOutSpeed * Scene::DeltaTime();

	// 下限に制限
	zoom = Max(zoom, minZoom);

	m_camera.setScale(zoom);
	m_camera.setCenter(Scene::CenterF());

	_fruitManager->Update(1.0f / m_camera.getScale());

	m_pizzza.Update();
}

void Game::GameScene::Draw() 
{
	{
		_backTex.resized(10000).drawAt(Scene::Center());
		auto t = m_camera.createTransformer();
		m_pizzza.Render();
		_fruitManager->Render();

	}

	FontAsset(U"MenuFont")(U"",(int)_score).drawAt(Point(100,100));
}
