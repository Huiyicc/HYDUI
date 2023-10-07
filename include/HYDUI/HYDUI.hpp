//
// Created by ShiYang Jia on 2023/10/7.
//

#ifndef HYDUI_HYDUI_HPP
#define HYDUI_HYDUI_HPP
#include "base.hpp"

namespace HYDUI {



/**
 * 初始化DUI环境
 *
 * \param RendererAccelerated 是否使用硬件加速
 * \param
 */
void DUIInit(std::string_view ThemeFile,bool RendererAccelerated = true);

// 退出并清理DUI环境
void DUIExit();

}


#endif //HYDUI_HYDUI_HPP
