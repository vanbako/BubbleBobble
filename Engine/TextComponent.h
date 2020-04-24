#pragma once
#include "Component.h"

namespace ieg
{
	class Minigin;
	class Font;
	class Renderer;
	class RenderComponent;

	class TextComponent final
		: public Component
	{
	public:
		explicit TextComponent(Minigin* pEngine, const Font* pFont);
		~TextComponent() = default;
		TextComponent(const TextComponent&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator=(const TextComponent&) = delete;
		TextComponent& operator=(TextComponent&&) = delete;

		void Update(const float deltaTime);
		void Render() const {};

		void SetRenderComponent(RenderComponent * pRenderComponent);
		void SetText(const std::string& text);
	private:
		bool mNeedsUpdate;
		const Font* mpFont;
		RenderComponent* mpRenderComponent;
		std::string mText;
	};
}
