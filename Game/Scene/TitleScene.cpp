#include "TitleScene.h"

void Game::TitleScene::Initialize()
{
	m_backTexture = Texture{ U"../Resources/Textures/Title.png" };
	m_pizzaTexture = Texture{ U"../Resources/Textures/TitlePizza.png" };
	m_rot = 0.0f;
	m_audio = Audio{ Audio::Stream,U"../Resources/Sounds/TitleBGM.mp3" };
	m_audio.play();
}

void Game::TitleScene::Update()
{
	if (MouseL.pressed())
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Game");
	}
	m_rot += 0.01f;
}

void Game::TitleScene::Draw() const
{
	Rect(Scene::Rect()).draw(ColorF(0.8f,0.5f,0));

	m_backTexture.resized(1000.0f).drawAt(Scene::Center());
	m_pizzaTexture.rotated(m_rot).drawAt(Scene::Center().x + 20.0f, Scene::Center().y-160.0f);

	FontAsset(U"TitleFont")(U"Pizzza Game").drawAt(Scene::Center(), Palette::Black);

	FontAsset(U"MenuFont")(U"[Click] Start Game").drawAt(Scene::Center().movedBy(0, 60), Palette::Black);

}
