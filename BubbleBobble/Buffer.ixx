export module BubbleBobble:Buffer;

import std.core;
import Engine;

namespace ieg
{
	class Buffer
	{
	public:
		explicit Buffer(const std::string& filename);
		virtual ~Buffer();
		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = delete;
		Buffer& operator=(const Buffer&) = delete;
		Buffer& operator=(Buffer&&) = delete;

		virtual bool LoadFile();
		char* GetData();
	protected:
		int mSize;
		char* mpData;
	private:
		const std::string mFilename;
	};

	export class BufferAblocks final
		: public Buffer
	{
	public:
		explicit BufferAblocks(const std::string& filename);
		~BufferAblocks() = default;
		BufferAblocks(const BufferAblocks&) = delete;
		BufferAblocks(BufferAblocks&&) = delete;
		BufferAblocks& operator=(const BufferAblocks&) = delete;
		BufferAblocks& operator=(BufferAblocks&&) = delete;

		void GetLevelBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, int level) const;
		void GetLevelBigBlock(ColorRGBA8* pBlock, ColorRGBA8* pPalette, int level) const;
		void GetLevelFalse3D(ColorRGBA8* pFalse3D, ColorRGBA8* pPalette) const;
		void GetCharacter(ColorRGBA8* pChr, ColorRGBA8* pPalette, int color, char chr);
		void GetFont(ColorRGBA8* pFont, ColorRGBA8* pPalette, int color);

