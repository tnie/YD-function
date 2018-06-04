#pragma once
#include <functional>
#include <memory>

using QID = unsigned long;
using CBD = int;
struct Dyna
{
    Dyna(double o, double c) : OpenPrice(o), ClosePrice(c)
    {

    }
    double OpenPrice;
    double ClosePrice;
};

using YDDATA2CALLBACK1 = std::function<void(QID qid, CBD cbd, int period, const std::shared_ptr<Dyna> data)>;

QID YDdata_subscribeDynaWithOrder(const char *code, YDDATA2CALLBACK1 cb, const char* order = nullptr, bool desc = false);
