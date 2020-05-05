#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;
	class Texture2D;

	enum class NpcType
	{
		ZenChan = 0,
		Hidegons,
		Banebou,
		PulPul,
		Monsta,
		Drunk,
		Maita,
		Invader,
		Count
	};

	class Npc final
	{
	public:
		explicit Npc() = delete;
		~Npc() = delete;
		Npc(const Npc&) = delete;
		Npc(Npc&&) = delete;
		Npc& operator=(const Npc&) = delete;
		Npc& operator=(Npc&&) = delete;

		static GameObject* CreateNpc(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, GameObject* pLevel, ColorRGBA8* pPalette, NpcType npcType, int col, int row);
	private:
		static const int mWidth;
		static const int mHeight;
		static const int mCount;

		static void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
	};
}

