# include "stdafx.h"
#include "InputManager.h"

namespace Game
{
	// --- ASCII → Input 変換 ---
	Input InputManager::AsciiToInput(char c)
	{
		// 英字テーブル (A..Z)
		static const Input letters[26] =
		{
			KeyA, KeyB, KeyC, KeyD, KeyE, KeyF, KeyG, KeyH, KeyI, KeyJ, KeyK, KeyL, KeyM,
			KeyN, KeyO, KeyP, KeyQ, KeyR, KeyS, KeyT, KeyU, KeyV, KeyW, KeyX, KeyY, KeyZ
		};

		if ('A' <= c && c <= 'Z')
		{
			return letters[c - 'A'];
		}
		if ('a' <= c && c <= 'z')
		{
			return letters[c - 'a'];
		}

		// 数字テーブル (0..9)
		static const Input digits[10] =
		{
			Key0, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8, Key9
		};

		if ('0' <= c && c <= '9')
		{
			return digits[c - '0'];
		}

		// 記号類
		switch (c)
		{
		case '-':  return KeyMinus;
		case '=':  return KeyEqual_US;        // US 配列の =
		case ',':  return KeyComma;
		case '.':  return KeyPeriod;
		case '/':  return KeySlash;
		case ';':  return KeySemicolon_JIS;    // US 配列の ;
		case '\'': return KeyApostrophe_US;   // US 配列の '
		case '[':  return KeyLBracket;
		case ']':  return KeyRBracket;
		case '\\': return KeyBackslash_US;    // バックスラッシュ（US）
		case ' ':  return KeySpace;
		case '\n': return KeyEnter;
		case '\t': return KeyTab;
		default:
			return Input{}; // 無効 (未対応)
		}
	}

	// --- キー登録 (既存の Input overloads と合わせて) ---
	void InputManager::BindKey(const String& action, char ascii)
	{
		Input key = AsciiToInput(ascii);
		if (key != Input{}) // Input の真偽判定 (有効なキーなら true)
		{
			m_bindings[action].push_back(key);
		}
	}

	void InputManager::BindKey(const std::string& action, char ascii)
	{
		BindKey(Unicode::Widen(action), ascii);
	}
	// --- キー登録 ---
	void InputManager::BindKey(const String& action, const Input& key)
	{
		m_bindings[action].push_back(key);
	}

	void InputManager::BindKey(const std::string& action, const Input& key)
	{
		BindKey(Unicode::Widen(action), key);
	}

	// --- 状態チェック ---
	bool InputManager::IsDown(const String& action) const
	{
		auto it = m_bindings.find(action);
		if (it == m_bindings.end()) return false;
		for (const auto& key : it->second)
		{
			if (key.pressed()) return true;
		}
		return false;
	}

	bool InputManager::IsPressed(const String& action) const
	{
		auto it = m_bindings.find(action);
		if (it == m_bindings.end()) return false;
		for (const auto& key : it->second)
		{
			if (key.down()) return true;
		}
		return false;
	}

	bool InputManager::IsUp(const String& action) const
	{
		auto it = m_bindings.find(action);
		if (it == m_bindings.end()) return false;
		for (const auto& key : it->second)
		{
			if (key.up()) return true;
		}
		return false;
	}

	bool InputManager::IsDown(const std::string& action) const
	{
		return IsDown(Unicode::Widen(action));
	}

	bool InputManager::IsPressed(const std::string& action) const
	{
		return IsPressed(Unicode::Widen(action));
	}

	bool InputManager::IsUp(const std::string& action) const
	{
		return IsUp(Unicode::Widen(action));
	}

	bool InputManager::IsKeyDown(const char c) const
	{
		return AsciiToInput(c).down();
	}

	bool InputManager::IsKeyPressed(const char c) const
	{
		return AsciiToInput(c).pressed();
	}

	bool InputManager::IsKeyUp(const char c) const
	{
		return AsciiToInput(c).up();
	}

	bool InputManager::IsLongPressed(const String& action, int32 ms) const
	{
		auto it = m_pressStartTime.find(action);
		if (it == m_pressStartTime.end()) return false;
		return (Time::GetMillisec() - it->second >= ms);
	}

	bool InputManager::IsLongPressed(const std::string& action, int32 ms) const
	{
		return IsLongPressed(Unicode::Widen(action),ms);
	}

	bool InputManager::IsChord(const Array<String>& actions) const
	{
		for (const auto& act : actions)
		{
			if (!IsDown(act)) return false;
		}
		return true;
	}
	 
	// --- コールバック登録 ---
	void InputManager::BindAction(const String& action, InputEventType type, std::function<void()> callback)
	{
		m_callbacks[action][type] = std::move(callback);
	}

	void InputManager::BindAction(const std::string& action, InputEventType type, std::function<void()> callback)
	{
		BindAction(Unicode::Widen(action), type, std::move(callback));
	}

	// --- 更新 & コールバック実行 ---
	void InputManager::Update()
	{
		for (const auto& [action, keys] : m_bindings)
		{
			if (IsPressed(action))
			{
				m_pressStartTime[action] = Time::GetMillisec();

				auto cb = m_callbacks[action].find(InputEventType::Down);
				if (cb != m_callbacks[action].end() && cb->second) cb->second();
			}

			if (IsDown(action))
			{
				auto cb = m_callbacks[action].find(InputEventType::Pressed);
				if (cb != m_callbacks[action].end() && cb->second) cb->second();

				// 長押しイベント
				if (IsLongPressed(action, 500)) // 500ms以上で長押し判定
				{
					auto cb2 = m_callbacks[action].find(InputEventType::LongPress);
					if (cb2 != m_callbacks[action].end() && cb2->second) cb2->second();
				}
			}

			if (IsUp(action))
			{
				m_pressStartTime.erase(action);

				auto cb = m_callbacks[action].find(InputEventType::Up);
				if (cb != m_callbacks[action].end() && cb->second) cb->second();
			}
		}
	}
	void InputManager::UnbindKey(const String& action, const Input& key)
	{
		auto it = m_bindings.find(action);
		if (it == m_bindings.end()) return;

		auto& vec = it->second;
		vec.erase(std::remove(vec.begin(), vec.end(), key), vec.end());

		if (vec.empty())
		{
			// キーが全部なくなったら、コールバックごと削除
			m_bindings.erase(it);
			m_callbacks.erase(action);
		}
	}
	void InputManager::UnbindKey(const std::string& action, const Input& key)
	{
		UnbindKey(Unicode::Widen(action), key);
	}
	void InputManager::UnbindKey(const String& action, char ascii)
	{
		Input key = AsciiToInput(ascii);
		if (key != Input())
		{
			UnbindKey(action, key);
		}
	}
	void InputManager::UnbindKey(const std::string& action, char ascii)
	{
		UnbindKey(Unicode::Widen(action), ascii);
	}
	void InputManager::UnbindAction(const String& action)
	{
		m_bindings.erase(action);
		m_callbacks.erase(action);
	}
	void InputManager::UnbindAction(const std::string& action)
	{
		UnbindAction(Unicode::Widen(action));
	}
	void InputManager::ClearAll()
	{
		m_bindings.clear();
		m_callbacks.clear();
	}
}
