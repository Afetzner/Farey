//
// Created by Amy Fetzner on 2/10/2024.
//

#ifndef FAREY_FRACTION_H
#define FAREY_FRACTION_H

#include <compare>
#include "iostream"

namespace Farey {

    struct Fraction {
        int numerator;
        int denominator;

        explicit Fraction(int numerator = 0, int denominator = 1);

        static Fraction approximate(double real, unsigned int order);

        [[nodiscard]]
        float toFloat() const;

        [[nodiscard]]
        double toDouble() const;

        friend std::strong_ordering operator<=>(const Fraction& f1, const Fraction& f2);
        friend bool operator==(const Fraction& f1, const Fraction& f2);

        Fraction& operator+=(Fraction rhs);
        Fraction& operator+=(int rhs);
        friend Fraction operator+(Fraction lhs, Fraction rhs);
        friend Fraction operator+(int lhs, Fraction rhs);
        friend Fraction operator+(Fraction lhs, int rhs);

        Fraction& operator-=(Fraction rhs);
        Fraction& operator-=(int rhs);
        friend Fraction operator-(Fraction lhs, Fraction rhs);
        friend Fraction operator-(int lhs, Fraction rhs);
        friend Fraction operator-(Fraction lhs, int rhs);

        Fraction& operator*=(Fraction rhs);
        Fraction& operator*=(int rhs);
        friend Fraction operator*(Fraction lhs, Fraction rhs);
        friend Fraction operator*(int lhs, Fraction rhs);
        friend Fraction operator*(Fraction lhs, int rhs);

        Fraction& operator/=(Fraction rhs);
        Fraction& operator/=(int rhs);
        friend Fraction operator/(Fraction lhs, Fraction rhs);
        friend Fraction operator/(int lhs, Fraction rhs);
        friend Fraction operator/(Fraction lhs, int rhs);

        friend Fraction operator-(Fraction fraction);

        Fraction& mediantEquals(Fraction frac);
        friend Fraction mediant(Fraction lhs, Fraction rhs);

        friend std::ostream& operator<<(std::ostream& os, Fraction const f) {
            return os << f.numerator << '/' << f.denominator;
        }
    };
}


#endif //FAREY_FRACTION_H
