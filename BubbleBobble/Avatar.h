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
		explicit Avatar(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette, AvatarType avatarType);
		~Avatar();
		Avatar(const Avatar&) = delete;
		Avatar(Avatar&&) = delete;
		Avatar& operator= (const Avatar&) = delete;
		Avatar& operator= (const Avatar&&) = delete;
	private:
		Minigin* mpEngine;
		Scene* mpScene;
		BufferManager* mpBufferManager;
		AvatarType mAvatarType;
		GameObject* mpGameObject;
		ColorRGBA8* mpPixels;
		Texture2D* mpTexture2D;

		static const size_t mWidth;
		static const size_t mHeight;
		static const size_t mCount;

		void DrawSprite(ColorRGBA8* pSprite, size_t offset, size_t loc);
	};
}

