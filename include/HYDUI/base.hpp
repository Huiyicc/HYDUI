//
// Created by ShiYang Jia on 2023/10/7.
//

#ifndef HYDUI_BASE_HPP
#define HYDUI_BASE_HPP

#include "error.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace HYDUI {

// 全局配置
struct ContextConfig {
	// 是否使用硬件加速
	bool RENDERER_ACCELERATED = true;
};
extern ContextConfig g_contextConfig;

}


#endif //HYDUI_BASE_HPP
