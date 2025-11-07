#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include "LevelManager.hpp"
#include <GameState.hpp>

LevelManager::LevelManager()
{
    std::unique_ptr<char, decltype(&SDL_free)> path(SDL_GetBasePath(), SDL_free);
    if (!path)
    {
        std::cerr << "Error getting base path: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    std::filesystem::path basePath = path.get();
    std::filesystem::path finalPath = basePath / "levels.dat";
    m_LevelsFilePath = finalPath.string();

    std::cout << "Initialized levels.dat path: " << m_LevelsFilePath << std::endl;
    this->Initialize();
}

LevelManager &LevelManager::Get()
{
    static LevelManager instance;
    return instance;
}

Level *LevelManager::GetLevel(const unsigned int levelIndex)
{
    if (levelIndex >= m_Levels.size())
    {
        return nullptr;
    }

    return &m_Levels[levelIndex];
}

void AnimateTile(int &tileId, int salt)
{
    unsigned int mod = 1;
    switch (tileId)
    {
    case StaticObject::FIRE_1:
    // case StaticObject::WEED_1:
    case StaticObject::WEED_1:
    case MiscObject::DEATH_1:
        mod = 4;
        break;
    case StaticObject::TROPHY_1:
    case StaticObject::WATER_1:
        mod = 5;
        break;
    default:
        return;
    }

    tileId = tileId + ((salt + (SDL_GetTicks() / 120)) % mod);
}

void LevelManager::RenderLevel(const unsigned int currentLevel)
{
    if (currentLevel >= m_Levels.size())
        return;

    const Level &level = m_Levels[currentLevel];
    int tileWidth = 16;
    int tileHeight = 16;
    for (int i = 0; i < level.level.size(); i++)
    {
        int o = offset / 16;
        for (int j = o; j < std::min(o + 20 * 16, (int)level.level[i].size()); j++)
        {
            int tileId = level.level[i][j];
            AnimateTile(tileId, j);
            if (tileId > 0)
            {
                // render static tile.
                SDL_Rect rect{16 * (j - o), 16 * (i + 1), 16, 16};
                SDL_RenderCopy(&SDLApp::Get().GetRenderer(), &TileManager::Get().GetTextureById(tileId), nullptr, &rect);
            }
        }
    }

    // std::list<MonsterObject *>::iterator itr = this->enemyObjects.begin();

    // for (itr = this->enemyObjects.begin(); itr != this->enemyObjects.end();)
    // {
    //     if ((*itr)->IsColliding())
    //     {
    //         delete *itr;
    //         itr = this->enemyObjects.erase(itr);
    //     }
    //     else
    //     {
    //         (*itr)->UpdateFrame();
    //         (*itr)->Render(offset);
    //         ++itr;
    //     }
    // }
}

void LevelManager::Initialize()
{
    try
    {
        this->LoadLevels();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during level initialization: " << e.what() << std::endl;
    }

    int r = this->GetCurrentLevel()->playerStartR;
    int c = this->GetCurrentLevel()->playerStartC;
    GameState::Get().SetPlayerPos(c * 16, r * 16);
}

void LevelManager::LoadLevels()
{
    std::cout << "Attempting to load level" << std::endl;

    std::ifstream file(m_LevelsFilePath, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Could not open file for reading: " + m_LevelsFilePath + "\n");
    }

    m_Levels.clear();

    uint64_t levelCount = 0;
    file.read(reinterpret_cast<char *>(&levelCount), sizeof(levelCount));

    if (!file.good() || levelCount == 0)
    {
        throw std::runtime_error("There seems to be some issue with the file or the file does not contain any levels.\n");
    }

    m_Levels.resize(levelCount);
    for (uint64_t i = 0; i < levelCount; ++i)
    {
        if (!m_Levels[i].load(file))
        {
            throw std::runtime_error("Error: Failed to read level #" + std::to_string(i) + " from file. File may be corrupt.\n");
            m_Levels.clear();
        }
    }

    this->ResetPlayerPos();
}

void LevelManager::NextLevel()
{
    GameState::Get().Reset();
    GameState::Get().NextLevel();

    const int idx = GameState::Get().GetCurrentLevel();

    if (idx >= m_Levels.size())
    {
        std::cout << "End of level reached" << std::endl;
        GameState::Get().SaveGameState();
        SDLApp::Get().Stop();
        return;
    }

    GameState::Get().GetPlayer().ResetJump();
    GameState::Get().GetPlayer().ResetSpeed();
    GameState::Get().GetPlayer().Reset();
    GameState::Get()
        .GetPlayer()
        .SetPlayerPos(m_Levels[idx].playerStartC * 16, m_Levels[idx].playerStartR * 16);
    ResetOffset();
}

void LevelManager::ResetPlayerPos()
{
    Level *level = this->GetCurrentLevel();
    const int x = level->playerStartR;
    const int y = level->playerStartC;
    GameState::Get().GetPlayer().ResetJump();
    GameState::Get().GetPlayer().ResetSpeed();
    GameState::Get().GetPlayer().SetPlayerPos(y * 16, x * 16);
}

void LevelManager::ResetOffset()
{
    this->SetOffset(0);
}

Level *LevelManager::GetCurrentLevel()
{
    int idx = GameState::Get().GetCurrentLevel();
    if (idx < 0 || idx >= m_Levels.size())
    {
        return nullptr;
    }

    return &m_Levels[idx];
}

int LevelManager::GetCurrentOffset()
{
    // return m_Levels[GameState::Get().GetCurrentLevel()]->GetOffset();
    return offset;
}

void LevelManager::SetPlayerX(int x)
{
    GameState::Get().GetPlayer().SetPlayerX(x);
}

void LevelManager::SetPlayerY(int y)
{
    GameState::Get().GetPlayer().SetPlayerY(y);
}

void LevelManager::SetPlayerPos(int x, int y)
{
    SetPlayerX(x);
    SetPlayerY(y);
}

void LevelManager::SetOffset(int o)
{
    offset = o;
}

LevelManager::~LevelManager()
{
    std::cout << "LevelManager destructor called" << std::endl;
}