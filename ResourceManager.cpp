#include "ResourceManager.h"

namespace Game
{
	ResourceManager::ResourceManager()
	{
	}

	ResourceManager& ResourceManager::Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	void ResourceManager::Clear()
	{
		m_resources.clear();
	}
}
