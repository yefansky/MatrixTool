#pragma once
#include <string>

class ComplexIndex;
const double cf_PI = 3.14159265358979323846264338327950288419716939937510582097944592307816406286208998;

class Complex
{
public:
	double m_fA = 0;
	double m_fB = 0;

public:
	Complex() {}
	Complex(double fA) : m_fA(fA), m_fB(0) {}
	Complex(double fA, double fB) : m_fA(fA), m_fB(fB) {}

	Complex operator = (double fR);
	Complex operator + (const Complex& c);
	Complex operator += (const Complex& c);
	Complex operator * (const Complex& c);

	ComplexIndex ToIndex();
	Complex Pow(double fN);
	std::string ToString();
};

Complex operator -(const Complex& c);

class ComplexIndex
{
public:
	double m_fR = 0;
	double m_fTheta = 0;

	ComplexIndex(double fR, double fTheta) : m_fR(fR), m_fTheta(fTheta) {}

	ComplexIndex Pow(double fN);
	Complex ToComplex();
	std::string ToString();
};


ComplexIndex operator -(const ComplexIndex & rIndex);

bool Near(double f, int n);
bool Near(double f, double f2);
bool NearZero(double f);

ComplexIndex W(int n);