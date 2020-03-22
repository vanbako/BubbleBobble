#pragma once
#include <vector>

namespace ieg
{
	class Scene;
	class Minigin;

	class BubbleBobble final
	{
	public:
		explicit BubbleBobble(Minigin* pEngine);
		~BubbleBobble();

		void AddScenes();
	private:
		Minigin* mpEngine;
		std::vector<Scene*> mpScenes;
	};
}
