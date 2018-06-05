#include "InterfaceOld.h"
#include <iostream>

void Quote_recv_callback::callback(QID qid, CBD cbd, int period, const void * dataptr, size_t size)/* = 0;*/
{
    std::cout << qid << " " << cbd << " " << period << " " << &dataptr << " " << size << std::endl;
}

void Quote_recv_callback::callback2(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data)
{

    return callback(qid, cbd, period, data.get(), 0);
}



