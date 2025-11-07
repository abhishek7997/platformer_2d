
#include <SDL.h>
#include "TileManager.hpp"

TileManager::TileManager()
{
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cerr << "Could not initialize SDL_Image: " << SDL_GetError() << std::endl;
        return;
    }

    std::unique_ptr<char, decltype(&SDL_free)> path(SDL_GetBasePath(), SDL_free);
    if (!path)
    {
        std::cerr << "Error getting base path: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    m_TilemapPath = (std::filesystem::path(path.get()) / "assets" / "tilesheet.bmp").string();

    std::cout << "Initialized m_TilemapPath path: " << m_TilemapPath << std::endl;

    this->LoadTiles();
}

TileManager &TileManager::Get()
{
    static TileManager instance;
    return instance;
}

void TileManager::CopyTexture(SDL_Renderer &renderer, SDL_Texture &source, Uint32 &pixelFormat, const int &x, const int &y, const int &w, const int &h, int &tile)
{
    SDL_Rect rect = {x, y, w, h};

    textures[tile] = std::unique_ptr<SDL_Texture, SDLTextureDeleter>(SDL_CreateTexture(&renderer, pixelFormat, SDL_TEXTUREACCESS_TARGET, w, h), SDLTextureDeleter());
    SDL_SetTextureBlendMode(textures[tile].get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(&renderer, textures[tile++].get());
    SDL_RenderCopy(&renderer, &source, &rect, NULL);
}

void TileManager::LoadGameObjects(SDL_Renderer &renderer, SDL_Texture &source, int &tile, Uint32 pixelFormat)
{
    const int tileWidth = 16;
    const int tileHeight = 16;
    SDL_Rect rect;
    int i = 0;
    int j = 0;

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 8; j++)
        {
            CopyTexture(renderer, source, pixelFormat, j * tileWidth, i * tileHeight, tileWidth, tileHeight, tile);
        }
    }

    // Load remaining game objects
    i = 6;
    for (j = 0; j < 5; j++)
    {
        rect = {j * tileWidth, i * tileHeight, tileWidth, tileHeight};
        // rect.x = j * tileWidth;
        // rect.y = i * tileHeight;
        // rect.w = tileWidth;
        // rect.h = tileHeight;

        CopyTexture(renderer, source, pixelFormat, j * tileWidth, i * tileHeight, tileWidth, tileHeight, tile);
    }
    std::cout << "Tile count for LoadGameObjects: " << tile << std::endl;
}

void TileManager::LoadPlayerObjects(SDL_Renderer &renderer, SDL_Texture &source, int &tile, Uint32 pixelFormat)
{
    constexpr int tileWidth = 20;
    constexpr int tileHeight = 16;
    int startX = 80;
    int startY = 96;

    // Load some player sprites
    for (int j = 0; j < 3; j++)
    {
        CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    }

    // Load remaining player sprites
    startX = 0;
    startY = 112;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY + i * tileHeight, tileWidth, tileHeight, tile);
        }
    }

    startX = 0;
    startY = 144;
    // Load last player sprite
    CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);
    std::cout << "Tile count for LoadPlayerObjects: " << tile << std::endl;
}

void TileManager::LoadMonsterObjects(SDL_Renderer &renderer, SDL_Texture &source, int &tile, Uint32 pixelFormat)
{
    //     int tileWidth = 28;
    //     int tileHeight = 15;
    //     int startX = 20;
    //     int startY = 181;

    //     // Load monster objects (spider)
    //     for (int j = 0; j < 4; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     // Load monster objects (Blade; first 3)
    //     tileWidth = 24;
    //     tileHeight = 20;
    //     startX = 132;
    //     startY = 176;
    //     for (int j = 0; j < 3; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     startX = 0;
    //     startY = 196;
    //     CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    //     // Load monster objects (Red sun; all 4)
    //     tileWidth = 24;
    //     tileHeight = 21;
    //     startX = 24;
    //     startY = 196;
    //     for (int j = 0; j < 4; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     // Load monster objects (Green stick; first 3)
    //     tileWidth = 24;
    //     tileHeight = 22;
    //     startX = 120;
    //     startY = 196;
    //     for (int j = 0; j < 3; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     // Load last monster object (green stick)
    //     startX = 0;
    //     startY = 218;
    //     CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    //     // Load monster objects (UFO; all 4)
    //     tileWidth = 18;
    //     tileHeight = 8;
    //     startX = 24;
    //     startY = 218;
    //     for (int j = 0; j < 4; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     // Load monster objects (Brown thing; first 3)
    //     tileWidth = 16;
    //     tileHeight = 12;
    //     startX = 96;
    //     startY = 218;
    //     for (int j = 0; j < 3; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     // Load last monster object (brown thing)
    //     startX = 0;
    //     startY = 240;
    //     CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    //     // Load monster objects (Green balls; all 4)
    //     tileWidth = 16;
    //     tileHeight = 16;
    //     startX = 16;
    //     startY = 240;
    //     for (int j = 0; j < 4; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     // Load monster objects (vertical disc; first 3)
    //     tileWidth = 16;
    //     tileHeight = 20;
    //     startX = 80;
    //     startY = 240;
    //     for (int j = 0; j < 3; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     // Load last monster object (vertical disc)
    //     startX = 0;
    //     startY = 260;
    //     CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    //     // Load three enemy bullets (right)
    //     tileWidth = 20;
    //     tileHeight = 3;
    //     startX = 16;
    //     startY = 260;
    //     for (int j = 0; j < 3; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }

    //     // Load three enemy bullets (left)
    //     startX = 75;
    //     startY = 260;
    //     for (int j = 0; j < 3; j++)
    //     {
    //         CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    //     }
    //     std::cout << "Tile count for LoadMonsterObjects: " << tile << std::endl;
}

