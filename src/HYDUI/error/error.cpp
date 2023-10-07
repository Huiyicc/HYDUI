//
// Created by ShiYang Jia on 2023/10/7.
//
#include <exception>
#include <string>
#include "HYDUI/error.hpp"

namespace HYDUI {


const char* DUIException::what() const noexcept {
	return mesStr.c_str();
};



};