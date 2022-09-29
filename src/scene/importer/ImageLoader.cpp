#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

#include <core/Core.h>
#include <scene/importer/Importer.h>
#include <scene/Scene.h>
#include <debug/Debug.h>

ArrayList<unsigned char*> images = ArrayList<unsigned char*>();

void initImageLoader()
{
	stbi_set_flip_vertically_on_load(true);
}

Image Scene::Importer::LoadImage(const char* path) 
{
	int width = 0;
	int height = 0;
	int channels = 0;
	
	unsigned char* pixels = stbi_load(path, &width, &height, &channels, 4);
	images.Add(pixels);

	return Image(width, height, channels, pixels);
}

void Scene::Importer::DeleteImageRegistry() 
{
	for (int i = 0; i < images.GetLength(); i++) stbi_image_free(images[i]);
}