//
// Created by ShiYang Jia on 2023/10/7.
//

#ifndef HYDUI_BASE_HPP
#define HYDUI_BASE_HPP

#include "error.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace HYDUI {

struct ThemeContext {
    std::string XMLData;
    std::string ImageData;
};

// 全局配置
struct ConfigContext {
	// 是否使用硬件加速
	bool RendererAccelerated = true;
    ThemeContext Theme;
};
extern ConfigContext g_ConfigContext;

}


#endif //HYDUI_BASE_HPP
