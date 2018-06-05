#include "Interface.h"
#include "InterfaceOld.h"
#include <thread>
#include <chrono>
#include <iostream>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

void _thread_send(YDDATA2CALLBACK1 cb)
{
    auto ptr = std::make_shared<Dyna>(100.23, 109.00);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (cb)
        cb(1, 2, 3, ptr);
}

QID YDdata_subscribeDynaWithOrder(const char *code, YDDATA2CALLBACK1 cb, const char* order /*= nullptr*/, bool desc /*= false*/)
{
    std::thread loop(std::bind(_thread_send, (cb)));
    if (loop.joinable())
    {
        //loop.join();
        loop.detach();
    }
    return 0;
}

// deprecated

//void _thread_deprecated(QUOTE_RECV_CALLBACK_PTR cb)
//{
//    auto ptr = new Dyna(100.23, 109.00);
//    std::this_thread::sleep_for(std::chrono::seconds(5));
//    if (auto cbptr = cb.lock())
//        cbptr->callback(1, 1, 3, (void*)ptr, sizeof(Dyna));
//}
//
//QID YDdata_subscribeDynaWithOrder(const char * code, QUOTE_RECV_CALLBACK_PTR cbwptr, const char * order, bool desc)
//{
//    std::thread loop(std::bind(_thread_deprecated, cbwptr));
//    if (loop.joinable())
//    {
//        //loop.join();
//        loop.detach();
//    }
//    return 0;
//
//    /*auto cbptr = cbwptr.lock();
//    if (cbptr)
//        return YDdata_subscribeDynaWithOrder("SH00001", std::bind(&Quote_recv_callback::callback2, cbptr.get(), _1, _2, _3, _4));
//    else
//        return 0;*/
//}
