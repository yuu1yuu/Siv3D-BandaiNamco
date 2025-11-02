#pragma once
class ToppingResources
{
	static constexpr int NUMS = 6;

public:

	static Texture GetRandomTexture()
	{
		Texture tex;

		int i = Random()* NUMS;

		switch (i)
		{
		case 0:
			tex = Texture{ U"../Resources/Textures/Kinoko.png" };
			break;
		case 1:
			tex = Texture{ U"../Resources/Textures/beekonn.png" };

			break;
		case 2:
			tex = Texture{ U"../Resources/Textures/brokkorii.png" };

			break;
		case 3:
			tex = Texture{ U"../Resources/Textures/kusa.png" };

			break;
		case 4:
			tex = Texture{ U"../Resources/Textures/tomato.png" };

			break;

		case 5:
			tex = Texture{ U"../Resources/Textures/ebi.png" };

			break;
		}


		return tex;
	}
};

