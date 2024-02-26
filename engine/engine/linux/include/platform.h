#pragma once

#include "SDL.h"
//#include <SDL_vulkan.h>
//#include "SDL_mixer.h"
#include "controller.h"
#include "input.h"
#include <vector>
#include <string>

namespace Nebel
{
    std::vector<char> read_file(const std::string &filename); // const char* &filemane);

    class Platform
    {
    private:
        SDL_Window* window;
        SDL_Event event;
        SDL_GLContext context;
        bool should_close = false;
    public:
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t virtual_width = 1920;
        uint32_t virtual_height = 1080;
        uint32_t screen_width = 1920;
        uint32_t screen_height = 1080;
        float diagonal_dpi = 0;
        float horizontal_dpi = 0;
        float vertical_dpi = 0;
        const char* title;
        double dt = 0.0;
        void Create(uint32_t w, uint32_t h, const char* t);
        void Prepare();
        void Update();
        void LateUpdate();
        bool ShouldClose();
        double GetTime();
        void updateWidthAndHeight();
        void setfullscreen(bool on);
        ~Platform();
        void InitInput();
        void UpdateInput();
	    //void GetInstanceExtensions(uint32_t &instanceExtensionCount, const char** instanceExtensions);
        //void CreateSurface(VkInstance &instance, VkSurfaceKHR* surface); // bool fun();
    };
}