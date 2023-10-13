//
// Created by 19254 on 2023/10/7.
//
#include "HYDUI/theme.hpp"
#include "HYDUI/error.hpp"
#include "HYDUI/base.hpp"
#include "xml/pugixml.hpp"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <cstring>

namespace HYDUI {

#define THEME_INDEX "HYDUI-INDEX"
#define THEME_INDEX_XML_BEGIN "HYDUI-XML-BEGIN"
#define THEME_INDEX_XML_END "HYDUI-XML-END"
#define THEME_INDEX_IMG_BEGIN "HYDUI-IMG-BEGIN"
#define THEME_INDEX_IMG_END "HYDUI-IMG-END"
#define THEME_INDEX_DATA "HYDUI-DATA"

void readTheme(std::string_view ThemeFile) {
    // 读取主题包
    std::ifstream file(ThemeFile.data(), std::ios::binary);
    if (!file.is_open()) {
        throw DUIException("打开主题文件失败");
    }

    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    // 创建一个足够大的缓冲区来存储文件内容
    std::string buffData(fileSize, 0);
    // 读取文件内容到缓冲区
    file.read(buffData.data(), fileSize);
    // 检查是否成功读取整个文件
    if (!file) {
        throw DUIException("读取主题文件失败");
    }
    // 关闭文件
    file.close();

    int tmpCount = 0;
    uint32_t count = 0;
    // 验证主题包
    // HYDUI-INDEX[count]HYDUI-XML-ENDHYDUI-IMG-BEGIN[count]HYDUI-IMG-ENDHYDUI-DATA[count]HYDUI-XML-BEGIN[主题XML]HYDUI-XML-ENDHYDUI-IMG-BEGIN[主题图片]HYDUI-IMG-END
    if (buffData.substr(count, strlen(THEME_INDEX)) != THEME_INDEX) {
        throw DUIException("主题文件头校验失败");
    }
    count += strlen(THEME_INDEX);
    tmpCount = *(int *) &buffData.data()[count];
    count += sizeof(int);
    if (tmpCount == 0 || tmpCount > buffData.size()) {
        throw DUIException("主题文件头校验失败");
    }
    std::string indexTree;
    indexTree.resize(tmpCount);
    indexTree = buffData.substr(count, tmpCount);
    count += tmpCount;
    uint32_t indexTreeIndex = 0, xmlSize = 0, imgSize = 0;
    // 解析索引树
    if (indexTree.substr(0, strlen(THEME_INDEX_XML_BEGIN)) != THEME_INDEX_XML_BEGIN
        || indexTree.substr(strlen(THEME_INDEX_XML_BEGIN) + 4, strlen(THEME_INDEX_XML_END)) != THEME_INDEX_XML_END) {
        throw DUIException("主题索引树校验失败");
    }
    indexTreeIndex = strlen(THEME_INDEX_XML_BEGIN);
    xmlSize = *(int *) &indexTree.data()[indexTreeIndex];
    if (xmlSize == 0 || xmlSize > buffData.size()) {
        throw DUIException("主题索引树校验失败");
    }
    indexTreeIndex += sizeof(int) + strlen(THEME_INDEX_XML_END);
    if (indexTree.substr(indexTreeIndex, strlen(THEME_INDEX_IMG_BEGIN)) != THEME_INDEX_IMG_BEGIN
        || indexTree.substr(indexTreeIndex + strlen(THEME_INDEX_IMG_BEGIN) + 4, strlen(THEME_INDEX_IMG_END)) !=
           THEME_INDEX_IMG_END) {
        throw DUIException("主题索引树校验失败");
    }
    indexTreeIndex += strlen(THEME_INDEX_IMG_BEGIN);
    imgSize = *(int *) &indexTree.data()[indexTreeIndex];
    if (imgSize == 0 || imgSize > buffData.size()) {
        throw DUIException("主题索引树校验失败");
    }
    // 读取主题XML与图片
    std::string indexData = buffData.substr(count, strlen(THEME_INDEX_DATA));
    if (indexData != THEME_INDEX_DATA) {
        throw DUIException("主题索引树校验失败");
    }
    uint32_t dataCount = 0;
    count += strlen(THEME_INDEX_DATA);
    dataCount = *(int *) &buffData.data()[count];
    if (dataCount == 0 || dataCount > buffData.size()) {
        throw DUIException("主题索引树校验失败");
    }
    count += sizeof(int);
    std::string indexDataBuff = buffData.substr(count, dataCount);
    count += dataCount;
    if (indexDataBuff.substr(0, strlen(THEME_INDEX_XML_BEGIN)) != THEME_INDEX_XML_BEGIN
        || indexDataBuff.substr(strlen(THEME_INDEX_XML_BEGIN) + xmlSize, strlen(THEME_INDEX_XML_END)) !=
           THEME_INDEX_XML_END) {
        throw DUIException("主题索引树校验失败");
    }
    std::string xmlBuff = indexDataBuff.substr(strlen(THEME_INDEX_XML_BEGIN), xmlSize);
    if (xmlBuff.size() != xmlSize) {
        throw DUIException("主题索引树校验失败");
    }
    count = xmlSize + strlen(THEME_INDEX_XML_BEGIN) + strlen(THEME_INDEX_XML_END);
    if (indexDataBuff.substr(count, strlen(THEME_INDEX_IMG_BEGIN)) != THEME_INDEX_IMG_BEGIN
        || indexDataBuff.substr(count + strlen(THEME_INDEX_IMG_BEGIN) + imgSize, strlen(THEME_INDEX_IMG_END)) !=
           THEME_INDEX_IMG_END) {
        throw DUIException("主题索引树校验失败");
    }
    std::string imgBuff = indexDataBuff.substr(count + strlen(THEME_INDEX_IMG_BEGIN), imgSize);
    if (imgBuff.size() != imgSize) {
        throw DUIException("主题索引树校验失败");
    }
    g_ConfigContext.Theme.XMLData = xmlBuff;
    g_ConfigContext.Theme.ImageData = imgBuff;
    auto imgRW = SDL_RWFromConstMem(g_ConfigContext.Theme.ImageData.data(), g_ConfigContext.Theme.ImageData.size());
    if (imgRW == nullptr) {
        throw DUIException("创建主题图片内存流失败");
    }
    g_ConfigContext.Theme.ImageSurface = IMG_Load_RW(imgRW, 1);
    if (g_ConfigContext.Theme.ImageSurface == nullptr) {
        throw DUIException("解析主题图片失败");
    }

}

void loadXML() {
    auto result = g_ConfigContext.Theme.XMLDoc.load_buffer(g_ConfigContext.Theme.XMLData.data(), g_ConfigContext.Theme.XMLData.size());
    if (!result) {
        throw DUIException("解析主题XML失败");
    }
    auto root = g_ConfigContext.Theme.XMLDoc.child("HY_DirectUI_ThemesPack");
    if (root.empty()) {
        throw DUIException("主题XML根节点错误");
    }
    for (auto &node: root.children()) {
        if (strcmp(node.name(), "common") == 0) {
            std::string name = node.attribute("name").value();
            std::cout << name << std::endl;
        }
    }

}

void LoadTheme(std::string_view ThemeFile) {
    // 读取主题包
    readTheme(ThemeFile);
    // 解析主题包
    loadXML();

}


};

