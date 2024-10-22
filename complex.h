#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <ostream>

class Complex {
public:
    Complex(double real = 0, double imag = 0);

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(double scalar) const;
    double abs() const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& complex);

private:
    double real;
    double imag;
};

#endif // COMPLEX_H
