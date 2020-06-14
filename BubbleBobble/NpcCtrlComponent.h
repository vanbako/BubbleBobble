#pragma once

namespace ieg
{
	class Minigin;
	class JumpCommand;
	class LeftCommand;
	class RightCommand;

	enum class NpcMove
	{
		Idle,
		Left,
		Right,
		Count
	};

	class NpcCtrlComponent final
		: public CtrlComponent
	{
	public:
		explicit NpcCtrlComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~NpcCtrlComponent();
		NpcCtrlComponent(const NpcCtrlComponent&) = delete;
		NpcCtrlComponent(NpcCtrlComponent&&) = delete;
		NpcCtrlComponent& operator=(const NpcCtrlComponent&) = delete;
		NpcCtrlComponent& operator=(NpcCtrlComponent&&) = delete;

		void Update(const float deltaTime) override;
		void SetMove(NpcMove move);
		void SwitchX();
	private:
		float mTimer;
		NpcMove mMove;
		JumpCommand* mpJumpCommand;
		LeftCommand* mpLeftCommand;
		RightCommand* mpRightCommand;

		static const int mMinDelay;
		static const int mMaxDelay;
	};
}
