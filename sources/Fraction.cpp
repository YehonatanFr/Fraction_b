#include "Fraction.hpp"
#include <iostream>
#include <cmath>
#include <sstream>
#include <climits>
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

    Fraction::Fraction() : numerator_(0), denominator_(1) {

    }

    Fraction::Fraction(const Fraction& other){
        this->denominator_ = other.getDenominator();
        this->numerator_ = other.getNumerator();
    }

    Fraction::Fraction(float value) {
        int denom = 1;
        float temp = floor(value * 1000) / 1000;
        while (temp - floor(temp) > 0.001 && denom <= 1000) {
            temp *= 10;
            denom *= 10;
        }
        int nume = static_cast<int>(temp);
        this->numerator_ = nume;
        this->denominator_ = denom;
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

        if(denominator_ < 0 && numerator_ <0){
            numerator_ = abs(numerator_);
            denominator_ = abs(denominator_);
        }

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

    void Fraction::CheckNum(Fraction other){
        if(other.getDenominator()>=INT_MAX||other.getDenominator()<=INT_MIN||other.getNumerator()>=INT_MAX||other.getNumerator()<=INT_MIN)
            throw overflow_error("Fraction result is too large to be represented as an integer");
    }

    float Fraction::fraction_to_float(const Fraction& other) const {
        float tempFloat =  static_cast<float>(this->numerator_) / this->denominator_;
        float float_num = round(tempFloat * 1000) / 1000;
        return float_num;
    }

    //Operators implemention

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

    bool Fraction::operator<=(const Fraction& other) const {
        return (this->operator<(other) || this->operator==(other));
    }

    bool Fraction::operator!= (const Fraction& other) const {
        return !(this->operator==(other));
    }


    // Friend functions for Fraction and float operations
    // Addition
    Fraction operator+(const float float_num, const Fraction& other) {
        Fraction temp = Fraction(float_num);
        return temp + other;
    }

    Fraction operator+(const Fraction& other, const float float_num) {
        Fraction temp = Fraction(float_num);
        return temp + other;
    }

    // Subtraction
    Fraction operator-(const Fraction& other, const float float_num) {
        Fraction temp = Fraction(float_num);
        return other - temp;
    }

    Fraction operator-(const float float_num, const Fraction& other) {
        Fraction temp = Fraction(float_num);
        return temp - other;
    }

    // Multiplication
    Fraction operator*(const Fraction& other, const float float_num) {
        Fraction temp = Fraction(float_num);
        return Fraction(other.getNumerator() * temp.getNumerator(), other.getDenominator() * temp.getDenominator());
    }

    Fraction operator*(const float float_num, const Fraction& other) {
        Fraction temp = Fraction(float_num);
        return Fraction(temp.getNumerator() * other.getNumerator() , temp.getDenominator() * other.getDenominator());
    }

    // Division
    Fraction operator/(const Fraction& other, const float float_num) {
        Fraction temp = Fraction(float_num);
        return Fraction(other.getNumerator() * temp.getDenominator(), other.getDenominator() * temp.getNumerator());
    }

    Fraction operator/(const float float_num, const Fraction& other) {
        Fraction temp = Fraction(float_num);
        return Fraction(temp.getNumerator() * other.getDenominator() , temp.getDenominator() * other.getNumerator()); 
    }


    // Comparison operations
    bool operator==(const Fraction& other, float float_num){
        Fraction temp = Fraction(float_num);
        return other == temp;
    }

    bool operator==(float float_num, const Fraction& other){
        Fraction temp = Fraction(float_num);
        return other == temp;
    }

    bool operator>(const Fraction& other, const float &float_num) {
        Fraction temp = Fraction(float_num);
        return other > temp;
    }

    bool operator>(const float &float_num, const Fraction& other) {
        Fraction temp = Fraction(float_num);
        return temp > other;
    }

    bool operator<(const Fraction& other, const float &float_num) {
        Fraction temp = Fraction(float_num);;
        return other < temp;
    }

    bool operator<(const float &float_num, const Fraction& other) {
        Fraction temp = Fraction(float_num);
        return temp < other;
    }

    bool operator>=(const Fraction& other, const float &float_num) {
        Fraction temp = Fraction(float_num);
        return  other >= temp;
    }

    bool operator>=(const float &float_num, const Fraction& other) {
       Fraction temp = Fraction(float_num);
        return temp >= other;
    }

    bool operator<=(const Fraction& other, const float &float_num) {
        Fraction temp = Fraction(float_num);
        return other <= temp;
    }

    bool operator<=(const float &float_num, const Fraction& other) {
        Fraction temp = Fraction(float_num);
        return temp <= other;
    }


    ostream& operator<<(ostream& os, const Fraction& other)
    {
        return os << other.getNumerator() << '/' << other.getDenominator();
    }

    // istream& operator>>(istream& is, const Fraction& other)
    // {
    //     is >> other.getNumerator() >> other.getDenominator();
    //     if(!is)  throw runtime_error("error : invalid input");
    //     return is;
    // }
    
    istream& operator>>(istream& iso, Fraction& other){
        int num_ ,den_;

        iso >> num_ >> den_;

        if((iso.fail()) || (den_ == 0)){
            throw runtime_error("invalid input: 2 arguments needed: <numerator>  <denominator>\n");
        }
        else{
            other = Fraction(num_, den_);
        }
        return iso;
    }
}

