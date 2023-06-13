#include <iostream>
#include "fraction.h"

int main1() {

    fraction f1(1,2); // 表示1/2
    fraction f2(1.2, 0.5); // 表示1.2/0.5
    fraction f3(0.6);//转换为分数3/5
    fraction f4 = f1 + f2;
    fraction f5 = f3;//拷贝构造

    //std::cin >> f4; //输入分子，分母，并简化
    
    //加减乘除
    std::cout << f1 + f2 << std::endl;
    std::cout << f1 - f2 << std::endl;
    std::cout << f1 * f2 << std::endl;
    std::cout << f1 / f2 << std::endl;

    //加减乘除2
    std::cout << f3 + 0.5 << std::endl;
    std::cout << 0.5 + f3 << std::endl;
    std::cout << 1 + f3 << std::endl;
    std::cout << f3 + 1 << std::endl;

    std::cout << f3 - 0.5 << std::endl;
    std::cout << 0.5 - f3 << std::endl;
    std::cout << 1 - f3 << std::endl;
    std::cout << f3 - 1 << std::endl;

    std::cout << f3 * 0.5 << std::endl;
    std::cout << 0.5 * f3 << std::endl;
    std::cout << 1 * f3 << std::endl;
    std::cout << f3 * 1 << std::endl;

    std::cout << f3 / 0.5 << std::endl;
    std::cout << 0.5 / f3 << std::endl;
    std::cout << 1 / f3 << std::endl;
    std::cout << f3 / 1 << std::endl;

    std::cout << double(f3) + 1 << std::endl;

    return 0;
}