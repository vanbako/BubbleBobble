#pragma once
#include <vector>

namespace ieg
{
	class Scene;
	class Minigin;
	class FireCommand;
	class StartCommand;
	class BufferManager;
	class Level;

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

		void Initialize();
		void AddScenes();
	private:
		Minigin* mpEngine;
		BufferManager* mpBufferManager;
		Level* mpLevel;
		std::vector<Scene*> mpScenes;
		FireCommand* mpFireCommand;
		StartCommand* mpStartCommand;
	};
}
