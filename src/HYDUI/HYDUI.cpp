//
// Created by ShiYang Jia on 2023/10/7.
//
#include "HYDUI/HYDUI.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "HYDUI/theme.hpp"

namespace HYDUI {

ConfigContext g_ConfigContext;

void DUIInit(std::string_view ThemeFile, bool RendererAccelerated) {
    //初始化SDL引擎
    //0成功，负值失败，所有sdl失败的原因都可以根据SDL_GetError()获得
    //SDL_INIT_EVERYTHING这个参数表示一次性将音视频，计时器，事件等都初始化好
    if (auto code = SDL_Init(SDL_INIT_EVERYTHING);code != 0) {
        throw DUIException("初始化SDL失败:" + std::string(SDL_GetError()));
    }
    if (auto code = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);code == 0) {
        throw DUIException("初始化SDL失败:" + std::string(SDL_GetError()));
    }


    g_ConfigContext.RendererAccelerated = RendererAccelerated;

    LoadTheme(ThemeFile);

}

void DUIExit() {
    if(g_ConfigContext.Theme.ImageSurface) {
        SDL_FreeSurface(g_ConfigContext.Theme.ImageSurface);
    }
    SDL_Quit();
}

};