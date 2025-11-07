#include "DigitDisplay.hpp"

DigitDisplay::DigitDisplay()
{
}

void DigitDisplay::RenderText(int x, int num)
{
    if (num > 99999)
    {
        num = 99999;
    }
    else if (num < 0)
    {
        num = 0;
    }

    SDL_Renderer *renderer = &SDLApp::Get().GetRenderer();
    std::string str = std::to_string(num);

    for (size_t i = 0; i < str.size(); i++)
    {
        char c = str.at(i);
        SDL_Texture *texture = &GetDigitTexture(static_cast<unsigned int>(c - '0'));
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

        SDL_Rect dst = {x + static_cast<int>(i) * this->digitWidth, 0, digitWidth, digitHeight};

        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
}

SDL_Texture &DigitDisplay::GetDigitTexture(unsigned int digit)
{
    if (digit > 9)
    {
        throw std::invalid_argument("Attempted to render invalid digit.");
    }
    // return TileManager::Get().GetTextureById(MiscObject::DIGIT_ZERO + digit);
    return TileManager::Get().GetTextureById(77 + digit);
}

DigitDisplay::~DigitDisplay()
{
    std::cout << "DigitDisplay Destructor called" << std::endl;
}