#include <gl/glew.h>

#include <utils/collection/Buffer.h>
#include <scene/importer/Importer.h>
#include <scene/Scene.h>

static ArrayList<unsigned int> textures = ArrayList<unsigned int>();

Texture Scene::Importer::LoadTexture(Image image) 
{
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	float value, max_anisotropy = 4.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &value);
	value = (value > max_anisotropy) ? max_anisotropy : value;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, value);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixels());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	textures.Add(textureID);

	return Texture(textureID);
}

Texture Scene::Importer::LoadTexture(unsigned char* pixels, int width, int height, int channels)
{
	Image image = LoadImage(pixels, width, height, channels);
	return LoadTexture(image);
}

Texture Scene::Importer::LoadTexture(const char* path) 
{
	Image image = LoadImage(path);
	return LoadTexture(image);
}

void Scene::Importer::DeleteTextureRegistry()
{
	for (int i = 0; i < textures.GetLength(); i++) glDeleteTextures(1, &textures[i]);
}