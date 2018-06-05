#include "InterfaceOld.h"
#include <iostream>

void Quote_recv_callback::callback(QID qid, CBD cbd, int period, const void * dataptr, size_t size)/* = 0;*/
{
    std::cout << qid << " " << cbd << " " << period << " " << &dataptr << " " << size << std::endl;
}

void Quote_recv_callback::callback2(QID qid, CBD cbd, int period, const std::vector<Dyna>& data)
{
    // no way: "this" has been destroyed! it's valid.
    // TODO: how judge "this"?
    if (this)
        return callback(qid, cbd, period, reinterpret_cast<const void*>(data.data()), data.size() * sizeof(Dyna));
}



