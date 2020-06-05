#pragma once

namespace ieg
{
	class Minigin;
	class BufferManager;

	class BubbleBobble final
	{
	public:
		explicit BubbleBobble() = delete;
		~BubbleBobble() = delete;
		BubbleBobble(const BubbleBobble&) = delete;
		BubbleBobble(BubbleBobble&&) = delete;
		BubbleBobble& operator=(const BubbleBobble&) = delete;
		BubbleBobble& operator=(BubbleBobble&&) = delete;

		static void Create(Minigin* pEngine, BufferManager* pBufferManager);
	};
}
