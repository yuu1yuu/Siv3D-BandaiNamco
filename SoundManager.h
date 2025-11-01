#pragma once
#include <Siv3D.hpp>

class AudioManager
{
private:
	struct AudioData
	{
		Audio audio;
		double volume = 1.0;
		Optional<double> duration; // 再生時間（秒）
		Optional<double> startTime; // 再生開始時刻（秒）
	};

	struct FadeData
	{
		double startVolume;      // 開始時の音量
		double targetVolume;     // 目標音量（通常は 0.0）
		double duration;         // フェード時間（秒）
		double elapsed = 0.0;    // 経過時間
		String key;              // 対象 Audio のキー
	};

	HashTable<String, AudioData> m_audios;  // 音データを名前で管理
	Array<FadeData> m_fades;
	float m_mastervol  =1.0f;
	AudioManager() = default;
	~AudioManager() = default;

public:
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	static AudioManager& Instance()
	{
		// E200（初期化順序エラー）回避
		static AudioManager instance;
		return instance;
	}

	// 音の読み込み
	void Load(const String& name, const FilePath& path)
	{
		if (m_audios.contains(name))
		{
			return;
		}

		Audio audio{ path };
		if (audio)
		{
			AudioData data;
			data.audio = std::move(audio);
			data.volume = 1.0;
			m_audios[name] = std::move(data);
		}
		else
		{
			throw Error{ U"Failed to load audio: {}"_fmt(path) };
		}
	}


	// 第3引数に durationSec（再生時間）を追加
	void Play(const String& name, Optional<double> durationSec = none)
	{
		if (auto it = m_audios.find(name); it != m_audios.end())
		{

				it->second.audio.play();
			it->second.startTime = Scene::Time();   // 再生開始時刻を記録
			it->second.duration = durationSec;      // 再生時間（秒）を記録
		}
	}

	// 停止
// 再生時間情報をリセットする処理を追加
	void Stop(const String& name)
	{
		if (auto it = m_audios.find(name); it != m_audios.end())
		{
			// 再生中であっても即停止
			if (it->second.audio.isPlaying())
			{
				it->second.audio.stop();
			}

			// 自動停止スケジュールを完全リセット
			it->second.startTime = none;
			it->second.duration = none;
		}
	}
	// 線形補間
	inline double Lerp(double a, double b, double t)
	{
		return a + (b - a) * t;
	}

	// 時間経過を監視して、指定秒経過した音を自動停止
	void Update()
	{
		const double now = Scene::Time();
		for (auto& [name, data] : m_audios)
		{
			if (data.duration && data.startTime)
			{
				if (now - *data.startTime >= *data.duration)
				{
					if (data.audio.isPlaying())
					{
						data.audio.stop();
					}
					data.startTime = none;
					data.duration = none;
				}
			}
		}
		const double dt = Scene::DeltaTime(); // 前フレームからの経過秒

		for (size_t i = 0; i < m_fades.size(); )
		{
			auto& fade = m_fades[i];
			fade.elapsed += dt;
			double t = Clamp(fade.elapsed / fade.duration, 0.0, 1.0);
			double newVolume = Lerp(fade.startVolume, fade.targetVolume, t);

			if (auto it = m_audios.find(fade.key); it != m_audios.end())
			{
				it->second.audio.setVolume(newVolume);
			}

			if (t >= 1.0)
			{
				// フェード完了 → 音を止める
				Stop(fade.key);
				m_fades.remove_at(i);
			}
			else
			{
				++i;
			}
		}
	}

	// 全停止
	void StopAll()
	{
		for (auto& [key, data] : m_audios)
		{
			data.audio.stop();
		}
	}

	// 再生中か確認
	bool IsPlaying(const String& name) const
	{
		if (auto it = m_audios.find(name); it != m_audios.end())
		{
			return it->second.audio.isPlaying();
		}
		return false;
	}

	//  音量設定（0.0～1.0）
	void SetVolume(const String& name, double volume)
	{
		if (auto it = m_audios.find(name); it != m_audios.end())
		{
			volume = Clamp(volume * m_mastervol, 0.0, 1.0);
			it->second.volume = volume * m_mastervol;
			it->second.audio.setVolume(volume * m_mastervol);
		}
	}

	//  音量取得
	double GetVolume(const String& name) const
	{
		if (auto it = m_audios.find(name); it != m_audios.end())
		{
			return it->second.volume * m_mastervol;
		}
		return 0.0;
	}

	//  全体音量設定（例：マスターボリューム）
	void SetMasterVolume(double volume)
	{
		volume = Clamp(volume, 0.0, 1.0);
		m_mastervol = volume;
		for (auto& [key, data] : m_audios)
		{
			data.volume = volume * m_mastervol;
			data.audio.setVolume(volume * m_mastervol);
		}
	}

	void FadeOut(const String& key, double seconds)
	{
		if (auto it = m_audios.find(key); it != m_audios.end())
		{
			m_fades.push_back({ it->second.audio.getVolume() * m_mastervol, 0.0, seconds, 0.0, key });
		}
	}

};
