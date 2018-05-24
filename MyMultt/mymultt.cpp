#include "mymultt.h"

int MyMultt(std::function<int(int)> f, int m)
{
    return f(m);
}
