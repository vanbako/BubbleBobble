#pragma once
#include "CharacterComponent.h"

namespace ieg
{
	class Minigin;

	enum class NpcType
	{
		ZenChan = 0,
		Hidegons,
		Banebou,
		PulPul,
		Monsta,
		Drunk,
		Maita,
		Invader,
		Count
	};

	enum class NpcEvent
	{
		Die
	};

	class NpcComponent final
		: public CharacterComponent
	{
	public:
		explicit NpcComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~NpcComponent() = default;
		NpcComponent(const NpcComponent&) = delete;
		NpcComponent(NpcComponent&&) = delete;
		NpcComponent& operator=(const NpcComponent&) = delete;
		NpcComponent& operator=(NpcComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void Update(const float deltaTime) override;

		void SetNpcType(NpcType npcType);
		NpcType GetNpcType();

		void Jump() override;
		void Left() override;
		void Right() override;
		void Pop();
		bool Capture();
	private:
		NpcType mNpcType;
	};
}
