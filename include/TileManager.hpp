#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <SDL_image.h>
#include "SDLApp.hpp"

struct SDLTextureDeleter
{
    void operator()(SDL_Texture *t) const noexcept
    {
        if (t)
            SDL_DestroyTexture(t);
    }
};

class TileManager
{
private:
    void CopyTexture(SDL_Renderer &renderer, SDL_Texture &source, Uint32 &pixelFormat, const int &x, const int &y, const int &w, const int &h, int &tile);
    void LoadGameObjects(SDL_Renderer &renderer, SDL_Texture &source, int &tile, Uint32 pixelFormat);
    void LoadPlayerObjects(SDL_Renderer &renderer, SDL_Texture &source, int &tile, Uint32 pixelFormat);
    void LoadMonsterObjects(SDL_Renderer &renderer, SDL_Texture &source, int &tile, Uint32 pixelFormat);
    void LoadMiscObjects(SDL_Renderer &renderer, SDL_Texture &source, int &tile, Uint32 pixelFormat);
    static TileManager instance;
    TileManager();

public:
    static TileManager &Get();
    TileManager(const TileManager &) = delete;
    void LoadTiles();
    SDL_Texture &GetTextureById(const size_t &id);
    ~TileManager();

private:
    std::string m_TilemapPath;
    const int m_TilemapWidth = 145;
    const int m_TilemapHeight = 110;
    std::array<std::unique_ptr<SDL_Texture, SDLTextureDeleter>, 158> textures;
};
