#pragma once

namespace ieg
{
	class Minigin;
	class Scene;
	class ColorRGBA8;
	class BufferManager;
	class GameObject;
	class Observer;

	class AvatarManager
	{
	public:
		explicit AvatarManager();
		~AvatarManager() = default;
		AvatarManager(const AvatarManager&) = delete;
		AvatarManager(AvatarManager&&) = delete;
		AvatarManager& operator=(const AvatarManager&) = delete;
		AvatarManager& operator=(AvatarManager&&) = delete;

		void CreateAvatars(Minigin * pEngine, BufferManager * pBufferManager, Scene * pScene, ColorRGBA8 * pPalette, Observer* pObserver);
		void Init(GameObject * pGOLevel);
		void DeactivateAll();

		static const int GetAvatarMax() { return mpAvatarMax; };
		static const Vec2<int>& GetAvatarInitialPos(int avatar) { return mpAvatarInitialPos[avatar]; };
	private:
		static const int mpAvatarMax{ 2 };
		std::vector<GameObject*> mpGOAvatars;

		static const Vec2<int> mpAvatarInitialPos[mpAvatarMax];
	};
}
