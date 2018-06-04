#include "Interface.h"
#include <thread>
#include <chrono>
#include <iostream>


void _thread_send(YDDATA2CALLBACK1 cb)
{
    auto ptr = std::make_shared<Dyna>(100.23, 109.00);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (cb)
        cb(1, 2, 3, ptr);
}

QID YDdata_subscribeDynaWithOrder(const char *code, YDDATA2CALLBACK1 cb, const char* order /*= nullptr*/, bool desc /*= false*/)
{
    std::thread loop(std::bind(_thread_send, std::ref(cb)));
    if (loop.joinable())
    {
        //loop.join();
        loop.detach();
    }
    return 0;
}