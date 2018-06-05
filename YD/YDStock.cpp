#include "Interface.h"
#include <iostream>
#include <string>
#include <thread>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;
using std::placeholders::_5;

/*展现层可能的实现方式*************************************/
class EXAMPLE : public std::enable_shared_from_this<EXAMPLE>
{
public:
    EXAMPLE() = default;
    EXAMPLE(const std::string& post) :m_postfix(post)
    {

    }
    ~EXAMPLE()
    {
        std::cout << "~EXAMPLE::EXAMPLE()" << std::endl;
    }
    std::shared_ptr<EXAMPLE> getptr() {
        return shared_from_this();
    }

    static void callback1(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data, std::weak_ptr<EXAMPLE> wptr)
    {
        auto ptr = wptr.lock();
        if (ptr == nullptr)
            return;
        ptr->_callback1(qid, cbd, period, data);
    }

    // 函数名不同，函数签名相同
    static void callback11(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data, std::weak_ptr<EXAMPLE> wptr)
    {
    }

    static void callback2(QID qid, CBD cbd, int period, const std::shared_ptr<Kline> data, std::weak_ptr<EXAMPLE> wptr)
    {
        auto ptr = wptr.lock();
        if (ptr == nullptr)
            return;
        ptr->_callback2(qid, cbd, period, data);
    }

    QID subscribeDyna()
    {
        std::weak_ptr<EXAMPLE> wptr = shared_from_this();
        return YDdata_subscribeDynaWithOrder("SH000001", std::bind(&EXAMPLE::callback1, _1, _2, _3, _4, wptr));
    }

private:
    std::string m_postfix;
    double m_close;
    void _callback1(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data)
    {
        // code
        m_close = data->ClosePrice;
        std::cout << m_close << m_postfix << std::endl;
    }
    void _callback2(QID qid, CBD cbd, int period, const std::shared_ptr<Kline> data)
    {
        // do something
    }
};

using Good = EXAMPLE;
// 只允许在先前已被std::shared_ptr 管理的对象上调用 shared_from_this 。否则调用行为未定义

template<typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t)*fnPointer;
}

int mainX()
{
    YDDATA2CALLBACK1 ff1 = std::bind(&EXAMPLE::callback1, _1, _2, _3, _4, std::weak_ptr<EXAMPLE>());
    YDDATA2CALLBACK1 ff2 = std::bind(&EXAMPLE::callback11, _1, _2, _3, _4, std::weak_ptr<EXAMPLE>());
    std::cout << ff1.target_type().name() << std::endl;
    std::cout << "ff1 == ff2: " << std::boolalpha << (ff1.target_type() == ff2.target_type()) << std::noboolalpha << std::endl;    // true
    //std::cout << "ff1 == ff2: " << std::boolalpha << (getAddress(ff1) == getAddress(ff2)) << std::noboolalpha << std::endl;    // true

    {
        auto ptr = std::make_shared<Good>("（元）");
        ptr->subscribeDyna();
    }

    auto ptr = std::make_shared<Good>("（$）");
    ptr->subscribeDyna();

    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}

