#pragma once
#include "ViewComponent.h"

namespace ieg
{
	class Minigin;
	class Font;
	class Renderer;
	class RenderViewComponent;

	class TextViewComponent final
		: public ViewComponent
	{
	public:
		explicit TextViewComponent(Minigin* pEngine, const Font* pFont);
		~TextViewComponent() = default;
		TextViewComponent(const TextViewComponent&) = delete;
		TextViewComponent(TextViewComponent&&) = delete;
		TextViewComponent& operator=(const TextViewComponent&) = delete;
		TextViewComponent& operator=(TextViewComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Render() const override {};

		void SetRenderComponent(RenderViewComponent * pRenderComponent);
		void SetText(const std::string& text);
	private:
		bool mNeedsUpdate;
		const Font* mpFont;
		RenderViewComponent* mpRenderComponent;
		std::string mText;
	};
}
