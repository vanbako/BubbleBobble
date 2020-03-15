#include "pch.h"
#include "FpsComponent.h"
#include "TextComponent.h"
#include <stdio.h>

ieg::FpsComponent::FpsComponent()
	: mFps{ 0.f }
	, mpTextComponent{ nullptr }
{
}

void ieg::FpsComponent::Update(const float deltaTime)
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

void ieg::FpsComponent::SetTextComponent(TextComponent* pTextComponent)
{
	mpTextComponent = pTextComponent;
	mpTextComponent->SetText(std::to_string(mFps));
}
