#pragma once

namespace ieg
{
	class Scene;
	class Minigin;
	class FireCommand;
	class StartCommand;
	class BufferManager;

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
		BubbleBobble(const BubbleBobble&) = delete;
		BubbleBobble(BubbleBobble&&) = delete;
		BubbleBobble& operator=(const BubbleBobble&) = delete;
		BubbleBobble& operator=(BubbleBobble&&) = delete;

		void Initialize();
		void AddScenes() noexcept;
	private:
		Minigin* mpEngine;
		BufferManager* mpBufferManager;
		std::vector<Scene*> mpScenes;
	};
}
