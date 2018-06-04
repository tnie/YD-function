#include "Interface.h"
#include <thread>
#include <chrono>
#include <iostream>

YDDATA2CALLBACK1 g_cb;

void _thread_send(/*YDDATA2CALLBACK1 cb*/)
{
    auto ptr = std::make_shared<Dyna>(100.23, 109.00);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (g_cb)
        g_cb(1, 2, 3, ptr);
    std::cout << "why re~EXAMPLE::EXAMPLE()?" << std::endl;
}

QID YDdata_subscribeDynaWithOrder(const char *code, YDDATA2CALLBACK1 cb, const char* order /*= nullptr*/, bool desc /*= false*/)
{
    g_cb = cb;
   /* _thread_send();
    return 0;*/
    std::thread loop(_thread_send/*std::bind(_thread_send, std::ref(cb))*/);
    if (loop.joinable())
    {
        //loop.join();
        loop.detach();
    }
    return 0;
}