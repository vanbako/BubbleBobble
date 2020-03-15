#pragma once

struct _TTF_Font;

namespace ieg
{
	class Font final
	{
	public:
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();
		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator= (const Font&) = delete;
		Font& operator= (const Font&&) = delete;

		_TTF_Font* GetFont() const;
	private:
		_TTF_Font* mFont;
		unsigned int mSize;
	};
}
