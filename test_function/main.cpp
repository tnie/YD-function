#include <functional>
#include <iostream>
#include "test.h"
using namespace std;

using f_multiN = std::function<int(int)>;

int main()
{
    auto multi2 = std::bind(multi, 2, std::placeholders::_1);
    auto multi2x20 = std::bind(multi2, 20);
    cout << "2*10 = " << multi2(10) << endl;
    cout << "2*20 = " << multi2x20() << endl;

    // 普通函数
    f_multiN f2 = multi2;
    cout << "2*20 = " << f2(20) << endl;
    cout << f2.target_type().name() << endl;
    // 可调用对象
    f_multiN f3 = Multt3();
    cout << "3*10=" << f3(10) << endl;
    cout << f3.target_type().name() << endl;
    // 类成员函数
    MulttX multt4 = MulttX(4);
    f_multiN f4 = std::bind(&MulttX::multi, &multt4, std::placeholders::_1);
    cout << "4*10=" << f4(10) << endl;
    cout << f4.target_type().name() << endl;
    //
    MulttX multt5 = MulttX(5);
    f_multiN f5 = std::bind(&MulttX::multi, &multt5, std::placeholders::_1);
    cout << "5*10=" << f5(10) << endl;
    cout << f5.target_type().name() << endl;
    //
    MulttZ multt6 = MulttZ(6);
    f_multiN f6 = std::bind(&MulttZ::multi, &multt6, std::placeholders::_1);
    cout << "6*10=" << f6(10) << endl;
    cout << f6.target_type().name() << endl;
    // 相等判断：通过同一个类的不同对象创建的 function 对象是相等的！！
    cout << "f4 == f5: " << std::boolalpha << (f4.target_type() == f5.target_type()) << noboolalpha << endl;    // true
    cout << "f5 == f6: " << std::boolalpha << (f5.target_type() == f6.target_type()) << noboolalpha << endl;    // false
    //
    cout << "MulttZ() tick: " << multt6.tick() << endl;
    return 0;
}