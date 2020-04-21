#pragma once

namespace ieg
{
	class Scene;
	class Minigin;
	class FireCommand;
	class StartCommand;
	class BufferManager;
	class Hud;
	class Intro;
	class Start;

	class BubbleBobble final
	{
	public:
		enum class Scenes
		{
			Intro = 0,
			Start,
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
		Hud* mpHud;
		Start* mpStart;
		std::vector<Scene*> mpScenes;
	};
}
