//
// Created by 19254 on 2023/10/7.
//
#include "HYDUI/ObjBase.hpp"

namespace HYDUI {

    int EventBase::_OnEvent(Event event, void *ptr) {
        switch (event) {
            default:
                break;
            case Event_Creation:
                return _EventOnCreation();
        }
        return 0;
    }
//
//void EventBase::RegisterEvent(Event event, void *classPtr, void *ptr) {
//    EventCallBack eventCallBack = {event, classPtr, ptr};
//    m_eventPtr[event].push_back(eventCallBack);
//}

    int EventBase::_EventOnCreation() {
        return 0;
    }

}