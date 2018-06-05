#include "InterfaceOld.h"
#include <iostream>
#include <string>
#include <thread>


class Wrapper : public Quote_recv_callback
{
public:
    void callback(QID qid, CBD cbd, int period, const void* dataptr, size_t size) override
    {
        _core->realCallback(qid, cbd, period, dataptr, size);
    }
    //
    class Core
    {
    public:
        virtual void realCallback(QID qid, CBD cbd, int period, const void* dataptr, size_t size) = 0;
        virtual ~Core() = default;
    };
    //
    Wrapper(Core* ptr) : _core(ptr)
    {

    }

private:
    Core* _core;
};

class DEPRECATED : public Wrapper::Core
{
public:
    DEPRECATED() = default;
    DEPRECATED(const std::string& post) :m_postfix(post)
    {

    }
    ~DEPRECATED()
    {
        std::cout << "~DEPRECATED::DEPRECATED()" << std::endl;
    }

    void realCallback(QID qid, CBD cbd, int period, const void* dataptr, size_t size) override
    {
        switch (cbd)
        {
        case 0:
            // kline
            _callback1(qid, period, reinterpret_cast<const Kline*>(dataptr), size / sizeof(Kline));
            break;
        case 1:
            // dyna
            _callback2(qid, period, reinterpret_cast<const Dyna*>(dataptr), size / sizeof(Dyna));

            break;
        case 2:
            // other
            break;
        default:
            break;
        }
    }
    QID subscribeDyna()
    {
        _wrapper = std::make_shared<Wrapper>(this);
        return YDdata_subscribeDynaWithOrder("SH000001", _wrapper);
    }
private:
    std::string m_postfix;
    //
    std::shared_ptr<Wrapper> _wrapper;
    void _callback1(QID qid, int period, const Kline *kptr, size_t count)
    {
        // code
    }
    void _callback2(QID qid, int period, const Dyna *dptr, size_t count)
    {
        // do something
        for (size_t i = 0; i < count; i++)
        {
            std::cout << dptr[i].ClosePrice << m_postfix << std::endl;
        }
    }
};

#ifdef _DEPRECATED

int main()
{
    auto ptr = std::make_shared<DEPRECATED>("£¨Ôª£©");
    ptr->subscribeDyna();

    {
        auto ptr = std::make_shared<DEPRECATED>("£¨$£©");
        ptr->subscribeDyna();
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}

#endif // _DEPRECATED


