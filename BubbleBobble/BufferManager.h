#pragma once
#include <string>

namespace ieg
{
	class Buffer;
	class ServiceLocator;

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
		BufferManager& operator=(const BufferManager&) = delete;
		BufferManager& operator=(BufferManager&&) = delete;

		void LoadFiles(ServiceLocator* pServiceLocator);
		Buffer* GetBuffer(EnumBuffer buffer) noexcept;
	private:
		static const std::vector<std::string> mFilenames;
		std::vector<Buffer*> mpBuffers;
	};
}
