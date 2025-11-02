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
	_backTex2 = Texture{ U"../Resources/Textures/utyu.png" };

	_startTime = Scene::Time();
}

void Game::GameScene::Update()
{
	Cursor::RequestStyle(CursorStyle::Hidden);


	// 経過時間をもとにズーム値を減らす
	zoom *= 0.999;// zoomOutSpeed * Scene::DeltaTime();

	// 下限に制限
	zoom = Max(zoom, minZoom);

	m_camera.setScale(zoom);
	m_camera.setCenter(Scene::CenterF());

	_fruitManager->Update(1.0f / m_camera.getScale());

	m_pizzza.Update();




	// 30秒経過したら処理
	if (30 - ((int)Scene::Time() - (int)_startTime) <= 0)
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Result");

	}
}

void Game::GameScene::Draw() 
{
	{

		auto t = m_camera.createTransformer();
		_backTex2.resized(200000).drawAt(Scene::Center());
		_backTex.resized(1500).rounded(50.0f).drawAt(Scene::Center());

		m_pizzza.Render();
		_fruitManager->Render();

	}

	FontAsset(U"MenuFont")(U"",(int)_score).drawAt(Point(100,100));

	FontAsset(U"MenuFont")(U"",30-((int)Scene::Time() - (int)_startTime)).drawAt(Point(600,100));
}
