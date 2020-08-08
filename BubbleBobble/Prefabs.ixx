export module BubbleBobble:Prefabs;

import Engine;

namespace ieg
{
	class BufferManager;
	class ObjectsManager;

	export enum class AvatarType
	{
		Bub = 0,
		Bob,
		Count
	};

	export class Avatar final
	{
	public:
		explicit Avatar() = delete;
		~Avatar() = delete;
		Avatar(const Avatar&) = delete;
		Avatar(Avatar&&) = delete;
		Avatar& operator=(const Avatar&) = delete;
		Avatar& operator=(Avatar&&) = delete;

		static GameObject* CreateAvatar(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ObjectsManager* pObjectsManager, ColorRGBA8* pPalette, AvatarType avatarType);
	private:
		static const std::string mInputFile;
		static const int mWidth;
		static const int mHeight;
		static const int mCount;

		static void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
	};
}
