#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
	class Minigin;
	class ColorRGBA8;

	class LevelComponent final
		: public ModelComponent
	{
	public:
		explicit LevelComponent(GameObject* pGameObject, Minigin* pEngine,...);
		~LevelComponent();
		LevelComponent(const LevelComponent&) = delete;
		LevelComponent(LevelComponent&&) = delete;
		LevelComponent& operator=(const LevelComponent&) = delete;
		LevelComponent& operator=(LevelComponent&&) = delete;

		virtual void Update(const float deltaTime) override;
	private:
		ColorRGBA8* mpLevelPalette;
		std::vector<GameObject*> mpGOAvatars;

		static const size_t mpAvatarMax;
	};
}
