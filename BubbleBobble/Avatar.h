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
		explicit Avatar(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, GameObject* pLevel, ColorRGBA8* pPalette, AvatarType avatarType);
		~Avatar() = default;
		Avatar(const Avatar&) = delete;
		Avatar(Avatar&&) = delete;
		Avatar& operator=(const Avatar&) = delete;
		Avatar& operator=(Avatar&&) = delete;

		GameObject* GetGameObject();
	private:
		GameObject* mpGOAvatar;

		static const int mWidth;
		static const int mHeight;
		static const int mCount;

		void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
	};
}

