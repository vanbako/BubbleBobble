#pragma once
#include "Component.h"

namespace ieg
{
	class RenderComponent;
	class Font;

	class TextComponent
		: public Component
	{
	public:
		explicit TextComponent(const Font* pFont);
		~TextComponent() = default;

		void Update(const float deltaTime);
		void Render() const {};

		void SetRenderComponent(RenderComponent * pRenderComponent);
		void SetText(const std::string & text);
	private:
		bool mNeedsUpdate;
		const Font* mpFont;
		std::string mText;
		RenderComponent* mpRenderComponent;
	};
}
