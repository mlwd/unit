#ifndef QUANTITY_HPP
#define QUANTITY_HPP

#include <ostream>

#include "Unit.hpp"

/**
 * Representation of physical quantity modelled as the product of
 * a scalar value and a unit.
 */
template<class U, class Scalar>
struct Quantity
{
    /**
     * The physical unit of the quantity.
     */
    typedef U Unit;

    /**
     * Construct a physical quantity from a scalar value.
     */
    Quantity(Scalar v) : value(v) {}

    /**
     * Construct a physical quantity from another scalar value.
     */
    template<class OtherScalar>
    Quantity(OtherScalar v) : value(v) {}

    /**
     * The scalar value of the quantity.
     */
    Scalar value;

    /**
     * Stream output of a quantity.
     */
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

/**
 * Product of two quantities.
 */
template<class Unit1, class Unit2, class Scalar>
Quantity<ProductUnitT<Unit1, Unit2>, Scalar>
operator*(Quantity<Unit1, Scalar> q1, Quantity<Unit2, Scalar> q2)
{
    return Quantity<ProductUnitT<Unit1, Unit2>, Scalar>(q1.value * q2.value);
}

/**
 * Scaling of a quantity from the right.
 */
template<class Unit, class Scalar, class OtherScalar>
Quantity<Unit, Scalar> operator*(Quantity<Unit, Scalar> q, OtherScalar s)
{
    return Quantity<Unit, Scalar>(q.value * s);
}

/**
 * Scaling of a quantity from the left.
 */
template<class Unit, class Scalar, class OtherScalar>
Quantity<Unit, Scalar> operator*(OtherScalar s, Quantity<Unit, Scalar> q)
{
    return Quantity<Unit, Scalar>(s * q.value);
}

/**
 * Division of two quantities.
 */
template<class Unit1, class Unit2, class Scalar>
Quantity<DivisionUnitT<Unit1, Unit2>, Scalar>
operator/(Quantity<Unit1, Scalar> q1, Quantity<Unit2, Scalar> q2)
{
    return Quantity<DivisionUnitT<Unit1, Unit2>, Scalar>(q1.value / q2.value);
}

/**
 * Sum of two quantities.
 */
template<class Unit, class Scalar>
Quantity<Unit, Scalar>
operator+(Quantity<Unit, Scalar> q1, Quantity<Unit, Scalar> q2)
{
    return Quantity<Unit, Scalar>(q1.value + q2.value);
}

/**
 * Difference between two quantities.
 */
template<class Unit, class Scalar>
Quantity<Unit, Scalar>
operator-(Quantity<Unit, Scalar> q1, Quantity<Unit, Scalar> q2)
{
    return Quantity<Unit, Scalar>(q1.value - q2.value);
}

/**
 * Negation of a quantity.
 */
template<class Unit, class Scalar>
Quantity<Unit, Scalar> operator-(Quantity<Unit, Scalar> q)
{
    return Quantity<Unit, Scalar>(-q.value);
}

#endif
