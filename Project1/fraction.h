#include <numeric>  // for std::gcd()
#include <stdexcept> //for std::invalid_argument
#include <iostream>

class fraction {
private:
    double _numerator;
    double _denominator;
public:
    //fraction 初始化
    fraction(int n = 0, int d = 1) {
        if (d == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        double gcd_val = std::gcd(n, d); //find the greatest common divisor
        //save them and simplify
        _numerator = n / gcd_val;
        _denominator = d / gcd_val;
    }

    fraction(double n, double d) {
        if (d == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        //remove the decimal point by multiplying numerator & denomiantor multiple times by 10. E.g. 2.3 --> 23
        while (fmod(n, 1) != 0 || fmod(d, 1) != 0) {
            n *= 10;
            d *= 10;
        }

        double gcd_val = (double)std::gcd(int(n), int(d)); //find the greatest common divisor

        _numerator = n / gcd_val;
        _denominator = d / gcd_val;
    }

    fraction(double num) {
        //remove the decimal point. E.g. 2.3 --> 23
        int denominator = 1;//save the number that we multiplied, it is also the denominator
        while (fmod(num, 1) != 0 || fmod(num, 1) != 0) {
            num *= 10;
            denominator *= 10;
        }
        int gcd_val = std::gcd(int(num), denominator); //find the greatest common divisor

        _numerator = num / gcd_val;
        _denominator = denominator / gcd_val;
    }

    //拷贝构造
    fraction& operator=(const fraction& other) {
        this->_denominator = other._denominator;
        this->_numerator = other._numerator;

        return *this;
    }

    //输入分子，分母，并简化
    friend std::istream& operator>>(std::istream& is, fraction& f) {
        double num, den;
        is >> num >> den;
        f = fraction(num, den);
        return is;
    }

    //输出分子，分母
    friend std::ostream& operator<<(std::ostream& os, const fraction& f) {
        os << f._numerator << "/" << f._denominator;
        return os;
    }

    //加
    fraction operator+(const fraction& other) const {
        int num = this->_numerator * other._denominator + other._numerator * this->_denominator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //fraction + double  
    fraction operator+(const double n) const {
        fraction other(n);
        int num = this->_numerator * other._denominator + other._numerator * this->_denominator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //double + fraction 
    friend fraction operator+(const double n, const fraction& f) {
        return f + n;
    }

    //fraction + int
    fraction operator+(const int n) const {
        fraction other(n);
        int num = this->_numerator * other._denominator + other._numerator * this->_denominator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //int + fraction 
    friend fraction operator+(const int n, const fraction& f) {
        return f + n;
    }


    //减
    fraction operator-(const fraction& other) const {
        int num = this->_numerator * other._denominator - other._numerator * this->_denominator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //fraction - double  
    fraction operator-(const double n) const {
        fraction other(n);
        int num = this->_numerator * other._denominator - other._numerator * this->_denominator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //double - fraction 
    friend fraction operator-(const double n, const fraction& f) {
        return f - n;
    }

    //fraction - int  
    fraction operator-(const int n) const {
        fraction other(n);
        int num = this->_numerator * other._denominator - other._numerator * this->_denominator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //int - fraction 
    friend fraction operator-(const int n, const fraction& f) {
        return f - n;
    }

    //乘
    fraction operator*(const fraction& other) const {
        int num = this->_numerator * other._numerator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //fraction * double  
    fraction operator*(const double n) const {
        fraction other(n);
        int num = this->_numerator * other._numerator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //double * fraction 
    friend fraction operator*(const double n, const fraction& f) {
        return f * n;
    }


    //fraction * int  
    fraction operator*(const int n) const {
        fraction other(n);
        int num = this->_numerator * other._numerator;
        int den = this->_denominator * other._denominator;
        return fraction(num, den);
    }

    //int * fraction 
    friend fraction operator*(const int n, const fraction& f) {
        return f * n;
    }

    //除
    fraction operator/(const fraction& other) const {
        int num = this->_numerator * other._denominator;
        int den = this->_denominator * other._numerator;
        return fraction(num, den);
    }

    //fraction / double  
    fraction operator/(const double n) const {
        fraction other(n);
        int num = this->_numerator * other._denominator;
        int den = this->_denominator * other._numerator;
        return fraction(num, den);
    }

    //double / fraction 
    friend fraction operator/(const double n, const fraction& f) {
        return f / n;
    }

    //fraction / int  
    fraction operator/(const int n) const {
        fraction other(n);
        int num = this->_numerator * other._denominator;
        int den = this->_denominator * other._numerator;
        return fraction(num, den);
    }

    //int / fraction 
    friend fraction operator/(const int n, const fraction& f) {
        return f / n;
    }

    //把fraction转换成double
    operator double() const {
        return static_cast<double>(_numerator) / static_cast<double>(_denominator);
    }
};
