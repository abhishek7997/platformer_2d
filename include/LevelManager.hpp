#pragma once

#include <array>
#include <SDL.h>
#include "TileManager.hpp"
#include "tile_types.hpp"

struct Level;

class LevelManager
{
public:
    static LevelManager &Get();
    Level *GetLevel(const unsigned int levelIndex);
    Level *GetCurrentLevel();
    LevelManager(const LevelManager &) = delete;
    void operator=(const LevelManager &) = delete;
    void RenderLevel(const unsigned int currentLevel);
    void Initialize();
    void NextLevel();
    void ResetOffset();
    void LoadLevels();

    void SetPlayerX(int x);
    void SetPlayerY(int y);
    void SetPlayerPos(int x, int y);
    void ResetPlayerPos();
    void SetOffset(int o);

    int GetCurrentOffset();
    ~LevelManager();

private:
    LevelManager();
    std::string m_LevelsFilePath;
    std::vector<Level> m_Levels;
    const int levelWidth = 20 * 16;
    const int levelHeight = 10 * 16;
    int offset;
};

struct Level
{
    int playerStartR;
    int playerStartC;
    std::array<std::array<uint8_t, 100>, 10> level{{}};
    std::vector<std::pair<uint8_t, uint8_t>> monsterPath{};

    void SetTile(size_t x, size_t y, uint8_t tile_id)
    {
        if (x >= 100 || y >= level[x].size())
        {
            return;
        }
        level[x][y] = tile_id;
    }

    void ClearCell(int x, int y)
    {
        level[x][y] = StaticObject::EMPTY;
    }

    void SetPlayerCoords(int32_t x, int32_t y)
    {
        playerStartR = x;
        playerStartC = y;
    }

    bool save(std::ostream &stream) const
    {
        stream.write(reinterpret_cast<const char *>(&playerStartR), sizeof(playerStartR));
        stream.write(reinterpret_cast<const char *>(&playerStartC), sizeof(playerStartC));
        stream.write(reinterpret_cast<const char *>(level.data()), sizeof(level));
        return stream.good();
    }

    bool load(std::istream &stream)
    {
        stream.read(reinterpret_cast<char *>(&playerStartR), sizeof(playerStartR));
        stream.read(reinterpret_cast<char *>(&playerStartC), sizeof(playerStartC));
        stream.read(reinterpret_cast<char *>(level.data()), sizeof(level));
        return stream.good();
    }
};
