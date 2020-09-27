
#ifndef UNIT_HPP
#define UNIT_HPP

template<class UnitTrait, int Exp>
struct BaseUnitTemplate
{
    static const int exponent = Exp;
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

template<class M, class K, class S, class A>
struct Unit
{
    static const int meter = M::exponent;
    static const int kilogram = K::exponent;
    static const int second = S::exponent;
    static const int ampere = A::exponent;

    static std::string name()
    {
        std::string n;
        n += M::name();
        if (!n.empty() && n.back() != ' ') n += " ";
        n += K::name();
        if (!n.empty() && n.back() != ' ') n += " ";
        n += S::name();
        if (!n.empty() && n.back() != ' ') n += " ";
        n += A::name();
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
        MeterUnitTemplate<Unit1::meter + Unit2::meter>,
        KilogramUnitTemplate<Unit1::kilogram + Unit2::kilogram>,
        SecondUnitTemplate<Unit1::second + Unit2::second>,
        AmpereUnitTemplate<Unit1::ampere + Unit2::ampere>>
        type;
};

template<class Unit1, class Unit2>
using ProductUnitT = typename ProductUnit<Unit1, Unit2>::type;

#endif
