//
// Created by ShiYang Jia on 2023/10/7.
//

#ifndef HYDUI_ERROR_HPP
#define HYDUI_ERROR_HPP

#include <exception>
#include <string>
#include <utility>

namespace HYDUI {

// DUI异常类
class DUIException : public std::exception {
private:
	std::string mesStr;
public:
	explicit DUIException(const char* message) : mesStr(message) {};
	explicit DUIException(std::string  message) : mesStr(std::move(message)) {};

	[[nodiscard]] const char * what() const noexcept override;

};

};

#endif //HYDUI_ERROR_HPP
