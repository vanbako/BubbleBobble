#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;
	class Texture2D;

	enum class AvatarType
	{
		Bub = 0,
		Bob,
		Count
	};

	class Avatar final
	{
	public:
		explicit Avatar() = delete;
		~Avatar() = delete;
		Avatar(const Avatar&) = delete;
		Avatar(Avatar&&) = delete;
		Avatar& operator=(const Avatar&) = delete;
		Avatar& operator=(Avatar&&) = delete;

		static GameObject* CreateAvatar(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette, AvatarType avatarType);
	private:
		static const int mWidth;
		static const int mHeight;
		static const int mCount;

		static void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
	};
}

