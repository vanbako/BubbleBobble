#pragma once

namespace ieg
{
	class Scene;
	class GameObject;
	class Minigin;
	class BufferManager;
	class ColorRGBA8;
	class Texture2D;

	enum class CandyType
	{
		Bananas = 0,
		Apple,
		Pear,
		Icecream,
		Cornetto,
		Cake,
		Beer,
		Strawberry,
		Corn,
		Diamond,
		Coctail,
		Fries,
		Strawberrypie,
		Melon,
		Crown,
		Cherrypie,
		Fireworks,
		Sunday
	};

	class Candy
	{
	public:
		explicit Candy() = delete;
		~Candy() = delete;
		Candy(const Candy&) = delete;
		Candy(Candy&&) = delete;
		Candy& operator=(const Candy&) = delete;
		Candy& operator=(Candy&&) = delete;

		static GameObject* CreateCandy(Minigin* pEngine, Scene* pScene, BufferManager* pBufferManager, ColorRGBA8* pPalette);
		static GameObject* CopyCandy(Minigin* pEngine, GameObject* pGOBubble);
	private:
		static const int mWidth;
		static const int mHeight;
		static const int mCount;

		static void DrawSprite(ColorRGBA8* pSprite, ColorRGBA8* pPixels, int offset, int loc);
	};
}
