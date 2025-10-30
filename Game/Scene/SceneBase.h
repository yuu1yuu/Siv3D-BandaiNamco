#include "Pizzza.h"
#pragma once

namespace Game
{
    class SceneBase
    {
    public:
		SceneBase() = default;

        virtual ~SceneBase() = default;

        // シーン開始時
        virtual void Initialize() {}
        // シーン終了時
        virtual void Finalize() {}

        // 毎フレームの更新処理
        virtual void Update() = 0;
        // 毎フレームの描画処理
        virtual void Draw() const = 0;
    };
}
