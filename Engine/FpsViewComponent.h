#pragma once
#include "ViewComponent.h"

namespace ieg
{
	class TextViewComponent;
	class Minigin;

	class FpsViewComponent final
		: public ViewComponent
	{
	public:
		explicit FpsViewComponent(Minigin* pEngine);
		~FpsViewComponent() = default;
		FpsViewComponent(const FpsViewComponent&) = delete;
		FpsViewComponent(FpsViewComponent&&) = delete;
		FpsViewComponent& operator=(const FpsViewComponent&) = delete;
		FpsViewComponent& operator=(FpsViewComponent&&) = delete;

		void Update(const float deltaTime) override;
		void Render() const override {};

		void SetTextComponent(TextViewComponent* pTextComponent);
	private:
		float mFps;
		TextViewComponent* mpTextComponent;
	};
}
