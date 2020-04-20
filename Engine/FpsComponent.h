#pragma once
#include "Component.h"

namespace ieg
{
	class TextComponent;

	class FpsComponent final
		: public Component
	{
	public:
		explicit FpsComponent();
		~FpsComponent() = default;

		void Update(const float deltaTime);
		void Render() const {};

		void SetTextComponent(TextComponent* pTextComponent);
	private:
		float mFps;
		TextComponent* mpTextComponent;
	};
}
