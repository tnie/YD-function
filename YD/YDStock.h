#pragma once
#include "Interface.h"
/*展现层可能的实现方式*************************************/


class EXAMPLE : public std::enable_shared_from_this<EXAMPLE>
{
public:
    EXAMPLE() = default;
    EXAMPLE(const std::string& pre, const std::string& post);
    ~EXAMPLE();
    std::shared_ptr<EXAMPLE> getptr() {
        return shared_from_this();
    }
    std::weak_ptr<EXAMPLE> wptr() {
        return shared_from_this();
    }

    void setOpen(double o) { m_open = o; };
    void setClose(double c) { m_close = c; }
    double Open() { return m_open; }
    double Close() { return m_close; }
    std::string prefix() { return m_prefix; }
    std::string postfix() { return m_postfix; }

    QID subscribeDyna();
private:
    std::string m_prefix;
    std::string m_postfix;
    double m_open;
    double m_close;
    static int g_count;
};

void callback1(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data, std::weak_ptr<EXAMPLE> ptr);
