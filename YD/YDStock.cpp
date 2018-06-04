#include "YDStock.h"
#include <iostream>
#include <string>
#include <thread>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;



int EXAMPLE::g_count = 0;
using Good = EXAMPLE;
// 只允许在先前已被std::shared_ptr 管理的对象上调用 shared_from_this 。否则调用行为未定义
int main()
{
    // 正确的示例
    /*std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();*/
    std::weak_ptr<EXAMPLE> wptr;
    {
        auto ptr = std::make_shared<Good>("属性： ", "（元）");
        ptr->subscribeDyna();
        wptr = ptr->wptr();
    }
    auto temp = wptr;
    // 错误的使用示例：调用 shared_from_this 但其没有被 std::shared_ptr 占有
    //try {
    //    Good not_so_good;
    //    std::shared_ptr<Good> gp1 = not_so_good.getptr();
    //}
    //catch (std::bad_weak_ptr& e) {
    //    // C++17 前为未定义行为； C++17 起抛出 std::bad_weak_ptr 异常
    //    std::cout << e.what() << '\n';
    //}
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}

EXAMPLE::EXAMPLE(const std::string & pre, const std::string & post) :m_prefix(pre), m_postfix(post)
{

}

EXAMPLE::~EXAMPLE()
{
    ++g_count;
    std::cout << "~EXAMPLE::EXAMPLE()" << std::endl;
}

QID EXAMPLE::subscribeDyna()
{
    std::weak_ptr<EXAMPLE> self = shared_from_this();
    return YDdata_subscribeDynaWithOrder("SH000001", std::bind(callback1, _1, _2, _3, _4, self));
}

void callback1(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data, std::weak_ptr<EXAMPLE> ptr)
{
    auto ep = ptr.lock();
    if (ep == nullptr)
        return;
    // code
    ep->setOpen(data->OpenPrice);
    std::cout << ep->prefix() << ep->Open() << ep->postfix() << std::endl;
}
