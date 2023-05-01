#include "Fraction.hpp"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>


// using namespace ariel;
using namespace std;

namespace ariel
{
    Fraction::~Fraction(){

    }
    
    //Constructor
    Fraction::Fraction(int num, int den) {
        if (den == 0)
            throw invalid_argument("Denominator can't be zero.");
        this->numerator_ = num;
        this->denominator_ = den;
        reduce();
    }

    //Getters & Setters
    int Fraction::getNumerator() const
    {
        return this->numerator_;
    }

    int Fraction::getDenominator() const
    {
        return this->denominator_;
    }

    void Fraction::setNumerator(int numerator) 
    {
        this->numerator_ = numerator;
    }

    void Fraction::setDenominator(int denominator)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Denominator can't be zero.");
        }
        this->denominator_ = denominator;
    }

    //Helpers
    void Fraction::reduce() {
        int tempGcd = gcd(abs(numerator_), abs(denominator_));
        numerator_ /= tempGcd;
        denominator_ /= tempGcd;
        if (denominator_ < 0) {
            numerator_ *= -1;
            denominator_ *= -1;
        }
    }

    int Fraction::gcd(int a, int b) const{
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    int Fraction::lcm(int a, int b) const{
        return abs(a * b) / gcd(a, b);
    }

    void Fraction::simplify() {
        int gcd_val = gcd(numerator_, denominator_);
        numerator_ /= gcd_val;
        denominator_ /= gcd_val;
    }

    //Operators implemention

    Fraction& Fraction::operator=(const Fraction &other){
        if (this != &other)
        {
            numerator_ = other.numerator_;
            denominator_ = other.denominator_;
        }
        return *this;
    }
    Fraction Fraction::operator+(const Fraction& other) const{
        int tempLcm = lcm(denominator_, other.denominator_);
        int numerator = numerator_ * (tempLcm / denominator_) + other.numerator_ * (tempLcm / other.denominator_);
        return Fraction(numerator, tempLcm);

    }
    Fraction Fraction::operator-(const Fraction& other) const{
        int tempLcm = lcm(denominator_, other.denominator_);
        int numerator = numerator_ * (tempLcm / denominator_) - other.numerator_ * (tempLcm / other.denominator_);
        return Fraction(numerator, tempLcm);
    }
    Fraction Fraction::operator*(const Fraction& other) const{
        int numerator = numerator_ * other.numerator_;
        int denominator = denominator_ * other.denominator_;
        return Fraction(numerator, denominator);
    }
    Fraction Fraction::operator/(const Fraction& other) const{
        int numerator = numerator_ * other.denominator_;
        int denominator = denominator_ * other.numerator_;
        return Fraction(numerator, denominator);
    }


    Fraction Fraction::operator++(int){
        Fraction temp(*this);
        numerator_ += denominator_;
        reduce();
        return temp;

    } 
    Fraction& Fraction::operator++(){
        numerator_ += denominator_;
        reduce();
        return *this;

    }   
    Fraction Fraction::operator--(int){
        Fraction temp(*this);
        numerator_ -= denominator_;
        reduce();
        return temp;

    } 
    Fraction& Fraction::operator--(){
        numerator_ -= denominator_;
        reduce();
        return *this;

    }


    bool Fraction::operator==(const Fraction& other) const {
        Fraction a = *this;
        Fraction b = other;
        a.reduce();
        b.reduce();
        return (a.numerator_ == b.numerator_ && a.denominator_ == b.denominator_);
    }

    bool Fraction::operator>(const Fraction& other) const {
        int lcm_ = lcm(denominator_, other.denominator_);
        int a = (lcm_ / denominator_) * numerator_;
        int b = (lcm_ / other.denominator_) * other.numerator_;
        return (a > b);
    }

    bool Fraction::operator<(const Fraction& other) const {
        return !(this->operator>(other)) && !(this->operator==(other));
    }

    bool Fraction::operator>=(const Fraction& other) const {
        return (this->operator>(other) || this->operator==(other));
    }

    bool Fraction::operator<=(Fraction& other) const {
        return (this->operator<(other) || this->operator==(other));
    }

    bool Fraction::operator!= (Fraction& other) const {
        return !(this->operator==(other));
    }


    // Friend functions for Fraction and float operations
    // Addition
    Fraction operator+(float float_num, const Fraction& other) {
        return Fraction(3,4);
    }

    Fraction operator+(const Fraction& other, float float_num) {
        return float_num + other;
    }

    // Subtraction
    Fraction operator-(const Fraction& other, float float_num) {
        return other + (-float_num);
    }

    Fraction operator-(float float_num, const Fraction& other) {
        return Fraction(3,4);
    }

    // Multiplication
    Fraction operator*(const Fraction& other, float float_num) {
        Fraction f(float_num, 1);
        return Fraction(other.getNumerator() * f.getNumerator(), other.getDenominator() * f.getDenominator());
    }

    Fraction operator*(float float_num, const Fraction& other) {
        return other * float_num;
    }

    // Division
    Fraction operator/(const Fraction& other, float float_num) {
        return Fraction(3,4);
    }

    Fraction operator/(float float_num, const Fraction& other) {
        return Fraction(3,4);
    }


    // Comparison operations
    bool operator>(const Fraction& other, float float_num) {
        float tempFloat = (float)other.getNumerator() / other.getDenominator();
        return tempFloat > float_num;
    }

    bool operator>(float float_num, const Fraction& other) {
        float tempFloat = (float)other.getNumerator() / other.getDenominator();
        return float_num > tempFloat;
    }

    bool operator<(const Fraction& other, float float_num) {
        float tempFloat = (float)other.getNumerator() / other.getDenominator();
        return tempFloat < float_num;
    }

    bool operator<(float float_num, const Fraction& other) {
        float tempFloat = (float)other.getNumerator() / other.getDenominator();
        return float_num < tempFloat;
    }

    bool operator>=(const Fraction& other, float float_num) {
        float tempFloat = (float)other.getNumerator() / other.getDenominator();
        return tempFloat >= float_num;
    }

    bool operator>=(float float_num, const Fraction& other) {
        float tempFloat = (float)other.getNumerator() / other.getDenominator();
        return float_num >= tempFloat;
    }

    bool operator<=(const Fraction& other, float float_num) {
        float tempFloat = (float)other.getNumerator() / other.getDenominator();
        return tempFloat <= float_num;
    }

    bool operator<=(float float_num, const Fraction& other) {
        float tempFloat = (float)other.getNumerator() / other.getDenominator();
        return float_num <= tempFloat;
    }


    ostream& operator<<(std::ostream& os, const Fraction& f)
    {
        return os;
    }

    istream& operator>>(std::istream& is, Fraction& f)
    {
        return is;
    }
}

