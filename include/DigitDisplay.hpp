#pragma once

#include <string>
#include <SDL.h>
#include "SDLApp.hpp"
#include "TileManager.hpp"
#include "tile_types.hpp"

class DigitDisplay
{
public:
    DigitDisplay();
    void RenderText(int x, int num);
    SDL_Texture &GetDigitTexture(unsigned int digit);
    ~DigitDisplay();

private:
    const int digitWidth = 8;
    const int digitHeight = 11;
};