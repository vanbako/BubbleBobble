#include "pch.h"
#include "FpsViewComponent.h"
#include "TextViewComponent.h"
#include "Minigin.h"
#include <stdio.h>

using namespace ieg;

FpsViewComponent::FpsViewComponent(Minigin* pEngine)
	: ViewComponent(pEngine)
	, mFps{ 0.f }
	, mpTextComponent{ nullptr }
{
}

void FpsViewComponent::Update(const float deltaTime)
{
	if (mpTextComponent != nullptr)
	{
		mFps = 1.f / deltaTime;
		char buf[16];
		sprintf_s(buf, "%.0f FPS", mFps);
		//mpTextComponent->SetText(std::to_string(std::round(mFps)));
		std::string str{ buf };
		mpTextComponent->SetText(str);
	}
}

void FpsViewComponent::SetTextComponent(TextViewComponent* pTextComponent)
{
	mpTextComponent = pTextComponent;
	mpTextComponent->SetText(std::to_string(mFps));
}
