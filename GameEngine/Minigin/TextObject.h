#pragma once
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextObject
	{
	public:
		void Update();
		void Render() const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);


		explicit TextObject(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:

		bool mNeedsUpdate;
		std::string mText;
		Transform mTransform;
		std::shared_ptr<Font> mFont;
		std::shared_ptr<Texture2D> mTexture;
	};

}
