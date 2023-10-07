//
// Created by ShiYang Jia on 2023/10/7.
//
#include "HYDUI/HYDUI.hpp"
#include "SDL2/SDL.h"

namespace HYDUI {

ContextConfig g_contextConfig;

void DUIInit(bool RENDERER_ACCELERATED) {
	//初始化SDL引擎
	//0成功，负值失败，所有sdl失败的原因都可以根据SDL_GetError()获得
	//SDL_INIT_EVERYTHING这个参数表示一次性将音视频，计时器，事件等都初始化好
	if (auto code = SDL_Init(SDL_INIT_EVERYTHING);code != 0) {
		throw DUIException("初始化SDL失败");
	}

	g_contextConfig.RENDERER_ACCELERATED = RENDERER_ACCELERATED;


}

void DUIExit() {
	SDL_Quit();
}

};