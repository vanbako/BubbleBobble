#pragma once
#include "Buffer.h"

namespace ieg {
	union SpawnLocation
	{
		unsigned int i;
		char c[4];
	};
	class BufferAirflow final
		: public Buffer
	{
	public:
		explicit BufferAirflow(const std::string& filename);
		~BufferAirflow() = default;
		BufferAirflow(const BufferAirflow&) = delete;
		BufferAirflow(BufferAirflow&&) = delete;
		BufferAirflow& operator=(const BufferAirflow&) = delete;
		BufferAirflow& operator=(BufferAirflow&&) = delete;

		bool LoadFile() override;
		SpawnLocation GetSpawnLocations(int level);
	};
}
