#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include <typeindex>

namespace Game
{
	class ResourceManager
	{
	private:
		std::unordered_map<std::type_index, std::unordered_map<std::string, std::weak_ptr<void>>> m_resources;

		ResourceManager(); // コンストラクタを cpp に

	public:
		static ResourceManager& Instance();

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		// --- テンプレート関数（ヘッダ内に実装） ---
		template <typename T>
		std::shared_ptr<T> Load(const std::string& key, const std::string& path)
		{
			std::unordered_map<std::string, std::weak_ptr<void>>& table = m_resources[typeid(T)];
			std::unordered_map<std::string, std::weak_ptr<void>>::iterator it = table.find(key);

			if (it != table.end())
			{
				std::shared_ptr<T> existing = std::static_pointer_cast<T>(it->second.lock());
				if (existing)
				{
					return existing;
				}
			}

			std::shared_ptr<T> resource = std::make_shared<T>(path);

			if constexpr (requires(T t) { t.isEmpty(); })
			{
				if (resource->isEmpty())
				{
					throw std::runtime_error("ResourceManager: Failed to load resource from " + path);
				}
			}

			table[key] = resource;
			return resource;
		}

		template <typename T>
		std::shared_ptr<T> Get(const std::string& key)
		{
			std::unordered_map<std::string, std::weak_ptr<void>>& table = m_resources[typeid(T)];
			std::unordered_map<std::string, std::weak_ptr<void>>::iterator it = table.find(key);

			if (it == table.end())
			{
				throw std::runtime_error("ResourceManager: Resource not found -> " + key);
			}

			std::shared_ptr<T> resource = std::static_pointer_cast<T>(it->second.lock());
			if (!resource)
			{
				throw std::runtime_error("ResourceManager: Resource already released -> " + key);
			}

			return resource;
		}

		template <typename T>
		void Unload(const std::string& key)
		{
			std::unordered_map<std::string, std::weak_ptr<void>>& table = m_resources[typeid(T)];
			table.erase(key);
		}

		template <typename T>
		void UnloadAll()
		{
			m_resources[typeid(T)].clear();
		}

		void Clear();
	};
}
