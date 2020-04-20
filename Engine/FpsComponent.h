#pragma once
#include "Component.h"

namespace ieg
{
	class TextComponent;
	class Minigin;

	class FpsComponent final
		: public Component
	{
	public:
		explicit FpsComponent(Minigin* pEngine);
		~FpsComponent() = default;

		void Update(const float deltaTime);
		void Render() const {};

		void SetTextComponent(TextComponent* pTextComponent);
	private:
		Minigin* mpEngine;
		float mFps;
		TextComponent* mpTextComponent;
	};
}
