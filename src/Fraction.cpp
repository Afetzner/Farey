//
// Created by Amy Fetzner on 2/10/2024.
//

#include "include/Fraction.h"
#include <numeric>

using namespace Farey;

Fraction::Fraction(int numerator, int denominator)
: numerator(numerator)
, denominator(denominator) {
    int gcd;
    // Reduce by GCD
    if ((gcd = std::gcd(numerator, denominator)) != 1) {
        numerator /= gcd;
        denominator /= gcd;
    }
    // If denominator negative, negate both
    if (denominator < 0){
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction::Fraction()
: numerator(0)
, denominator(1)
{}

Fraction approximate(double real, unsigned int order){
    // TODO
    return {0, 0};
}

float Fraction::toFloat() const {
    return (float)numerator / (float)denominator;
}

double Fraction::toDouble() const {
    return (double)numerator / (double)denominator;
}

void Fraction::reduce() {
    int gcd = std::gcd(numerator, denominator);
    if (gcd != 1){
        numerator /= gcd;
        denominator /= gcd;
    }
}

Fraction Fraction::reduced() const {
    return Farey::Fraction {numerator, denominator};
}

// ADDITION
Fraction& Fraction::operator+=(const Farey::Fraction rhs) {
    int lcm = denominator;
    if (denominator != rhs.denominator) {
        lcm = std::lcm(denominator, rhs.denominator);
    }
    numerator = (numerator * (lcm / denominator)) + (rhs.numerator * (lcm / rhs.denominator));
    denominator = lcm;
    // because the lcm is used, the fraction need not be reduced after addition. I think?
    // reduce();
    return *this;
}

Fraction operator+(const Fraction lhs, const Fraction rhs){
    Fraction result = lhs;
    return result += rhs;
}

//SUBTRACTION
Fraction& Fraction::operator-=(const Farey::Fraction rhs) {
    *this += Fraction{-rhs.numerator, rhs.denominator};
    return *this;
}

Fraction operator-(const Fraction lhs, const Fraction rhs){
    Fraction result = lhs;
    return result -= rhs;
}

// MULTIPLICATION
Fraction& Fraction::operator*=(const Farey::Fraction rhs) {
    int gcd1 = std::gcd(numerator, rhs.denominator);
    int gcd2 = std::gcd(denominator, rhs.numerator);
    // Dividing by the GCDs first means
    // 1) The fraction need not be reduced after multiplication
    // 2) Fractions where the result does not overflow, but the intermediate product does
    //    can still be multiplied without overflow.
    numerator *= (rhs.numerator / gcd2);
    denominator *= (rhs.denominator / gcd1);
    return *this;
}

Fraction operator*(const Fraction lhs, const Fraction rhs){
    Fraction result = lhs;
    return result *= rhs;
}

// DIVISION
Fraction& Fraction::operator/=(const Farey::Fraction rhs) {
    *this *= Fraction{rhs.denominator, rhs.numerator};
    return *this;
}

Fraction operator/(const Fraction lhs, const Fraction rhs){
    Fraction result = lhs;
    return result /= rhs;
}

Fraction& Fraction::mediantEquals(const Farey::Fraction frac) {
    // Intermittently use a larger int in case sum overflows, but after reduction, it does not
    long long num = numerator + frac.numerator;
    long long denom = denominator + frac.denominator;
    long long gcd = std::gcd(num, denom);
    numerator = static_cast<int>(num / gcd);
    denominator = static_cast<int>(denom / gcd);
    return *this;
}

Fraction Farey::mediant(Fraction lhs, Fraction rhs) {
    Fraction result = lhs;
    return result.mediantEquals(rhs);
}


