#ifndef UNIT_HPP
#define UNIT_HPP

#include <ostream>

/**
 * Template for constructing a base unit in terms of a unit trait
 * class and an integral exponent.
 */
template<class UT, int Exp>
struct BaseUnitTemplate
{
    static const int exponent = Exp;
    typedef UT UnitTrait;

    /**
     * Compute the name of the unit as the name of the unit trait
     * raised to the exponent.
     */
    static std::string name()
    {
        std::string s;
        if (exponent)
        {
            s += UnitTrait::symbol;
            if (exponent != 1)
            {
                s.push_back('^');
                s += std::to_string(exponent);
            }
        }
        return s;
    }
};

template<class BaseUnit1, class BaseUnit2>
struct BaseUnitProduct
{
    typedef BaseUnitTemplate<typename BaseUnit1::UnitTrait, BaseUnit1::exponent + BaseUnit2::exponent> type;
};

template<class BaseUnit1, class BaseUnit2>
using BaseUnitProductT = typename BaseUnitProduct<BaseUnit1, BaseUnit2>::type;

template<class BaseUnit1, class BaseUnit2>
struct BaseUnitDivision
{
    typedef BaseUnitTemplate<typename BaseUnit1::UnitTrait, BaseUnit1::exponent - BaseUnit2::exponent> type;
};

template<class BaseUnit1, class BaseUnit2>
using BaseUnitDivisionT = typename BaseUnitDivision<BaseUnit1, BaseUnit2>::type;

/**
 * Trait class for the meter unit.
 */
struct MeterTrait
{
    static constexpr const char *symbol = "m";
};

template<int Exp>
struct MeterUnitTemplate : public BaseUnitTemplate<MeterTrait, Exp>
{
    using BaseUnitTemplate<MeterTrait, Exp>::exponent;
};

/**
 * Trait class for the kilogram unit.
 */
struct KilogramTrait
{
    static constexpr const char *symbol = "kg";
};

template<int Exp>
struct KilogramUnitTemplate : public BaseUnitTemplate<KilogramTrait, Exp>
{
    using BaseUnitTemplate<KilogramTrait, Exp>::exponent;
};

/**
 * Trait class for the second unit.
 */
struct SecondTrait
{
    static constexpr const char *symbol = "s";
};

template<int Exp>
struct SecondUnitTemplate : public BaseUnitTemplate<SecondTrait, Exp>
{
    using BaseUnitTemplate<SecondTrait, Exp>::exponent;
};

/**
 * Trait class for the ampere unit.
 */
struct AmpereTrait
{
    static constexpr const char *symbol = "A";
};

template<int Exp>
struct AmpereUnitTemplate : public BaseUnitTemplate<AmpereTrait, Exp>
{
    using BaseUnitTemplate<AmpereTrait, Exp>::exponent;
};

/**
 * Representation of physical unit as the combination of four
 * base units from the MKSA system.
 */
template<class MU, class KU, class SU, class AU>
struct Unit
{
    typedef MU MeterUnit;
    typedef KU KilogramUnit;
    typedef SU SecondUnit;
    typedef AU AmpereUnit;

    /**
     * Compute the name of the physical unit as the concatenation of
     * the names of the individual base units.
     */
    static std::string name()
    {
        std::string n;
        n += MU::name();
        if (!n.empty() && n.back() != ' ') n += " ";
        n += KU::name();
        if (!n.empty() && n.back() != ' ') n += " ";
        n += SU::name();
        if (!n.empty() && n.back() != ' ') n += " ";
        n += AU::name();
        return n;
    }

    /**
     * Send a physical unit to an output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, Unit const &u)
    {
        os << name();
        return os;
    }
};

/**
 * Meter unit.
 */
typedef Unit<MeterUnitTemplate<1>,
             KilogramUnitTemplate<0>,
             SecondUnitTemplate<0>,
             AmpereUnitTemplate<0>> Meter;

/**
 * Kilogram unit.
 */
typedef Unit<MeterUnitTemplate<0>,
             KilogramUnitTemplate<1>,
             SecondUnitTemplate<0>,
             AmpereUnitTemplate<0>> Kilogram;

/**
 * Second unit.
 */
typedef Unit<MeterUnitTemplate<0>,
             KilogramUnitTemplate<0>,
             SecondUnitTemplate<1>,
             AmpereUnitTemplate<0>> Second;

/**
 * Ampere unit.
 */
typedef Unit<MeterUnitTemplate<0>,
             KilogramUnitTemplate<0>,
             SecondUnitTemplate<0>,
             AmpereUnitTemplate<1>> Ampere;

/**
 * Metafunction for product type of physical units.
 */
template<class Unit1, class Unit2>
struct ProductUnit
{
    typedef Unit<
        BaseUnitProductT<typename Unit1::MeterUnit,    typename Unit2::MeterUnit>,
        BaseUnitProductT<typename Unit1::KilogramUnit, typename Unit2::KilogramUnit>,
        BaseUnitProductT<typename Unit1::SecondUnit,   typename Unit2::SecondUnit>,
        BaseUnitProductT<typename Unit1::AmpereUnit,   typename Unit2::AmpereUnit>>
        type;
};

/**
 * Shorthand for the product type of physical units.
 */
template<class Unit1, class Unit2>
using ProductUnitT = typename ProductUnit<Unit1, Unit2>::type;

/**
 * Metafunction for division type of physical units.
 */
template<class Unit1, class Unit2>
struct DivisionUnit
{
    typedef Unit<
        BaseUnitDivisionT<typename Unit1::MeterUnit,    typename Unit2::MeterUnit>,
        BaseUnitDivisionT<typename Unit1::KilogramUnit, typename Unit2::KilogramUnit>,
        BaseUnitDivisionT<typename Unit1::SecondUnit,   typename Unit2::SecondUnit>,
        BaseUnitDivisionT<typename Unit1::AmpereUnit,   typename Unit2::AmpereUnit>>
        type;
};

/**
 * Shorthand for division type of physical units.
 */
template<class Unit1, class Unit2>
using DivisionUnitT = typename DivisionUnit<Unit1, Unit2>::type;

#endif
