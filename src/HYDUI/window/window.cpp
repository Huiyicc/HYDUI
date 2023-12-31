//
// Created by ShiYang Jia on 2023/10/7.
//
#include <iostream>
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

WindowHandle Window::Create(const char *title, int width, int height, int x, int y) {
    //创建窗口
    /*
     * 基本需要用到的也就是窗口标题:第一个参数
    窗口的大小:下面代码中的800是宽,600是高
    SDL_WINDOW_OPENGL 是启用opengl渲染
    创建失败则返回空指针NULL
    */
    m_window = SDL_CreateWindow(title, x, y, width, height,
            WindowFlag::ALLOW_HIGHDPI | WindowFlag::RESIZABLE | WindowFlag::BORDERLESS);

    if (m_window == nullptr) {
        throw DUIException("创建窗口失败");
    }
    //创建渲染结构
    /*失败则返回空指针NULL
    第三个参数需要注意下,	值SDL_RENDERER_PRESENTVSYNC不建议使用，这个使用了就不会按设置的帧频去渲染了，而是按显示器的更新频率去渲染
    SDL_RENDERER_ACCELERATED这个值表示启用硬件加速
    */
    Uint32 lFlags = 0;
    if (g_ConfigContext.RendererAccelerated) {
        lFlags = SDL_RENDERER_ACCELERATED;
    }
    m_render = SDL_CreateRenderer(m_window, -1, lFlags);
    if (m_render == nullptr) {
        throw DUIException("创建渲染器失败");
    }
    return m_window;
};

void Window::Show() {
    while (!m_quit) {
        //循环处理事件
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_quit = true;
            } else if (event.type == SDL_WINDOWEVENT) {

            } else if (event.type == SDL_MOUSEMOTION) {
                // 处理鼠标移动事件
                MouseMoveEvent(event);
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // 鼠标按下
                m_lastMousePoint = {event.motion.x, event.motion.y};
                m_mouseDown = true;

            } else if (event.type == SDL_MOUSEBUTTONUP) {
                // 鼠标释放
                m_lastMousePoint = {0, 0};
                m_mouseDown = false;

            }

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
        SDL_Delay(5);
    }
}

void Window::SetCursor(SDL_SystemCursor id) {
    if (m_cursor) {
        SDL_FreeCursor(m_cursor);
    }
    m_cursor = SDL_CreateSystemCursor(id);
    SDL_SetCursor(m_cursor);
}

void Window::MouseMoveEvent(const SDL_Event&event) {
    if (m_mouseDown) {
        // 窗口跟随鼠标移动
        int x,y;
        SDL_GetWindowPosition(m_window, &x, &y);
        SDL_SetWindowPosition(m_window, x+event.motion.x - m_lastMousePoint.x,
                              y+event.motion.y - m_lastMousePoint.y);
        return;
    }

}

}