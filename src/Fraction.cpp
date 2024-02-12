//
// Created by Amy Fetzner on 2/10/2024.
//

#include "Farey/Fraction.h"
#include <numeric>

namespace Farey {

    Fraction::Fraction(int numerator, int denominator)
            : numerator(numerator), denominator(denominator) {
        int gcd;
        // Reduce by GCD
        if ((gcd = std::gcd(numerator, denominator)) != 1) {
            numerator /= gcd;
            denominator /= gcd;
        }
        // If denominator negative, negate both
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    Fraction Fraction::approximate(double real, unsigned int order) {
        if (real < 0 || real > 1)
            throw std::invalid_argument("approximate only used for real numbers in [0, 1]");
        if (order == 0)
            throw std::invalid_argument("approximate requires order >= 1");

        // Edge cases
        if (real == 0)
            return Fraction{0, 1};
        if (real == 1)
            return Fraction{1, 1};

        Fraction lowerBound = Fraction{0, 1};
        Fraction upperBound = Fraction{1, 1};
        Fraction approximation;
        double epsilon = 1. / (order * (order + 1));

        do {
            Fraction mediant_ = mediant(lowerBound, upperBound);
            if (mediant_.denominator > order)
                break;
            approximation = mediant_;
            if (approximation.toDouble() < real){
                lowerBound = approximation;
            } else {
                upperBound = approximation;
            }
        } while (std::abs(approximation.toDouble() - real) >= epsilon);

        double upperErr = upperBound.toDouble() - real;
        double lowerErr = real - lowerBound.toDouble();
        return (upperErr < lowerErr) ? upperBound : lowerBound;
    }

    float Fraction::toFloat() const {
        return (float) numerator / (float) denominator;
    }

    double Fraction::toDouble() const {
        return (double) numerator / (double) denominator;
    }

    // COMPARISON
    std::strong_ordering operator<=>(const Fraction &f1, const Fraction &f2) {
        long long product1 = f1.numerator * f2.denominator;
        long long product2 = f2.numerator * f1.denominator;
        return product1 <=> product2;
    }

    bool operator==(const Fraction &f1, const Fraction &f2) {
        long long product1 = f1.numerator * f2.denominator;
        long long product2 = f2.numerator * f1.denominator;
        return product1 == product2;
    }

    // ADDITION
    Fraction& Fraction::operator+=(const Fraction rhs) {
        int lcm = denominator;
        if (denominator != rhs.denominator) {
            lcm = std::lcm(denominator, rhs.denominator);
        }
        numerator = (numerator * (lcm / denominator)) + (rhs.numerator * (lcm / rhs.denominator));
        denominator = lcm;
        return *this;
    }

    Fraction& Fraction::operator+=(const int rhs) {
        return *this += Fraction (rhs);
    }

    Fraction operator+(const Fraction lhs, const Fraction rhs) {
        Fraction result = lhs;
        return result += rhs;
    }

    Fraction operator+(const int lhs, const Fraction rhs) {
        Fraction result = Fraction{lhs};
        return result += rhs;
    }

    Fraction operator+(const Fraction lhs, const int rhs) {
        Fraction result = Fraction{rhs};
        return result += lhs;
    }

    //SUBTRACTION
    Fraction& Fraction::operator-=(const Fraction rhs) {
        *this += Fraction{-rhs.numerator, rhs.denominator};
        return *this;
    }

    Fraction& Fraction::operator-=(const int rhs) {
        return *this -= Fraction (rhs);
    }

    Fraction operator-(const Fraction lhs, const Fraction rhs) {
        Fraction result = lhs;
        return result -= rhs;
    }

    Fraction operator-(const int lhs, const Fraction rhs) {
        Fraction result = Fraction{lhs};
        return result -= rhs;
    }

    Fraction operator-(const Fraction lhs, const int rhs) {
        Fraction result = lhs;
        return result -= Fraction{rhs};
    }

    // MULTIPLICATION
    Fraction& Fraction::operator*=(const Fraction rhs) {
        long long num = static_cast<long long>(numerator) * rhs.numerator;
        long long denom = static_cast<long long>(denominator) * rhs.denominator;
        long long gcd = std::gcd(num, denom);
        numerator = static_cast<int>((num / gcd));
        denominator = static_cast<int>((denom / gcd));
        return *this;

    }

    Fraction& Fraction::operator*=(const int rhs) {
        return *this *= Fraction (rhs);
    }

    Fraction operator*(const Fraction lhs, const Fraction rhs) {
        Fraction result = lhs;
        return result *= rhs;
    }

    Fraction operator*(const int lhs, const Fraction rhs) {
        Fraction result = Fraction{lhs};
        return result *= rhs;
    }

    Fraction operator*(const Fraction lhs, const int rhs) {
        Fraction result = Fraction{rhs};
        return result *= lhs;
    }

    // DIVISION
    Fraction& Fraction::operator/=(const Fraction rhs) {
        *this *= Fraction{rhs.denominator, rhs.numerator};
        return *this;
    }

    Fraction& Fraction::operator/=(const int rhs) {
        return *this /= Fraction (rhs);
    }

    Fraction operator/(const Fraction lhs, const Fraction rhs) {
        Fraction result = lhs;
        return result /= rhs;
    }

    Fraction operator/(const int lhs, const Fraction rhs) {
        Fraction result = Fraction{lhs};
        return result /= rhs;
    }

    Fraction operator/(const Fraction lhs, const int rhs) {
        Fraction result = lhs;
        return result /= Fraction{rhs};
    }

    Fraction& Fraction::mediantEquals(const Fraction frac) {
        // Intermittently use a larger int in case sum overflows, but after reduction, it does not
        long long num = numerator + frac.numerator;
        long long denom = denominator + frac.denominator;
        long long gcd = std::gcd(num, denom);
        numerator = static_cast<int>(num / gcd);
        denominator = static_cast<int>(denom / gcd);
        return *this;
    }
    
    // NEGATION
    Fraction operator-(const Fraction fraction) {
        return Fraction{-fraction.numerator, fraction.denominator};
    }
    
    // MEDIANT
    Fraction mediant(Fraction lhs, Fraction rhs) {
        Fraction result = lhs;
        return result.mediantEquals(rhs);
    }
}

