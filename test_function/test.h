#pragma once

int multi(int x, int y)
{
    return (x*y);
}

class Multt3
{
public:
    int operator() (int y)
    {
        return (3 * y);
    }
    Multt3() = default;

};

class MulttX
{
public:
    MulttX(int x) :m_x(x)
    {

    }
    virtual ~MulttX() {}

    virtual int multi(int y)
    {
        return (m_x*y);
    }
private:
    int m_x;
};

class MulttZ : public MulttX
{
public:
    MulttZ(int x) : MulttX(x), m_tick(0)
    {

    }

    int multi(int y) override
    {
        ++m_tick;
        return MulttX::multi(y);
    }

    int tick() const {
        return m_tick;
    }
private:
    int m_tick;
};