		static const int GetFalse3DCount();
		static const int GetBlockPixelCount();
		static const int GetBigBlockPixelCount();
		static const int GetBlockWidth();
		static const int GetBigBlockWidth();
		static const int GetBlockHeight();
		static const int GetBigBlockHeight();
		static const int GetFontWidth();
		static const int GetFontHeight();
		static const int GetFontStart();
		static const char GetFontChrCount();
	private:
		static const int mBitplanes;
		static const int mLevelBlockOffset;
		static const int mLevelBlockRowPitch;
		static const int mLevelBlockBitplanePitch;
		static const int mLevelFalse3DOffset;
		static const int mBlockWidth;
		static const int mBigBlockWidth;
		static const int mBlockByteWidth;
		static const int mBigBlockByteWidth;
		static const int mBlockHeight;
		static const int mBigBlockHeight;
		static const int mFalse3DCount;
		static const int mFontOffset1;
		static const int mFontOffset2;
		static const int mFontWidth;
		static const int mFontByteWidth;
		static const int mFontHeight;
		static const int mFontStart;
		static const int mFontRowPitch;
		static const int mFontBitplanePitch;
		static const char mFontChrCount;
	};

	export class BufferAdwarf final
		: public Buffer
	{
	public:
		explicit BufferAdwarf(const std::string& filename);
		~BufferAdwarf() = default;
		BufferAdwarf(const BufferAdwarf&) = delete;
		BufferAdwarf(BufferAdwarf&&) = delete;
		BufferAdwarf& operator=(const BufferAdwarf&) = delete;
		BufferAdwarf& operator=(BufferAdwarf&&) = delete;
	};

	export class BufferAextend final
		: public Buffer
	{
	public:
		explicit BufferAextend(const std::string& filename);
		~BufferAextend() = default;
		BufferAextend(const BufferAextend&) = delete;
		BufferAextend(BufferAextend&&) = delete;
		BufferAextend& operator=(const BufferAextend&) = delete;
		BufferAextend& operator=(BufferAextend&&) = delete;
	};

	union SpawnLocation
	{
		unsigned int i;
		char c[4];
	};

	export class BufferAirflow final
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

	export class BufferApic final
		: public Buffer
	{
	public:
		explicit BufferApic(const std::string& filename);
		~BufferApic() = default;
		BufferApic(const BufferApic&) = delete;
		BufferApic(BufferApic&&) = delete;
		BufferApic& operator=(const BufferApic&) = delete;
		BufferApic& operator=(BufferApic&&) = delete;

		void GetPic(ColorRGBA8* pPic, ColorRGBA8* pPalette) const;
	private:
		static const int mBitplanes;
		static const int mWidth;
		static const int mByteWidth;
		static const int mHeight;
		static const int mBitplanePitch;
	};

	export class BufferAsecret final
		: public Buffer
	{
	public:
		explicit BufferAsecret(const std::string& filename);
		~BufferAsecret() = default;
		BufferAsecret(const BufferAsecret&) = delete;
		BufferAsecret(BufferAsecret&&) = delete;
		BufferAsecret& operator=(const BufferAsecret&) = delete;
		BufferAsecret& operator=(BufferAsecret&&) = delete;
	};

	export enum class Sprite
		: int
	{
		Bub = 0,
		Bob = 16,
		ZenChan = 32,		// 0
		Hidegons = 48,		// 1
		Banebou = 64,		// 2
		PulPul = 80,		// 3
		Monsta = 88,		// 4
		Drunk = 104,		// 5
		Maita = 120,		// 6
		Invader = 136,		// 7
		SkelMonsta = 144,
		BubFireAnim = 160,
		BobFireAnim = 192,
		BubBalloon = 224,
		BobBalloon = 232,
		ZenChanBubble = 240,
		HidegonsBubble = 248,
		BanebouBubble = 256,
		PulPulBubble = 264,
		MonstaBubble = 272,
		DrunkBubble = 280,
		MaitaBubble = 288,
		InvaderBubble = 296,
		BubBubble = 416,
		BobBubble = 420,
		BubDieAnim = 424,
		BobDieAnim = 428,
		SmallCandy = 481,
		HudBub1Up = 652,
		HudBob1Up = 654,
		HudBUB = 541,
		HudBLE = 542,
		HudBOB = 543
	};

	export class BufferAsprites final
		: public Buffer
	{
	public:
		explicit BufferAsprites(const std::string& filename);
		~BufferAsprites() = default;
		BufferAsprites(const BufferAsprites&) = delete;
		BufferAsprites(BufferAsprites&&) = delete;
		BufferAsprites& operator=(const BufferAsprites&) = delete;
		BufferAsprites& operator=(BufferAsprites&&) = delete;

		void GetSprites(ColorRGBA8* pSprite, int count, Sprite sprite, ColorRGBA8* pPalette) const;

		static const int GetWidth();
		static const int GetByteWidth();
		static const int GetHeight();
	private:
		static const int mBitplanes;
		static const int mWidth;
		static const int mByteWidth;
		static const int mHeight;
	};

	export class BufferBdata final
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

	export class BufferBubble final
		: public Buffer
	{
	public:
		explicit BufferBubble(const std::string& filename);
		~BufferBubble() = default;
		BufferBubble(const BufferBubble&) = delete;
		BufferBubble(BufferBubble&&) = delete;
		BufferBubble& operator=(const BufferBubble&) = delete;
		BufferBubble& operator=(BufferBubble&&) = delete;

		void GetIntroColors(ColorRGBA8* pPalette);
		void GetLevelColors(ColorRGBA8* pPalette, int level);
		int GetLevelBigBlockOffset(int level);

		static int GetPaletteColorCount();
	private:
		static const int mIntroPaletteOffset;
		static const int mPaletteColorCount;
		static const int mPaletteOffset;
		static const int mLevelColorCount;
		static const int mLevelColorsOffset;
		static const int mLevelColorsPaletteOffset;
		static const int mLevelBigBlockOffsets;

		void GetPalette(ColorRGBA8* pPalette, const int offset);
	};

	export class BufferBubcode final
		: public Buffer
	{
	public:
		explicit BufferBubcode(const std::string& filename);
		~BufferBubcode() = default;
		BufferBubcode(const BufferBubcode&) = delete;
		BufferBubcode(BufferBubcode&&) = delete;
		BufferBubcode& operator=(const BufferBubcode&) = delete;
		BufferBubcode& operator=(BufferBubcode&&) = delete;
	};

	export enum class EnumBuffer
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

	export class BufferManager final
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
