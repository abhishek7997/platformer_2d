
#include "GameState.hpp"

GameState::GameState() : ticks(0), player(new Player()), digitDisplay(std::make_unique<DigitDisplay>())
{
}

GameState &GameState::Get()
{
    static GameState instance;
    return instance;
}

void GameState::AddScore(int score)
{
    this->score += score;
}

void GameState::ApplyGravity()
{
    if (jetpackActivated)
        return;
    this->player->Gravity();
}

Player &GameState::GetPlayer()
{
    return *(this->player);
}

void GameState::SetPlayerPos(const int &x, const int &y)
{
    this->player->SetPlayerPos(x, y);
}

void GameState::ToggleJetpack()
{
    if (this->jetpackFuel == 0)
    {
        this->player->ResetJump();
        return;
    }
    if (jetpackActivated)
    {
        this->player->ResetJump();
        this->player->ResetSpeed();
    }
    else
    {
        this->player->IncreaseSpeed();
    }
    jetpackActivated = !jetpackActivated;
}

void GameState::ConsumeJetpack()
{
    if (this->jetpackFuel > 0 && !this->player->IsDead())
    {
        --(this->jetpackFuel);
    }
    else
    {
        this->player->ResetSpeed();
        this->jetpackActivated = false;
    }
}

bool GameState::IsJetpackActivated()
{
    return jetpackActivated;
}

int GameState::GetCurrentLevel()
{
    return currentLevel;
}

void GameState::RenderStates()
{
    // Display SCORES
    SDL_Renderer *renderer = &SDLApp::Get().GetRenderer();
    SDL_Texture *texture = &TileManager::Get().GetTextureById(MiscObject::TEXT_SCORE);
    SDL_Rect dst = {0, 0, 62, 11};
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);

    digitDisplay->RenderText(63, this->score);

    // Display Current level
    texture = &TileManager::Get().GetTextureById(MiscObject::TEXT_LEVEL);
    int levelTextOffset = 62 + 5 * 8 + 8;
    dst = {levelTextOffset, 0, 62, 11};
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);

    digitDisplay->RenderText(levelTextOffset + 62 + 8, this->currentLevel + 1);

    // Display LIVES text
    texture = &TileManager::Get().GetTextureById(MiscObject::TEXT_LIVES);
    int livesTextOffset = levelTextOffset + 62 + 8 * 3;

    dst = {livesTextOffset, 0, 62, 11};

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);

    // Display number of lives left
    for (int i = 0; i < this->lives; i++)
    {
        dst = {livesTextOffset + 62 + i * 17, 0, 17, 12};
        texture = &TileManager::Get().GetTextureById(MiscObject::LIFE_UNIT);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
    }

    // Display jetpack
    if (gotJetpack)
    {
        texture = &TileManager::Get().GetTextureById(MiscObject::TEXT_JETPACK);
        dst = {0, 185, 62, 11};
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, texture, nullptr, &dst);

        // Display jetpack meter
        // texture = &TileManager::Get().GetTextureById(MiscObject::JETPACK_METER);
        dst = {62 + 8, 185, 130, 12};
        // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        // SDL_RenderCopy(renderer, texture, nullptr, &dst);
        SDL_RenderDrawRect(renderer, &dst);

        // Display jetpack units
        texture = &TileManager::Get().GetTextureById(MiscObject::JETPACK_UNIT);
        for (int i = 0; i < jetpackFuel; i++)
        {
            dst = {74 + 2 * i, 189, 6, 4};
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer, texture, nullptr, &dst);
        }
    }

    // Display gun if accquired
    if (gotGun)
    {
        texture = &TileManager::Get().GetTextureById(MiscObject::TEXT_GUN);
        dst = {62 + 8 + 185, 185, 62, 11};
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, texture, nullptr, &dst);

        texture = &TileManager::Get().GetTextureById(StaticObject::GUN);
        dst = {62 + 8 + 185 + 62 + 8, 185, 62, 11};
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
    }

    // Display Go thru the door text
    if (gotTrophy)
    {
        texture = &TileManager::Get().GetTextureById(MiscObject::TEXT_CANEXIT);
        dst = {62 + 8, 185 + 16, 176, 14};
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
    }
}

