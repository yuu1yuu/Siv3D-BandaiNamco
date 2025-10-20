#pragma once


namespace Game
{
	class GameData final
	{
	public:
		static GameData& GetInstance();

		// データ設定
		template <class T>
		void Set(const std::string& key, const T& value)
		{
			JSON json;
			json = value;
			m_data[key] = json;
		}

		// データ取得（存在しない場合はdefaultValueを返す）
		template <class T>
		T Get(const std::string& key, const T& defaultValue = T{}) const
		{
			if (auto it = m_data.find(key); it != m_data.end())
			{
				return it->second.getOr<T>(defaultValue);
			}
			return defaultValue;
		}

		// データの有無を確認
		bool Has(const std::string& key) const;

		// 全データ削除
		void Clear();

		// セーブ / ロード
		bool Save(const FilePath& path) const;
		bool Load(const FilePath& path);

		// デバッグ表示
		void DrawDebug(const Vec2& pos) const;

	private:
		GameData() = default;
		std::unordered_map<String, JSON> m_data;
	};
}
