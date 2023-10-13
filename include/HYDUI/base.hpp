//
// Created by ShiYang Jia on 2023/10/7.
//

#ifndef HYDUI_BASE_HPP
#define HYDUI_BASE_HPP
#include <SDL2/SDL_mouse.h>
#include "xml/pugixml.hpp"
#include "error.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Cursor;
struct SDL_Event;


namespace HYDUI {

struct ThemeContext {
    std::string XMLData;
    pugi::xml_document XMLDoc;
    std::string ImageData;
    SDL_Surface* ImageSurface = nullptr;
};

// 全局配置
struct ConfigContext {
	// 是否使用硬件加速
	bool RendererAccelerated = true;
    ThemeContext Theme;
};
extern ConfigContext g_ConfigContext;

struct Point {
    int x;
    int y;
};

}


#endif //HYDUI_BASE_HPP