void GameState::SetGotTrophy(bool status)
{
    this->gotTrophy = status;
}

void GameState::SetGotJetpack(bool status)
{
    this->gotJetpack = status;
}

void GameState::SetGotGun(bool status)
{
    this->gotGun = status;
}

bool GameState::GotGun()
{
    return this->gotGun;
}

bool GameState::GotTrophy()
{
    return this->gotTrophy;
}

bool GameState::GotJetpack()
{
    return this->gotJetpack;
}

void GameState::Reset()
{
    this->canClimb = false;
    this->gotJetpack = false;
    this->jetpackActivated = false;
    this->gotTrophy = false;
    this->canClimb = false;
    this->gotGun = false;
    this->jetpackFuel = 60;
}

void GameState::DecreaseLives()
{
    --(this->lives);
    if (this->lives == 0)
    {
        std::cout << "Lives set to 0. Resetting...\n";
        this->lives = 3;
        this->currentLevel = 0;
        this->score = 0;
        Reset();
        LevelManager::Get().LoadLevels();
    }
}

void GameState::NextLevel()
{
    this->currentLevel = this->currentLevel + 1;
}

void GameState::Update()
{
    ++(this->ticks);
}

unsigned int GameState::GetTicks()
{
    return this->ticks;
}

void GameState::UpdateOffset(LevelManager &levelManager)
{
    if (this->GetPlayer().GetDirection() == DIR::RIGHT)
    {
        if (this->GetPlayer().GetRectangle().x > SCREENOFFSET::FIVE)
        {
            levelManager.SetOffset(SCREENOFFSET::FIVE);
        }
        else if (this->GetPlayer().GetRectangle().x > SCREENOFFSET::FOUR)
        {
            levelManager.SetOffset(SCREENOFFSET::FOUR);
        }
        else if (this->GetPlayer().GetRectangle().x > SCREENOFFSET::THREE)
        {
            levelManager.SetOffset(SCREENOFFSET::THREE);
        }
        else if (this->GetPlayer().GetRectangle().x > SCREENOFFSET::TWO)
        {
            levelManager.SetOffset(SCREENOFFSET::TWO);
        }
        else if (this->GetPlayer().GetRectangle().x > SCREENOFFSET::ONE)
        {
            levelManager.SetOffset(SCREENOFFSET::ONE);
        }
    }
    else if (this->GetPlayer().GetDirection() == DIR::LEFT)
    {
        if (this->GetPlayer().GetRectangle().x < SCREENOFFSET::ONE)
        {
            levelManager.SetOffset(SCREENOFFSET::ZERO);
        }
        else if (this->GetPlayer().GetRectangle().x < SCREENOFFSET::TWO)
        {
            levelManager.SetOffset(SCREENOFFSET::ONE);
        }
        else if (this->GetPlayer().GetRectangle().x < SCREENOFFSET::THREE)
        {
            levelManager.SetOffset(SCREENOFFSET::TWO);
        }
        else if (this->GetPlayer().GetRectangle().x < SCREENOFFSET::FOUR)
        {
            levelManager.SetOffset(SCREENOFFSET::THREE);
        }
        else if (this->GetPlayer().GetRectangle().x < SCREENOFFSET::FIVE)
        {
            levelManager.SetOffset(SCREENOFFSET::FOUR);
        }
    }
}

void GameState::SaveGameState()
{
    try
    {
        std::unique_ptr<char, decltype(&SDL_free)> path(SDL_GetBasePath(), SDL_free);
        if (!path)
        {
            std::cerr << "Error getting base path: " << SDL_GetError() << std::endl;
            throw std::runtime_error("Error getting base path: " + std::string(SDL_GetError()));
        }
        const std::string scores_path = (std::filesystem::path(path.get()) / "scores.dat").string();
        std::ofstream file(scores_path);
        if (file.is_open())
        {
            std::time_t now = std::time(0);
            std::tm *localTime = std::localtime(&now);

            // Format date and time
            char buffer[100];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

            file << "completed_date=" << buffer << "\n";
            file << "score=" << this->score << "\n";
            file << "lives=" << this->lives << "\n";
            file.close();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error saving game state: " << e.what() << std::endl;
    }
}

GameState::~GameState()
{
}
