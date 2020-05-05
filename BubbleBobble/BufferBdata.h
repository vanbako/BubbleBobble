#pragma once
#include "Buffer.h"

namespace ieg {
	class BufferBdata final
		: public Buffer
	{
	public:
		explicit BufferBdata(const std::string& filename);
		~BufferBdata() = default;
		BufferBdata(const BufferBdata&) = delete;
		BufferBdata(BufferBdata&&) = delete;
		BufferBdata& operator=(const BufferBdata&) = delete;
		BufferBdata& operator=(BufferBdata&&) = delete;

		bool LoadFile() override;
		void GetLayout(char* pLayout, int level);
		void GetEnemies(char* pEnemies, int level);
	private:
		char* GetEnemiesOffset(int level) const;

		static const int mLevelDataOffset;
		static const int mLevelByteWidth;
		static const int mLevelWidth;
		static const int mLevelHeight;
		static const int mLevelEnemyOffset;
	};
}
