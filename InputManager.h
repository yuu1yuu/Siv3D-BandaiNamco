// InputManager.h
#pragma once
namespace Game
{
	enum class InputEventType
	{
		Down,
		Pressed,
		Up,
		LongPress
	};

	class InputManager final
	{
	private:
		InputManager() = default;
		//  ASCII → Input 変換
		static Input AsciiToInput(char c);

	public:

		// シングルトン取得
		static InputManager& GetInstance()
		{
			static InputManager instance;
			return instance;
		}

		// コピー禁止
		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;

		// --- バインド ---
		void BindKey(const String& action, const Input& key);
		void BindKey(const std::string& action, const Input& key);

		void BindKey(const String& action, char ascii);
		void BindKey(const std::string& action, char ascii);

		// --- 状態チェック ---
		bool IsDown(const String& action) const;
		bool IsPressed(const String& action) const;
		bool IsUp(const String& action) const;

		bool IsDown(const std::string& action) const;
		bool IsPressed(const std::string& action) const;
		bool IsUp(const std::string& action) const;

		bool IsKeyDown(const char c)const;
		bool IsKeyPressed(const char c)const;
		bool IsKeyUp(const char c)const;
		// 長押し判定（ミリ秒指定）
		bool IsLongPressed(const String& action, int32 ms) const;
		bool IsLongPressed(const std::string& action, int32 ms) const;

		// 同時押し判定
		bool IsChord(const Array<String>& actions) const;
		bool IsChord(const Array<std::string>& actions) const;

		// --- コールバック登録 ---
		void BindAction(const String& action, InputEventType type, std::function<void()> callback);
		void BindAction(const std::string& action, InputEventType type, std::function<void()> callback);

		// --- 更新 & コールバック実行 ---
		void Update();
		// --- 特定のキーを解除 ---
		void UnbindKey(const String& action, const Input& key);

		void UnbindKey(const std::string& action, const Input& key);

		void UnbindKey(const String& action, char ascii);

		void UnbindKey(const std::string& action, char ascii);

		// --- アクション全解除 ---
		void UnbindAction(const String& action);

		void UnbindAction(const std::string& action);

		// --- 全部解除 ---
		void ClearAll();
	private:
		std::unordered_map<String, Array<Input>> m_bindings;
		std::unordered_map<String, std::unordered_map<InputEventType, std::function<void()>>> m_callbacks;
		std::unordered_map<String, int32> m_pressStartTime;

	};
}
