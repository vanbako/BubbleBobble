#pragma once
#include <string>

namespace ieg
{
	class Buffer;

	enum class EnumBuffer
	{
		Ablocks = 0,
		Adwarf,
		Aextend,
		Airflow,
		Apic,
		Asecret,
		Asprites,
		Bdata,
		Bubble,
		Bubcode,
		Count
	};
	class BufferManager final
	{
	public:
		explicit BufferManager();
		~BufferManager();
		BufferManager(const BufferManager&) = delete;
		BufferManager(BufferManager&&) = delete;
		BufferManager& operator= (const BufferManager&) = delete;
		BufferManager& operator= (const BufferManager&&) = delete;

		void LoadFiles();
		Buffer* GetBuffer(EnumBuffer buffer);
	private:
		static const std::vector<std::string> mFilenames;
		std::vector<Buffer*> mpBuffers;
	};
}
