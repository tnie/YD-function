#include "Interface.h"
#include <iostream>
#include <string>
#include <thread>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

/*展现层可能的实现方式*************************************/
class EXAMPLE : public std::enable_shared_from_this<EXAMPLE>
{
public:
    EXAMPLE() = default;
    EXAMPLE(const std::string& pre, const std::string& post) :m_prefix(pre), m_postfix(post)
    {

    }
    ~EXAMPLE()
    {
        ++g_count;
        std::cout << "~EXAMPLE::EXAMPLE()" << std::endl;
    }
    std::shared_ptr<EXAMPLE> getptr() {
        return shared_from_this();
    }

    void callback1(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data, std::weak_ptr<EXAMPLE> ptr)
    {
        if (ptr.lock() == nullptr)
            return;
        // code
        m_open = data->OpenPrice;
        std::cout << m_prefix << m_open << m_postfix << std::endl;
        m_close = data->ClosePrice;
        std::cout << m_prefix << m_close << m_postfix << std::endl;
    }

    QID subscribeDyna()
    {
        auto self = shared_from_this();
        return YDdata_subscribeDynaWithOrder("SH000001", std::bind(&EXAMPLE::callback1, this, _1, _2, _3, _4, std::ref(self)));
    }
private:
    std::string m_prefix;
    std::string m_postfix;
    double m_open;
    double m_close;
    static int g_count;
};

int EXAMPLE::g_count = 0;
using Good = EXAMPLE;
// 只允许在先前已被std::shared_ptr 管理的对象上调用 shared_from_this 。否则调用行为未定义
int main()
{
    // 正确的示例
    /*std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();*/

    {
        auto ptr = std::make_shared<Good>("属性： ", "（元）");
        ptr->subscribeDyna();
    }
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

