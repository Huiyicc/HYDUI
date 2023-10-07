//
// Created by ShiYang Jia on 2023/10/7.
//

#ifndef HYDUI_WINDOW_HPP
#define HYDUI_WINDOW_HPP

#include "base.hpp"

namespace HYDUI {

enum WindowFlag {
	FULLSCREEN = 0x00000001,    // 全屏窗口
	FULLSCREEN_DESKTOP = (FULLSCREEN | 0x00001000),    // 当前桌面分辨率的全屏窗口
	OPENGL = 0x00000002,    // 窗口可用于OpenGL上下文
	VULKAN = 0x10000000,    //可用于Vulkan实例的窗口
	HIDDEN = 0x00000008,    //隐藏窗口
	BORDERLESS = 0x00000010,  //无边框窗口
	RESIZABLE = 0x00000020,    //窗口可以调整大小
	MINIMIZED = 0x00000040,    //窗口最小化
	MAXIMIZED = 0x00000080,    //窗口最大化
	GRABBED = 0x00000100,    //窗口可以捕获键盘输入焦点
	ALLOW_HIGHDPI = 0x00002000,    //如果支持，则应在高DPI模式下创建窗口
	DEFAULT = 0,    //窗口的默认状态
};

class Window {
	SDL_Window *m_window = nullptr;
	SDL_Renderer *m_render = nullptr;
	bool m_quit = false;
public:
	Window();

	~Window();

	// 创建窗口
	void Create(const char *title, int width, int height, int x = (0x1FFF0000u | (0)), int y = (0x1FFF0000u | (0)),
	            WindowFlag flags = WindowFlag::DEFAULT);

	void Show();

private:
};

};

#endif //HYDUI_WINDOW_HPP
