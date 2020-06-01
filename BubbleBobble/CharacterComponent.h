#pragma once
#include "../Engine/ModelComponent.h"

namespace ieg
{
    class CharacterComponent
        : public ModelComponent
    {
    public:
        explicit CharacterComponent(GameObject* pGameObject, Minigin* pEngine, ...)
            : ModelComponent(pGameObject, pEngine)
        {};
        virtual ~CharacterComponent() = default;
        CharacterComponent(const CharacterComponent&) = delete;
        CharacterComponent(CharacterComponent&&) = delete;
        CharacterComponent& operator=(const CharacterComponent&) = delete;
        CharacterComponent& operator=(CharacterComponent&&) = delete;

        virtual void Update(const float deltaTime) = 0;
        virtual void Collision() = 0;
        virtual void Switch() = 0;

        virtual void Fire() = 0;
        virtual void Jump() = 0;
        virtual void Left() = 0;
        virtual void Right() = 0;
    };
}
