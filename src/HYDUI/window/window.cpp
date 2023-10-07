//
// Created by ShiYang Jia on 2023/10/7.
//
#include "HYDUI/window.hpp"
#include "SDL2/SDL.h"

namespace HYDUI {

Window::Window() {

};

Window::~Window() {
	if (m_render) {
		SDL_DestroyRenderer(m_render);
	}
	if (m_render) {
		SDL_DestroyWindow(m_window);
	}
};

void Window::Create(const char *title, int width, int height, int x, int y, WindowFlag flags) {
	//创建窗口
	/*
	 * 基本需要用到的也就是窗口标题:第一个参数
	窗口的大小:下面代码中的800是宽,600是高
	SDL_WINDOW_OPENGL 是启用opengl渲染
	创建失败则返回空指针NULL
	*/
	m_window = SDL_CreateWindow(title, x, y, width, height, (Uint32) flags);
	if (m_window == nullptr) {
		throw DUIException("创建窗口失败");
	}
	//创建渲染结构
	/*失败则返回空指针NULL
	第三个参数需要注意下,	值SDL_RENDERER_PRESENTVSYNC不建议使用，这个使用了就不会按设置的帧频去渲染了，而是按显示器的更新频率去渲染
	SDL_RENDERER_ACCELERATED这个值表示启用硬件加速
	*/
	Uint32 lFlags = 0;
	if (g_contextConfig.RENDERER_ACCELERATED) {
		lFlags = SDL_RENDERER_ACCELERATED;
	}
	m_render = SDL_CreateRenderer(m_window, -1, lFlags);
	if (m_render == nullptr) {
		throw DUIException("创建渲染器失败");
	}

};

void Window::Show() {
	while(!m_quit)
	{
		//循环处理事件
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				m_quit = true;
			//这里可以其它事件处理了
		}
		//这里可以开始更新事件
		//onUpdate();
		//更新完可以渲染界面了
		SDL_RenderClear(m_render);
		//更新你的图片,字体....
		//结束绘制,渲染到屏幕
		//如果创建渲染的时候加了SDL_RENDERER_PRESENTVSYNC这个参数，那么这个地方就不会立马渲染到屏幕
		SDL_RenderPresent(m_render);
		//这里需要让CPU去喝口水上个厕所- -
		//自己设置帧频的时候需要在这里计算delay的时间
		SDL_Delay(10);
	}
}

}