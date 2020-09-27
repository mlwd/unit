
#include <iostream>

#include "Unit.hpp"
#include "Quantity.hpp"

int main()
{
    Quantity<Meter, double> l{1.01};
    Quantity<Kilogram, double> m{1.02};
    Quantity<Second, double> t{2.00};
    Quantity<Ampere, double> i{3.00};
    std::cout << "l = " << l << std::endl;
    std::cout << "m = " << m << std::endl;
    std::cout << "t = " << t << std::endl;
    std::cout << "i = " << i << std::endl;
    std::cout << "l t = " << l * t << std::endl;
    std::cout << "l m t i = " << l * m * t * i << std::endl;
}
