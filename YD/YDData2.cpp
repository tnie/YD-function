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
    std::vector<Dyna> data;
    data.emplace_back(100.23, 109.01);
    data.emplace_back(10.23, 10.02);
    data.emplace_back(1.23, 1.03);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (cb)
        cb(1, 1, 3, data);
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

void _thread_deprecated(QUOTE_RECV_CALLBACK_PTR cb)
{
    const size_t _COUNT_ARRAY = 3;
    auto ptr = new Dyna[_COUNT_ARRAY];
    ptr[0] = { 100.23, 109.03 };
    ptr[1] = { 10.23, 10.02 };
    ptr[2] = { 1.23, 1.01 };
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (auto cbptr = cb.lock())
        cbptr->callback(1, 1, 3, (void*)ptr, sizeof(Dyna)*_COUNT_ARRAY);
}

QID YDdata_subscribeDynaWithOrder(const char * code, QUOTE_RECV_CALLBACK_PTR cbwptr, const char * order, bool desc)
{
    //std::thread loop(std::bind(_thread_deprecated, cbwptr));
    //if (loop.joinable())
    //{
    //    //loop.join();
    //    loop.detach();
    //}
    //return 0;

    auto cbptr = cbwptr.lock();
    if (cbptr)
        return YDdata_subscribeDynaWithOrder("SH00001", std::bind(&Quote_recv_callback::callback2, cbptr.get(), _1, _2, _3, _4), order, desc);
    else
        return 0;
}
