#pragma once

#include <scene/Image.h>

namespace Scene 
{
	struct TextureProperties
	{
	public:
		enum Wrap
		{
			MIRRORED,
			REAPEAT,
			CLAMP,
			BORDER
		};

		enum Filter
		{
			NEAREST,
			LINEAR
		};

		enum Format
		{
			RGB,
			RGBA,
			RGBA8,
			RGBA16,
			RGBA16F,

			DEPTH
		};

		TextureProperties(Wrap wrap, Filter filter, Format format) : wrap(wrap), filter(filter), format(format) {}

		TextureProperties(Wrap wrap, Filter filter) : wrap(wrap), filter(filter), format(RGBA) {}
		TextureProperties(Wrap wrap, Format format) : wrap(wrap), filter(LINEAR), format(format) {}

		TextureProperties(Wrap wrap) : wrap(wrap), filter(LINEAR), format(RGBA) {}
		TextureProperties(Filter filter) : wrap(MIRRORED), filter(filter), format(RGBA) {}
		TextureProperties(Format format) : wrap(MIRRORED), filter(LINEAR), format(format) {}

		TextureProperties() : wrap(MIRRORED), filter(LINEAR), format(RGBA) {}

		inline Wrap GetWrap() const { return wrap; }
		inline Filter GetFilter() const { return filter; }
		inline Format GetFormat() const { return format; }

	private:
		Wrap wrap;
		Filter filter;
		Format format;
	};

	struct Texture
	{
	public:
		Texture() = default;
		Texture(unsigned int textureID, TextureProperties properties) : textureID(textureID), properties(properties) {}

		inline unsigned int GetTextureID() const { return textureID; }

	private:
		TextureProperties properties;
		unsigned int textureID = 0;
	};
}

using namespace Scene;