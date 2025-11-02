#include"stdafx.h"
#include "GameData.h"

namespace Game
{
	GameData& GameData::GetInstance()
	{
		static GameData instance;
		return instance;
	}

}
