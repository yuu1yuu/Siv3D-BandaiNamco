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
	m_buttonClicked = false;
	m_masterVol = 0.5f;
}

void Game::TitleScene::Update()
{
	if (m_buttonClicked && !m_clicked)
	{

		AudioManager::Instance().Play(U"TitleSE",2.35);
		AudioManager::Instance().FadeOut(U"TitleBGM", 2.0);
	;
		m_time = Scene::Time();
		m_clicked = true;
	}
	if (Scene::Time() - m_time > 1.3f && m_clicked)
	{
		Game::SceneManager::GetInstance().ChangeScene(U"Game");
	}
	m_rot += 0.02f;

	AudioManager::Instance().SetMasterVolume(m_masterVol);
}

void Game::TitleScene::Draw() 
{
	Rect(Scene::Rect()).draw(ColorF(0.8f,0.5f,0));

	m_backTexture.resized(1000.0f).drawAt(Scene::Center());
	m_pizzaTexture.rotated(m_rot).drawAt(Scene::Center().x + 20.0f, Scene::Center().y-160.0f);

	FontAsset(U"TitleFont")(U"Pizzza Game").drawAt(Scene::Center(), Palette::Black);


	if (SimpleGUI::Button(U"Click Start", Vec2(580,450)))
	{
		m_buttonClicked = true;
	}
	SimpleGUI::Slider(U"masterVolume",m_masterVol,0.0,1.0,Vec2(10,680),150);

}
