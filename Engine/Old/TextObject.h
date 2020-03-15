#pragma once
#include "SceneObject.h"
#include "Transform.h"

namespace ieg
{
	class ResourceManager;
	class Font;
	class Texture2D;

	class TextObject final
		: public SceneObject
	{
	public:
		explicit TextObject(const ResourceManager* pRes, const std::string& text, const Font* pFont);
		virtual ~TextObject();
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		void Update(const float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(const float x, const float y);
	private:
		const ResourceManager* mpRes;
		bool mNeedsUpdate;
		std::string mText;
		Transform mTransform;
		const Font* mpFont;
		Texture2D* mpTexture;
	};
}
