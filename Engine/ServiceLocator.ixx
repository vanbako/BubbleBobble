module;

#include "fmod.hpp" //Precompiled Header
#pragma warning(push)
#pragma warning(disable: 4505) //Unreferenced local function removed (FMOD_ErrorString)
#include "fmod_errors.h"
#pragma warning(pop)

export module Engine:ServiceLocator;

import std.core;

namespace ieg
{
	enum class MsgType
	{
		Info = 0,
		Warning,
		Fatal,
		Count
	};

	export class Logger
	{
	public:
		explicit Logger(const std::string& location);
		virtual ~Logger() = default;
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		virtual void Message(void* pClass, MsgType msgType, const std::string& msg) = 0;
	protected:
		const std::string mLocation;

		static const std::vector<std::string> mTypeStrings;
	};

	export class NullLogger final
		: public Logger
	{
	public:
		explicit NullLogger(const std::string& location = "");
		~NullLogger() = default;
		NullLogger(const NullLogger&) = delete;
		NullLogger(NullLogger&&) = delete;
		NullLogger& operator=(const NullLogger&) = delete;
		NullLogger& operator=(const NullLogger&&) = delete;

		virtual void Message(void* pClass, MsgType msgType, const std::string& msg) override;
	};

	export class FileLogger final
		: public Logger
	{
	public:
		explicit FileLogger(const std::string& location);
		~FileLogger() = default;
		FileLogger(const FileLogger&) = delete;
		FileLogger(FileLogger&&) = delete;
		FileLogger& operator=(const FileLogger&) = delete;
		FileLogger& operator=(const FileLogger&&) = delete;

		virtual void Message(void* pClass, MsgType msgType, const std::string& msg) override;
	};

	export class Audio
	{
	public:
		explicit Audio() = default;
		virtual ~Audio() = default;
		Audio(const Audio&) = delete;
		Audio(Audio&&) = delete;
		Audio& operator=(const Audio&) = delete;
		Audio& operator=(Audio&&) = delete;

		virtual int AddSound(const std::string& filename, bool loop) = 0;
		virtual void PlaySound(int soundId) = 0;
		virtual void StopSound(int soundId) = 0;
	};

	export class NullAudio final
		: public Audio
	{
	public:
		explicit NullAudio() = default;
		~NullAudio() = default;
		NullAudio(const NullAudio&) = delete;
		NullAudio(NullAudio&&) = delete;
		NullAudio& operator=(const NullAudio&) = delete;
		NullAudio& operator=(const NullAudio&&) = delete;

		virtual int AddSound(const std::string& filename, bool loop) override;
		virtual void PlaySound(int soundId) override { (soundId); };
		virtual void StopSound(int soundId) override { (soundId); };
	};

	export class MutedAudio final
		: public Audio
	{
	public:
		explicit MutedAudio();
		~MutedAudio() = default;
		MutedAudio(const MutedAudio&) = delete;
		MutedAudio(MutedAudio&&) = delete;
		MutedAudio& operator=(const MutedAudio&) = delete;
		MutedAudio& operator=(MutedAudio&&) = delete;

		virtual int AddSound(const std::string& filename, bool loop) override;
		virtual void PlaySound(int soundId) override;
		virtual void StopSound(int soundId) override;
	private:
		std::ofstream mLogFile;
	};

	class RegularAudio final
		: public Audio
	{
	public:
		explicit RegularAudio();
		~RegularAudio();
		RegularAudio(const RegularAudio&) = delete;
		RegularAudio(RegularAudio&&) = delete;
		RegularAudio& operator=(const RegularAudio&) = delete;
		RegularAudio& operator=(RegularAudio&&) = delete;

		virtual int AddSound(const std::string& filename, bool loop) override;
		virtual void PlaySound(int soundId) override;
		virtual void StopSound(int soundId) override;
	private:
		FMOD::System* mpFmodSystem;
		FMOD::ChannelGroup* mpChannelGroup;
		std::vector<FMOD::Sound*> mpSounds;
	};

	export class ServiceLocator final
	{
	public:
		explicit ServiceLocator() = default;
		~ServiceLocator() = default;
		ServiceLocator(const ServiceLocator&) = delete;
		ServiceLocator(ServiceLocator&&) = delete;
		ServiceLocator& operator=(const ServiceLocator&) = delete;
		ServiceLocator& operator=(ServiceLocator&&) = delete;

		static void Init();
		static Audio* GetAudio();
		static void RegisterAudioService(Audio* pAudioService);
		static Logger* GetLogger();
		static void RegisterLoggerService(Logger* pLoggerService);
	private:
		static Audio* mpAudioService;
		static NullAudio mNullAudioService;
		static Logger* mpLoggerService;
		static NullLogger mNullLoggerService;
	};
}
