#include"../../stdafx.h"
#include "TitleScene.h"

void Game::TitleScene::Initialize()
{
	m_backTexture = Texture{ U"../Resources/Textures/Title.png" };
	m_pizzaTexture = Texture{ U"../Resources/Textures/TitlePizza.png" };
	m_rot = 0.0f;

	AudioManager::Instance().Load(U"TitleBGM", U"../Resources/Sounds/TitleBGM.mp3");
	AudioManager::Instance().Play(U"TitleBGM");

	AudioManager::Instance().Load(U"TitleSE", U"../Resources/Sounds/TitlePushSE.mp3");

	AudioManager::Instance().SetMasterVolume(0.5);
	m_time = 0.0f;
	m_clicked = false;

	m_masterVol = 1.0f;
}

void Game::TitleScene::Update()
{
	if (MouseL.pressed() && !m_clicked)
	{

		AudioManager::Instance().Play(U"TitleSE");
		AudioManager::Instance().FadeOut(U"TitleBGM", 2.0);
		AudioManager::Instance().FadeOut(U"TitleSE", 2.3);
		m_time = Scene::Time();
		m_clicked = true;
	}
	if (Scene::Time() - m_time > 1.3f && m_clicked)
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Game");
	}
	m_rot += 0.01f;

	AudioManager::Instance().SetMasterVolume(m_masterVol);
}

void Game::TitleScene::Draw() const
{
	Rect(Scene::Rect()).draw(ColorF(0.8f,0.5f,0));

	m_backTexture.resized(1000.0f).drawAt(Scene::Center());
	m_pizzaTexture.rotated(m_rot).drawAt(Scene::Center().x + 20.0f, Scene::Center().y-160.0f);

	FontAsset(U"TitleFont")(U"Pizzza Game").drawAt(Scene::Center(), Palette::Black);

	FontAsset(U"MenuFont")(U"[Click] Start Game").drawAt(Scene::Center().movedBy(0, 60), Palette::Black);
	SimpleGUI::Button(U"Click Start", Vec2(600, 600));

}
