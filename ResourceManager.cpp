#include "ResourceManager.h"

ResourceManager* ResourceManager::GetInstance()
{
    return instance;
}

ResourceManager* ResourceManager::CreateInstance()
{
    if (!instance)
    {
        instance = new ResourceManager();
    }
    return instance;
}

void ResourceManager::AddTexture(Texture* texture)
{
    textures.push_back(texture);
}


void ResourceManager::Destroy()
{
    for (Texture* texture : textures)
    {
        delete texture;
    }
    delete instance;
    instance = nullptr;
}

Texture* ResourceManager::GetTexture(int index)
{
    if (index < 0 || index > textures.size() - 1) return nullptr;
    return textures[index];
}

ResourceManager* ResourceManager::instance = nullptr;