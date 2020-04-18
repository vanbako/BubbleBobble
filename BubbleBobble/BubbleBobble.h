#pragma once
#include <vector>

namespace ieg
{
	class Scene;
	class Minigin;
	class FireCommand;
	class StartCommand;

	class BubbleBobble final
	{
	public:
		enum class Scenes
		{
			Intro = 0,
			Game,
			Count
		};
		explicit BubbleBobble(Minigin* pEngine);
		~BubbleBobble();

		void AddScenes();
	private:
		Minigin* mpEngine;
		std::vector<Scene*> mpScenes;
		FireCommand* mpFireCommand;
		StartCommand* mpStartCommand;
	};
}
