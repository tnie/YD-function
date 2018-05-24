#pragma once
#include <functional>

//int MyMultt(f_multiN& f, int m)   // 传值、传引用区别
int MyMultt(std::function<int(int)> f, int m);
