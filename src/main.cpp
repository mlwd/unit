
#include <iostream>

#include "Unit.hpp"
#include "Quantity.hpp"

int main()
{
    Quantity<Meter, double> l{1.00};
    Quantity<Meter, double> l1{1.01};
    Quantity<Meter, double> l2{1.02};
    Quantity<Kilogram, double> m{1.02};
    Quantity<Second, double> t{2.00};
    Quantity<Ampere, double> i{3.00};
    std::cout << "l = " << l << std::endl;
    std::cout << "m = " << m << std::endl;
    std::cout << "t = " << t << std::endl;
    std::cout << "i = " << i << std::endl;
    std::cout << "l t = " << l * t << std::endl;
    std::cout << "l m t i = " << l * m * t * i << std::endl;
    auto a = l / t / t;
    std::cout << "a = " << a << std::endl;
    std::cout << "f = " << m * a << std::endl;
    std::cout << "l + l = " << l + l << std::endl;
    std::cout << "l2 - l1 = " << l2 - l1 << std::endl;
    std::cout << "m * 0.5 = " << m * 0.5 << std::endl;
    std::cout << "0.5 * m = " << 0.5 * m << std::endl;
    m = 2 * m;
    std::cout << "-m = " << -m << std::endl;
}
