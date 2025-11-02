#pragma once
#include <unordered_map>
#include <any>
#include <string>

namespace Game
{
	class GameData final
	{
	public:
		static GameData& GetInstance();

		// データ設定（どんな型でもOK）
		template <class T>
		void Set(const std::string& key, const T& value)
		{
			m_data[key] = value; // std::any に格納
		}

		// データ取得（型が違う場合は defaultValue を返す）
		template <class T>
		T Get(const std::string& key)
		{
			auto it = m_data.find(key);
			if (it != m_data.end())
			{
				try
				{
					return std::any_cast<T>(it->second);
				}
				catch (const std::bad_any_cast&)
				{
					// 型が一致しなかった場合
				}
			}
			return 0;
		}

		// データの有無を確認
		bool Has(const std::string& key) const
		{
			return m_data.find(key) != m_data.end();
		}

		// 全データ削除
		void Clear()
		{
			m_data.clear();
		}

	private:
		GameData() = default;

		std::unordered_map<std::string, std::any> m_data;
	};
}
