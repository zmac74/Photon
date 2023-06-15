#include <gl/glew.h>

#include <utils/collection/Buffer.h>
#include <scene/importer/Importer.h>
#include <scene/Scene.h>

static void setTextureParameters(int& wrap, int& filter, int& format, const TextureProperties& textureProperties);
static ArrayList<unsigned int> textureIDs = ArrayList<unsigned int>();

Texture Scene::Importer::LoadTexture(Image image, TextureProperties properties)
{
	int wrap, filter, format;
	setTextureParameters(wrap, filter, format, properties);
	
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	float value, max_anisotropy = 4.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &value);
	if (value > max_anisotropy) value = max_anisotropy;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, value);

	glTexImage2D(GL_TEXTURE_2D, 0, format, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixels());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	textureIDs.Add(textureID);

	return Texture(textureID, properties);
}

Texture Scene::Importer::LoadTexture(unsigned char* pixels, int width, int height, int channels, TextureProperties properties)
{
	Image image = LoadImage(pixels, width, height, channels);
	return LoadTexture(image, properties);
}

Texture Scene::Importer::LoadTexture(const char* path, TextureProperties properties)
{
	Image image = LoadImage(path);
	return LoadTexture(image, properties);
}

Texture Scene::Importer::LoadTexture(unsigned char* pixels, int width, int height, int channels) 
{
	Image image = LoadImage(pixels, width, height, channels);
	return LoadTexture(image, { TextureProperties::MIRRORED, TextureProperties::LINEAR, TextureProperties::RGBA });
}

Texture Scene::Importer::LoadTexture(Image image) 
{
	return LoadTexture(image, { TextureProperties::MIRRORED, TextureProperties::LINEAR, TextureProperties::RGBA });
}

Texture Scene::Importer::LoadTexture(const char* path) 
{
	Image image = LoadImage(path);
	return LoadTexture(image, { TextureProperties::MIRRORED, TextureProperties::LINEAR, TextureProperties::RGBA });
}

Texture Scene::Importer::LoadFrameBufferTexture(int width, int height, TextureProperties properties, int index)
{
	int wrap, filter, format;
	setTextureParameters(wrap, filter, format, properties);
	
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	
	if (properties.GetFormat() == TextureProperties::DEPTH)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureID, 0);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, (GL_COLOR_ATTACHMENT0 + index), GL_TEXTURE_2D, textureID, 0);
	}
	
	glBindTexture(GL_TEXTURE_2D, 0);
	textureIDs.Add(textureID);

	return Texture(textureID, properties);
}

Texture Scene::Importer::LoadFrameBufferTexture(int width, int height, int index)
{
	return LoadFrameBufferTexture(width, height, { TextureProperties::CLAMP, TextureProperties::LINEAR, TextureProperties::RGBA }, index);
}

void Scene::Importer::DeleteTextureRegistry()
{
	for (int i = 0; i < textureIDs.GetLength(); i++) glDeleteTextures(1, &textureIDs[i]);
}

static void setTextureParameters(int& wrap, int& filter, int& format, const TextureProperties& textureProperties)
{
	if (textureProperties.GetWrap() == TextureProperties::REAPEAT) wrap = GL_REPEAT;
	else if (textureProperties.GetWrap() == TextureProperties::MIRRORED) wrap = GL_MIRRORED_REPEAT;
	else if (textureProperties.GetWrap() == TextureProperties::CLAMP) wrap = GL_CLAMP_TO_EDGE;
	else if (textureProperties.GetWrap() == TextureProperties::BORDER) wrap = GL_CLAMP_TO_BORDER;

	if (textureProperties.GetFilter() == TextureProperties::NEAREST) filter = GL_NEAREST;
	else if (textureProperties.GetFilter() == TextureProperties::LINEAR) filter = GL_LINEAR;

	if (textureProperties.GetFormat() == TextureProperties::RGB) format = GL_RGB;
	else if (textureProperties.GetFormat() == TextureProperties::RGBA) format = GL_RGBA;
	else if (textureProperties.GetFormat() == TextureProperties::RGBA8) format = GL_RGBA8;
	else if (textureProperties.GetFormat() == TextureProperties::RGBA16) format = GL_RGBA16;
	else if (textureProperties.GetFormat() == TextureProperties::RGBA16F) format = GL_RGBA16F;
	else if (textureProperties.GetFormat() == TextureProperties::DEPTH) format = GL_DEPTH_COMPONENT;
}