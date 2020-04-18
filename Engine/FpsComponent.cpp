#include "pch.h"
#include "FpsComponent.h"
#include "TextComponent.h"
#include <stdio.h>

using namespace ieg;

FpsComponent::FpsComponent()
	: mFps{ 0.f }
	, mpTextComponent{ nullptr }
{
}

void FpsComponent::Update(const float deltaTime)
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

void FpsComponent::SetTextComponent(TextComponent* pTextComponent)
{
	mpTextComponent = pTextComponent;
	mpTextComponent->SetText(std::to_string(mFps));
}
