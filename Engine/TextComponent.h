#pragma once
#include "Component.h"

namespace ieg
{
	class RenderComponent;
	class Font;
	class Renderer;

	class TextComponent
		: public Component
	{
	public:
		explicit TextComponent(const Font* pFont, Renderer* pRenderer);
		~TextComponent() = default;

		void Update(const float deltaTime);
		void Render() const {};

		void SetRenderComponent(RenderComponent * pRenderComponent);
		void SetText(const std::string & text);
	private:
		Renderer* mpRenderer;
		bool mNeedsUpdate;
		const Font* mpFont;
		std::string mText;
		RenderComponent* mpRenderComponent;
	};
}
