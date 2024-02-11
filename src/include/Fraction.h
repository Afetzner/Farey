//
// Created by Amy Fetzner on 2/10/2024.
//

#ifndef FAREY_FRACTION_H
#define FAREY_FRACTION_H

namespace Farey {

    struct Fraction {
        int numerator;
        int denominator;

        Fraction(int numerator, int denominator);
        Fraction();

        friend Fraction approximate(double real, unsigned int order);

        [[nodiscard]]
        float toFloat() const;

        [[nodiscard]]
        double toDouble() const;

        inline void reduce();

        [[nodiscard]]
        Fraction reduced() const;

        Fraction& operator+=(Fraction rhs);
        friend Fraction operator+(Fraction lhs, Fraction rhs);

        Fraction& operator-=(Fraction rhs);
        friend Fraction operator-(Fraction lhs, Fraction rhs);

        Fraction& operator*=(Fraction rhs);
        friend Fraction operator*(Fraction lhs, Fraction rhs);

        Fraction& operator/=(Fraction rhs);
        friend Fraction operator/(Fraction lhs, Fraction rhs);

        Fraction& mediantEquals(Fraction frac);
        friend Fraction mediant(Fraction lhs, Fraction rhs);

    };
}


#endif //FAREY_FRACTION_H
