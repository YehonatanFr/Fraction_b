#ifndef Fraction_HPP
#define Fraction_HPP

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>


namespace ariel
{
    class Fraction
    {
        int numerator_;
        int denominator_;
        void simplify();


    public:
        //Constructor
        Fraction();
        Fraction(float);
        Fraction(int, int);
        Fraction(const Fraction& other);
        
        //destructor
        ~Fraction();
        
        //Helpers
        void reduce();
        int gcd(int num1, int num2) const;
        int lcm(int num1, int num2) const;
        void CheckNum(long num1, long num);
        float fraction_to_float() const;
        float float_to_fraction() const;

        //Getters & Setters
        int getNumerator() const;
        int getDenominator() const;
        void setNumerator(int numerator);
        void setDenominator(int denominator); 

        //Basic operators
        Fraction& operator=(const Fraction &other);
        Fraction operator+(const Fraction& other) const;
        Fraction operator-(const Fraction& other) const;
        Fraction operator*(const Fraction& other) const;
        Fraction operator/(const Fraction& other) const;

        Fraction operator++(int); // post-increment
        Fraction& operator++();   // pre-increment
        Fraction operator--(int); // post-decrement
        Fraction& operator--();  // pre-decrement

        //Bool operations
        bool operator==(const Fraction& other) const;
        bool operator>(const Fraction& other) const;
        bool operator<(const Fraction& other) const;
        bool operator>=(const Fraction& other) const;
        bool operator<=(Fraction& other) const;
        bool operator!= (Fraction& other) const;

        //Other operations
        friend std::ostream& operator<<(std::ostream& os_, const Fraction& other);
        friend std::istream& operator>>(std::istream& is_, Fraction& other);

        //Functions with friend implemention for float
        friend Fraction operator+ (float float_num, const Fraction& other);
        friend Fraction operator+ (const Fraction& other, float float_num);
        
        friend Fraction operator* (float float_num, const Fraction& other);
        friend Fraction operator* (const Fraction& other, float float_num);
        
        friend Fraction operator/ (float float_num, const Fraction& other);
        friend Fraction operator/ (const Fraction& other, float float_num);
        
        friend Fraction operator- (const Fraction& other, float float_num);
        friend Fraction operator- (float float_num, const Fraction& other);
        
        friend bool operator> (float float_num, const Fraction& other);
        friend bool operator> (const Fraction& other, float float_num);
        
        friend bool operator< (float float_num, const Fraction& other);
        friend bool operator< (const Fraction& other, float float_num);
        
        friend bool operator>= (float float_num, const Fraction& other);
        friend bool operator>= (const Fraction& other, float float_num);
        
        friend bool operator<= (float float_num, const Fraction& other);
        friend bool operator<= (const Fraction& other, float float_num);

    };
}

#endif