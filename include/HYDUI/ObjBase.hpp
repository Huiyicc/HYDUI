//
// Created by 19254 on 2023/10/7.
//

#ifndef HYDUI_OBJBASE_HPP
#define HYDUI_OBJBASE_HPP

#include <map>
#include <list>
#include <string>

namespace HYDUI {

enum Event {
    // 事件_被创建
    // 当组件/窗口被创建时产生此事件。
    Event_Creation,
    // 事件_将被销毁
    // 当组件/窗口将被销毁前产生此事件。
    Event_Destruction,
    // 事件_尺寸被改变
    // 当窗口的尺寸被改变时产生此事件。
    Event_SizeChanged,
    // 事件_被显示
    // 当窗口被显示时产生此事件。
    Event_OnShow,
    // 事件_被隐藏
    // 当窗口被隐藏时产生此事件。
    Event_OnHide,
    // 事件_鼠标左键被按下
    // 当鼠标左键被按下时产生此事件。
    Event_MouseLeftDown,
    // 事件_鼠标左键被释放
    // 当鼠标左键被释放时产生此事件。
    Event_MouseLeftUp,
    // 事件_鼠标右键被按下
    // 当鼠标右键被按下时产生此事件。
    Event_MouseRightDown,
    // 事件_鼠标右键被释放
    // 当鼠标右键被释放时产生此事件。
    Event_MouseRightUp,
    // 事件_鼠标位置被移动
    // 当鼠标位置在组件/窗口内移动时产生此事件。
    Event_MouseMove,
    // 事件_被双击
    // 当组件/窗口被双击时产生此事件。
    Event_OnDoubleClick,
    // 事件_按下某键
    // 当某键被按下时产生此事件。
    Event_OnKeyDown,
    // 事件_放开某键
    // 当某键被放开时产生此事件。
    Event_OnKeyUp,
    // 事件_滚轮被滚动
    // 当鼠标滚轮被滚动时产生此事件。
    Event_MouseWheel,
    // 事件_鼠标进入
    // 当鼠标进入组件/窗口时产生此事件。
    Event_MouseEnter,
    // 事件_鼠标离开
    // 当鼠标离开组件/窗口时产生此事件。
    Event_MouseLeave,
    // 事件_字符输入
    // 当字符被输入时产生此事件。
    Event_CharInput,

};

class EventBase {
protected:

    int _OnEvent(Event event, void *ptr);

    int _EventOnCreation();

public:
//    void RegisterEvent(Event event,void * classPtr, void *ptr);
//
//    virtual void OnEvent(int event, void *ptr) = 0;

    //virtual int EventOnCreation() = 0;

};

}

#endif //HYDUI_OBJBASE_HPP
