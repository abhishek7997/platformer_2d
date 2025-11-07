#pragma once

enum StaticObject
{
    EMPTY = 0,
    WALL_MUD = 1,
    DOOR = 2,
    WALL_METAL = 3,
    JETPACK = 4,
    WALL_BLUE = 5,
    FIRE_1 = 6,
    FIRE_2 = 7,
    FIRE_3 = 8,
    FIRE_4 = 9,
    TROPHY_1 = 10,
    TROPHY_2 = 11,
    TROPHY_3 = 12,
    TROPHY_4 = 13,
    TROPHY_5 = 14,
    PIPE_RIGHT = 15,
    PIPE_DOWN = 16,
    WALL_RED = 17,
    WALL_MUD_2 = 18,
    WALL_LIGHT_BLUE = 19,
    GUN = 20,
    WALL_HALF_1 = 21,
    WALL_HALF_2 = 22,
    WALL_HALF_3 = 23,
    WALL_HALF_4 = 24,
    WEED_1 = 25,
    WEED_2 = 26,
    WEED_3 = 27,
    WEED_4 = 28,
    DIVIDER_PURPLE = 29,
    PLATFORM = 30,
    PLATFORM_FAKE = 31,
    GRASS_1 = 32,
    TREE_TRUNK = 33,
    GRASS_2 = 34,
    GRASS_3 = 35,
    WATER_1 = 36,
    WATER_2 = 37,
    WATER_3 = 38,
    WATER_4 = 39,
    WATER_5 = 40,
    STARS = 41,
    MOON = 42,
    TREE_TOP_LEFT = 43,
    TREE_TOP_RIGHT = 44,
    TREE_BOTTOM_LEFT = 45,
    TREE_BOTTOM_RIGHT = 46,
    POINT_BLUE = 47,
    POINT_PURPLE = 48,
    POINT_RED = 49,
    POINT_CROWN = 50,
    POINT_RING = 51,
    POINT_WAND = 52
};

enum PlayerObject
{
    PLAYER_WALK_R_1 = 53,
    PLAYER_WALK_R_2 = 54,
    PLAYER_WALK_R_3 = 55,

    PLAYER_FRONT = 56,

    PLAYER_WALK_L_1 = 57,
    PLAYER_WALK_L_2 = 58,
    PLAYER_WALK_L_3 = 59,

    PLAYER_JUMP_R = 60,
    PLAYER_JUMP_L = 61,

    PLAYER_CLIMB_1 = 62,
    PLAYER_CLIMB_2 = 63,
    PLAYER_CLIMB_3 = 64,

    PLAYER_JETPACK_R_1 = 65,
    PLAYER_JETPACK_R_2 = 66,
    PLAYER_JETPACK_R_3 = 67,

    PLAYER_JETPACK_L_1 = 68,
    PLAYER_JETPACK_L_2 = 69,
    PLAYER_JETPACK_L_3 = 70,

    PLAYER_BULLET_R = 71,
    PLAYER_BULLET_L = 72
};

enum EnemyObject
{
    ENEMY_BULLET_R_1 = 121,
    ENEMY_BULLET_R_2 = 122,
    ENEMY_BULLET_R_3 = 123,

    ENEMY_BULLET_L_1 = 124,
    ENEMY_BULLET_L_2 = 125,
    ENEMY_BULLET_L_3 = 126,
};

enum MiscObject
{
    DEATH_1 = 129,
    DEATH_2 = 130,
    DEATH_3 = 131,
    DEATH_4 = 132,
    // TEXT_JETPACK = 133,
    TEXT_JETPACK = 71,
    TEXT_GUN = 134,
    // TEXT_LIVES = 135,
    TEXT_LIVES = 72,
    // TEXT_LEVEL = 136,
    TEXT_LEVEL = 73,
    // TEXT_SCORE = 137,
    TEXT_SCORE = 74,
    TEXT_CANEXIT = 138,
    TEXT_WARP = 139,
    TEXT_ZONE = 140,
    JETPACK_METER = 141,
    // JETPACK_UNIT = 142,
    JETPACK_UNIT = 75,
    // LIFE_UNIT = 143,
    LIFE_UNIT = 76,
    BANNER_1 = 144,
    BANNER_2 = 145,
    BANNER_3 = 146,
    BANNER_4 = 147,
    // DIGIT_ZERO = 148,
    // DIGIT_ONE = 149,
    // DIGIT_TWO = 150,
    // DIGIT_THREE = 151,
    // DIGIT_FOUR = 152,
    // DIGIT_FIVE = 153,
    // DIGIT_SIX = 154,
    // DIGIT_SEVEN = 155,
    // DIGIT_EIGHT = 156,
    // DIGIT_NINE = 157
    DIGIT_ZERO = 77,
    DIGIT_ONE = 78,
    DIGIT_TWO = 79,
    DIGIT_THREE = 80,
    DIGIT_FOUR = 81,
    DIGIT_FIVE = 82,
    DIGIT_SIX = 83,
    DIGIT_SEVEN = 84,
    DIGIT_EIGHT = 85,
    DIGIT_NINE = 86
};

enum DIR
{
    UNSET = -1,
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3
};

enum SCREENOFFSET
{
    ZERO = 0,
    ONE = 18 * 16,
    TWO = 2 * ONE,
    THREE = 3 * ONE,
    FOUR = 4 * ONE,
    FIVE = 5 * ONE
};

struct TileData
{
    int x;
    int y;
    int tileId;
    TileData() : x(0), y(0), tileId(StaticObject::EMPTY)
    {
    }

    TileData(int x, int y, int tileId) : x(x), y(y), tileId(tileId)
    {
    }
};

struct sdl_deleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};