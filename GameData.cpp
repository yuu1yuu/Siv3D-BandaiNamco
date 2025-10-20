#include"stdafx.h"
#include "GameData.h"

namespace Game
{
	GameData& GameData::GetInstance()
	{
		static GameData instance;
		return instance;
	}

	bool GameData::Has(const std::string& key) const
	{
		return m_data.contains(Unicode::Widen(key));
	}

	void GameData::Clear()
	{
		m_data.clear();
	}

	bool GameData::Save(const FilePath& path) const
	{
		JSON json;
		for (const auto& [key, value] : m_data)
		{
			json[key] = value;
		}
		return json.save(path);
	}

	bool GameData::Load(const FilePath& path)
	{
		if (not FileSystem::Exists(path)) return false;
		JSON json = JSON::Load(path);
		if (not json) return false;

		m_data.clear();
		for (const auto& [key, value] : json) 
		{
			m_data[key] = value;
		}

		return true;
	}

	void GameData::DrawDebug(const Vec2& pos) const
	{
		float y = pos.y;
		for (const auto& [key, value] : m_data)
		{
			FontAsset(U"Debug")(U"{}: {}", key, value.format()).draw(pos.x, y, Palette::Yellow);

			y += 20;
		}
	}
}
