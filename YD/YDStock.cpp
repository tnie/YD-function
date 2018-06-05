#include "Interface.h"
#include <iostream>
#include <string>
#include <thread>

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

/*չ�ֲ���ܵ�ʵ�ַ�ʽ*************************************/
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

    static void callback1(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data, std::weak_ptr<EXAMPLE> wptr)
    {
        auto ptr = wptr.lock();
        if (ptr == nullptr)
            return;
        ptr->_callback1(qid, cbd, period, data);
    }

    QID subscribeDyna()
    {
        std::weak_ptr<EXAMPLE> wptr = shared_from_this();
        return YDdata_subscribeDynaWithOrder("SH000001", std::bind(&EXAMPLE::callback1, _1, _2, _3, _4, wptr));
    }
private:
    std::string m_prefix;
    std::string m_postfix;
    double m_open;
    double m_close;
    static int g_count;
    void _callback1(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data)
    {
        // code
        m_open = data->OpenPrice;
        std::cout << m_prefix << m_open << m_postfix << std::endl;
        m_close = data->ClosePrice;
        std::cout << m_prefix << m_close << m_postfix << std::endl;
    }
};

int EXAMPLE::g_count = 0;
using Good = EXAMPLE;
// ֻ��������ǰ�ѱ�std::shared_ptr ����Ķ����ϵ��� shared_from_this �����������Ϊδ����
int main()
{
    // ��ȷ��ʾ��
    /*std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();*/

    //{
        auto ptr = std::make_shared<Good>("���ԣ� ", "��Ԫ��");
        ptr->subscribeDyna();
    //}
    // �����ʹ��ʾ�������� shared_from_this ����û�б� std::shared_ptr ռ��
    //try {
    //    Good not_so_good;
    //    std::shared_ptr<Good> gp1 = not_so_good.getptr();
    //}
    //catch (std::bad_weak_ptr& e) {
    //    // C++17 ǰΪδ������Ϊ�� C++17 ���׳� std::bad_weak_ptr �쳣
    //    std::cout << e.what() << '\n';
    //}
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}

