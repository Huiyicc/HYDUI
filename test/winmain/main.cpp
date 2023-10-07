//
// Created by ShiYang Jia on 2023/10/7.
//
#include "HYDUI/HYDUI.hpp"
#include "HYDUI/window.hpp"

int main() {
	HYDUI::DUIInit("./theme/Default/Default.hy");

	HYDUI::Window window;
	window.Create("hello", 800, 600);
	window.Show();

	HYDUI::DUIExit();
	return 0;
}
