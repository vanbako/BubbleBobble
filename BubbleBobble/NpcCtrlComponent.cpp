module BubbleBobble:Component;
import :Command;

using namespace ieg;

const int NpcCtrlComponent::mMinDelay{ 2 };
const int NpcCtrlComponent::mMaxDelay{ 4 };

NpcCtrlComponent::NpcCtrlComponent(GameObject* pGameObject, Minigin* pEngine, ...)
	: CtrlComponent(pGameObject, pEngine)
	, mTimer{ float(std::rand() % (mMaxDelay - mMinDelay + 1) + mMinDelay) }
	, mMove{ NpcMove::Idle }
	, mpJumpCommand{ new JumpCommand{} }
	, mpLeftCommand{ new LeftCommand{} }
	, mpRightCommand{ new RightCommand{} }
{
}

NpcCtrlComponent::~NpcCtrlComponent()
{
	delete mpRightCommand;
	delete mpLeftCommand;
	delete mpJumpCommand;
}

void NpcCtrlComponent::Update(const float deltaTime)
{
	mTimer -= deltaTime;
	if (mTimer <= 0.f)
	{
		mTimer += float(std::rand() % (mMaxDelay - mMinDelay + 1) + mMinDelay);
		int action{ std::rand() % 3 };
		switch (action)
		{
		case 0:
			mMove = NpcMove::Idle;
			mTimer = 0.5f;
			mpJumpCommand->Execute(mpGameObject->GetModelComponent<NpcComponent>());
			break;
		case 1:
			mMove = NpcMove::Left;
			break;
		case 2:
			mMove = NpcMove::Right;
			break;
		}
	}
	else
	{
		switch (mMove)
		{
		case NpcMove::Left:
			mpLeftCommand->Execute(mpGameObject->GetModelComponent<NpcComponent>());
			break;
		case NpcMove::Right:
			mpRightCommand->Execute(mpGameObject->GetModelComponent<NpcComponent>());
			break;
		}
	}
}

void NpcCtrlComponent::SetMove(NpcMove move)
{
	mMove = move;
}

void NpcCtrlComponent::SwitchX()
{
	if (mMove == NpcMove::Left)
		mMove = NpcMove::Right;
	else if (mMove == NpcMove::Right)
		mMove = NpcMove::Left;
}
