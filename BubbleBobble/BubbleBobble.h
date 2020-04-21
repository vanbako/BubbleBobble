#pragma once

namespace ieg
{
	class Scene;
	class Minigin;
	class FireCommand;
	class StartCommand;
	class BufferManager;
	class Level;
	class Hud;
	class Intro;

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
		Intro* mpIntro;
		Level* mpLevel;
		Hud* mpHud;
		std::vector<Scene*> mpScenes;
	};
}