void TileManager::LoadMiscObjects(SDL_Renderer &renderer, SDL_Texture &source, int &tile, Uint32 pixelFormat)
{
    // Load player bullet (right)
    int tileWidth = 2;
    int tileHeight = 4;
    int startX = 12;
    int startY = 193;

    // CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // // Load player bullet (left)
    // startX = 0;
    // startY = 280;

    // CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // Load death animations
    // tileWidth = 20;
    // tileHeight = 13;
    // startX = 12;
    // startY = 280;
    // for (int j = 0; j < 4; j++)
    // {
    //     CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    // }

    // JETPACK text (71)
    tileWidth = 63;
    tileHeight = 11;
    startX = 0;
    startY = 170;
    CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // GUN Text
    // tileWidth = 26;
    // tileHeight = 11;
    // startX = 80;
    // startY = 160;
    // CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // LIVES:___ (72)
    tileWidth = 52;
    tileHeight = 10;
    startX = 63;
    startY = 170;
    CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // LEVEL:___ (73)
    tileWidth = 62;
    tileHeight = 11;
    startX = 0;
    startY = 181;
    CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // SCORE:___ (74)
    tileWidth = 62;
    tileHeight = 11;
    startX = 51;
    startY = 181;
    CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // GO THRU THE DOOR
    // LEVEL:___
    // tileWidth = 176;
    // tileHeight = 14;
    // startX = 124;
    // startY = 293;
    // CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // WARP Text
    // tileWidth = 73;
    // tileHeight = 15;
    // startX = 300;
    // startY = 293;
    // CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // ZONE Text
    // tileWidth = 67;
    // tileHeight = 15;
    // startX = 373;
    // startY = 293;
    // CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // JETPACK meter
    // tileWidth = 130;
    // tileHeight = 12;
    // startX = 440;
    // startY = 293;
    // CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // JETPACK unit (75)
    tileWidth = 2;
    tileHeight = 4;
    startX = 12;
    startY = 193;
    CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // Lives/Heart unit (76)
    tileWidth = 12;
    tileHeight = 12;
    startX = 0;
    startY = 192;
    CopyTexture(renderer, source, pixelFormat, startX, startY, tileWidth, tileHeight, tile);

    // Banners (4)
    // tileWidth = 112;
    // tileHeight = 47;
    // startX = 0;
    // startY = 308;
    // for (int j = 0; j < 4; j++)
    // {
    //     CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    // }

    // Digits (0 to 9) (77 to 86)
    tileWidth = 8;
    tileHeight = 10;
    startX = 0;
    startY = 160;
    for (int j = 0; j < 10; j++)
    {
        CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    }

    // // Digits (4 to 9)
    // tileWidth = 8;
    // tileHeight = 11;
    // startX = 0;
    // startY = 355;
    // for (int j = 0; j < 6; j++)
    // {
    //     CopyTexture(renderer, source, pixelFormat, startX + j * tileWidth, startY, tileWidth, tileHeight, tile);
    // }

    std::cout << "Tile count for LoadMiscObjects: " << tile << std::endl;
}

void TileManager::LoadTiles()
{
    SDL_Renderer &renderer = SDLApp::Get().GetRenderer();
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(SDL_LoadBMP(m_TilemapPath.c_str()), SDL_FreeSurface);

    if (!surface)
    {
        std::cerr << "Tilemap not loaded" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const SDL_PixelFormat *pixelFormat = surface.get()->format;

    if (SDL_SetColorKey(surface.get(), SDL_TRUE, SDL_MapRGB(pixelFormat, 0x00, 0x00, 0x00)) < 0)
    {
        std::cerr << "Could not set color key: " << SDL_GetError() << std::endl;
    }

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_TilemapTexture(SDL_CreateTextureFromSurface(&renderer, surface.get()), SDL_DestroyTexture);

    if (!m_TilemapTexture)
    {
        std::cerr << "Could not load texture: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int tile = 0;

    LoadGameObjects(renderer, *m_TilemapTexture.get(), tile, pixelFormat->format);
    LoadPlayerObjects(renderer, *m_TilemapTexture.get(), tile, pixelFormat->format);
    LoadMonsterObjects(renderer, *m_TilemapTexture.get(), tile, pixelFormat->format);
    LoadMiscObjects(renderer, *m_TilemapTexture.get(), tile, pixelFormat->format);

    SDL_SetRenderTarget(&renderer, nullptr);

    std::cout << "Final tile count: " << tile << '\n';
}

SDL_Texture &TileManager::GetTextureById(const size_t &id)
{
    return *textures[id];
}

TileManager::~TileManager()
{
    std::cout << "TileManager Destructor called" << std::endl;
}