
#ifndef UNIT_HPP
#define UNIT_HPP

template<class UT, int Exp>
struct BaseUnitTemplate
{
    static const int exponent = Exp;
    typedef UT UnitTrait;
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

struct MeterTrait
{
    static constexpr const char *symbol = "m";
};

template<int Exp>
struct MeterUnitTemplate : public BaseUnitTemplate<MeterTrait, Exp>
{
    using BaseUnitTemplate<MeterTrait, Exp>::exponent;
};

struct KilogramTrait
{
    static constexpr const char *symbol = "kg";
};

template<int Exp>
struct KilogramUnitTemplate : public BaseUnitTemplate<KilogramTrait, Exp>
{
    using BaseUnitTemplate<KilogramTrait, Exp>::exponent;
};

struct SecondTrait
{
    static constexpr const char *symbol = "s";
};

template<int Exp>
struct SecondUnitTemplate : public BaseUnitTemplate<SecondTrait, Exp>
{
    using BaseUnitTemplate<SecondTrait, Exp>::exponent;
};

struct AmpereTrait
{
    static constexpr const char *symbol = "A";
};

template<int Exp>
struct AmpereUnitTemplate : public BaseUnitTemplate<AmpereTrait, Exp>
{
    using BaseUnitTemplate<AmpereTrait, Exp>::exponent;
};

template<class MU, class KU, class SU, class AU>
struct Unit
{
    typedef MU MeterUnit;
    typedef KU KilogramUnit;
    typedef SU SecondUnit;
    typedef AU AmpereUnit;

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

    friend std::ostream &operator<<(std::ostream &os, Unit const &u)
    {
        os << name();
        return os;
    }
};

typedef Unit<MeterUnitTemplate<1>,
             KilogramUnitTemplate<0>,
             SecondUnitTemplate<0>,
             AmpereUnitTemplate<0>> Meter;

typedef Unit<MeterUnitTemplate<0>,
             KilogramUnitTemplate<1>,
             SecondUnitTemplate<0>,
             AmpereUnitTemplate<0>> Kilogram;

typedef Unit<MeterUnitTemplate<0>,
             KilogramUnitTemplate<0>,
             SecondUnitTemplate<1>,
             AmpereUnitTemplate<0>> Second;

typedef Unit<MeterUnitTemplate<0>,
             KilogramUnitTemplate<0>,
             SecondUnitTemplate<0>,
             AmpereUnitTemplate<1>> Ampere;

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

template<class Unit1, class Unit2>
using ProductUnitT = typename ProductUnit<Unit1, Unit2>::type;

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

template<class Unit1, class Unit2>
using DivisionUnitT = typename DivisionUnit<Unit1, Unit2>::type;

#endif
