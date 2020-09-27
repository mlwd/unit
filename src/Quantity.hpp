#ifndef QUANTITY_HPP
#define QUANTITY_HPP

#include <iostream>

#include "Unit.hpp"

template<class Unit, class Scalar>
struct Quantity
{
    Scalar value;

    friend std::ostream &operator<<(std::ostream &os, Quantity const &q)
    {
        os << q.value;
        auto name = Unit::name();
        if (!name.empty())
        {
            os << " " << name;
        }
        return os;
    }
};

template<class Unit1, class Unit2, class Scalar>
Quantity<ProductUnitT<Unit1, Unit2>, Scalar>
operator*(Quantity<Unit1, Scalar> q1, Quantity<Unit2, Scalar> q2)
{
    return Quantity<ProductUnitT<Unit1, Unit2>, Scalar>{q1.value * q2.value};
}

template<class Unit1, class Unit2, class Scalar>
Quantity<DivisionUnitT<Unit1, Unit2>, Scalar>
operator/(Quantity<Unit1, Scalar> q1, Quantity<Unit2, Scalar> q2)
{
    return Quantity<DivisionUnitT<Unit1, Unit2>, Scalar>{q1.value / q2.value};
}

#endif
