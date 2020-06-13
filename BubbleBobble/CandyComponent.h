#pragma once

namespace ieg
{
	class Minigin;
	enum class CandyType;

	class CandyComponent final
		: public ModelComponent
	{
	public:
		explicit CandyComponent(GameObject* pGameObject, Minigin* pEngine, ...);
		~CandyComponent() = default;
		CandyComponent(const CandyComponent&) = delete;
		CandyComponent(CandyComponent&&) = delete;
		CandyComponent& operator=(const CandyComponent&) = delete;
		CandyComponent& operator=(CandyComponent&&) = delete;

		void OnSceneActivation(int value) override { (value); };
		void Update(const float deltaTime) override;
		void Collision() override;
		void Switch() override {};

		void SetLevel(GameObject* pLevel);
		void Seize();
		void SetCandyType(CandyType candyType);
	private:
		GameObject* mpGOLevel;
	};
}
