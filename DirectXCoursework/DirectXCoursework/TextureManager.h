#pragma once
#include "ResourceManager.h"
#include "Rect.h"
#include "Texture.h"

class Texture;

class TextureManager:public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	TexturePtr createTextureFromFile(const wchar_t* file_path);

	TexturePtr createTexture(const Rect& size, Texture::Type type = Texture::Type::RenderTarget);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};

