#pragma once

#include <iostream>
#include <memory>
#include <functional>
#include <SDL.h>
#include <SDL_image.h>

class SDLApp
{
public:
    static SDLApp &Get();
    int Initialize();
    void SetEventCallback(std::function<void(void)> func);
    void SetUpdateCallback(std::function<void(void)> func);
    void SetRenderCallback(std::function<void(void)> func);
    void Run();
    void Stop();
    SDL_Renderer &GetRenderer();
    ~SDLApp();
    SDLApp(const SDLApp &) = delete;
    SDLApp &operator=(const SDLApp &) = delete;

private:
    SDLApp();
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    bool isRunning = true;
    const int m_RenderScale = 3;
    const int m_WindowWidth = 960;
    const int m_WindowHeight = 672;
    const int m_MaxFrameRate = 30;
    const std::string m_Title = "Platform 2.0 - SDL";
    std::function<void(void)> m_EventCallback = []() {};
    std::function<void(void)> m_UpdateCallback = []() {};
    std::function<void(void)> m_RenderCallback = []() {};
};