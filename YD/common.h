#pragma once
using QID = unsigned long;
using CBD = int;
struct Dyna
{
    Dyna::Dyna(double o, double c) : OpenPrice(o), ClosePrice(c)
    {

    }
    double OpenPrice;
    double ClosePrice;
};

struct Kline
{
    Kline::Kline(double o, double c) : OpenPrice(o), ClosePrice(c)
    {

    }
    double OpenPrice;
    double ClosePrice;
};
