#pragma once

namespace ieg
{
	class BufferManager;
	class ColorRGBA8;

    class TextComponent final
        : public ModelComponent
    {
	public:
		explicit TextComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~TextComponent() = default;
		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Collision() override {};
		void Switch() override {};

		void SetText(const std::string& text, int colorIndex);
		void SetRenderViewComponent(RenderViewComponent* pRenderViewComponent);
	private:
		BufferManager* mpBufferManager;
		ColorRGBA8* mpPalette;
		std::string mText;
		int mColorIndex;
		bool mNeedsUpdate;
		RenderViewComponent* mpRenderViewComponent;

		static const int mWidth;
		static const int mHeight;
		static const int mChrWidth;
		static const int mChrHeight;

		void DrawChr(ColorRGBA8* pChr, ColorRGBA8* pPixels, int loc);
		void DrawStr(ColorRGBA8* pFont, ColorRGBA8* pPixels, int loc, const std::string& str);
	};
}
