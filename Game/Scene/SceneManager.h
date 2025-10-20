#pragma once
#include "SceneBase.h"

namespace Game
{
	class SceneManager final
	{
	private:
		SceneManager(float fadeDuration = 1.0f)
			: m_fadeDuration(fadeDuration)
			, m_fadeTimer(0.0f)
			, m_isFadingOut(false)
			, m_isTransitioning(false)
			,m_nextSceneName(U"")
		{
		}

	public:

		// シングルトン取得
		static SceneManager& GetInstance()
		{
			static SceneManager instance;
			return instance;
		}

		// コピー禁止
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

	public:
		// シーンを登録
		template<class T>
		void Register(const String& name)
		{
			m_sceneFactories[name] = []() {
				return std::make_unique<T>();
				};
		}

		// シーンを登録
		template<class T>
		void Register(const std::string& name)
		{
			Register<T>(Unicode::Widen(name));
		}

		// フェード付きでシーン切り替えを開始
		void ChangeScene(const String& name)
		{
			if (m_isTransitioning) return; // 遷移中は無視

			if (m_currentScene)
			{
				m_currentScene->Finalize();
			}

			m_nextSceneName = name;
			m_isTransitioning = true;
			m_fadeTimer = 0.0f;
			m_isFadingOut = true;
		}
		void ChangeScene(const std::string& name)
		{
			ChangeScene(Unicode::Widen(name));
		}
		void Update()
		{
			if (m_isTransitioning)
			{
				m_fadeTimer += float(Scene::DeltaTime());

				if (m_isFadingOut && m_fadeTimer >= m_fadeDuration)
				{
					// フェードアウト完了 → 新シーンに切り替え
					auto it = m_sceneFactories.find(m_nextSceneName);
					if (it != m_sceneFactories.end())
					{
						m_currentScene = it->second();
						m_currentSceneName = m_nextSceneName;
						m_currentScene->Initialize();
					}

					m_fadeTimer = 0.0f;
					m_isFadingOut = false;
				}
				else if (!m_isFadingOut && m_fadeTimer >= m_fadeDuration)
				{
					// フェードイン完了
					m_isTransitioning = false;
				}
			}
			else
			{
				if (m_currentScene)
				{
					m_currentScene->Update();
				}
			}
		}

		void Draw() const
		{
			if (m_currentScene)
			{
				m_currentScene->Draw();
			}

			if (m_isTransitioning)
			{
				float t = m_fadeTimer / m_fadeDuration;
				float alpha = m_isFadingOut ? t : (1.0f - t);

				Rect(Scene::Rect()).draw(ColorF(0, alpha));
			}
		}
		void SetFadeDuration(float duration)
		{
			m_fadeDuration = duration;
		}
		const String& GetCurrentSceneName() const { return m_currentSceneName; }

	private:
		String m_currentSceneName;
		std::unique_ptr<SceneBase> m_currentScene;
		std::unordered_map<String, std::function<std::unique_ptr<SceneBase>()>> m_sceneFactories;

		// 遷移管理
		bool m_isTransitioning;
		bool m_isFadingOut;
		float m_fadeDuration;
		float m_fadeTimer;
		String m_nextSceneName;
	};
}
