#include "Complex.h"
#include <cmath>

bool Near(double f, int n)
{
	return fabs((double)n - f) < 1e-10;
}

bool Near(double f, double f2)
{
	return fabs(f - f2) < 1e-10;
}

bool NearZero(double f)
{
	return Near(f, 0);
}

Complex Complex::operator = (double fR)
{
	return *this = Complex(fR);
}

Complex Complex::operator + (const Complex& c)
{
	return Complex(m_fA + c.m_fA, m_fB + c.m_fB);
}

Complex Complex::operator += (const Complex& c)
{
	return (*this = *this + c);
}

Complex Complex::operator * (const Complex& c)
{
	return Complex(m_fA * c.m_fA - m_fB * c.m_fB, m_fB * c.m_fA + m_fA * c.m_fB);
}

Complex Complex::Conjugation() const
{
	return Complex(m_fA, -m_fB);
}

ComplexIndex Complex::ToIndex() const
{
	double fR = sqrt(m_fA * m_fA + m_fB * m_fB);
	double fA = atan2(m_fB, m_fA);
	return ComplexIndex(fR, fA);
}

Complex Complex::Pow(double fN) const
{
	auto Index = ToIndex();
	Index.Pow(fN);
	return Index.ToComplex();
}

std::string Complex::ToString() const
{
	std::string result;

	if (!NearZero(m_fA))
	{
		if (Near(fabs(m_fA), 1))
			result += std::to_string((int)m_fA);
		else
			result += std::to_string(m_fA);
	}

	if (!NearZero(m_fB))
	{
		if (Near(m_fB, -1))
			result += "-";
		else if (!result.empty() && m_fB > 0)
			result += " + ";

		if (!Near(fabs(m_fB), 1))
			result += std::to_string(m_fB);

		result += "i";
	}

	if (result.empty())
		result = "0";

	return result;
}

Complex operator -(const Complex& c)
{
	Complex result = c;
	result.m_fA = -result.m_fA;
	result.m_fB = -result.m_fB;
	return result;
}

ComplexIndex ComplexIndex::Pow(double fN) const
{
	double fR = pow(m_fR, fN);
	double fAngle = m_fTheta * fN;
	return ComplexIndex(fR, fAngle);
}

Complex ComplexIndex::ToComplex() const
{
	return Complex(m_fR * cos(m_fTheta), m_fR * sin(m_fTheta));
}

std::string ComplexIndex::ToString() const
{
	std::string result;
	if (fabs(m_fR) == 0)
		result = "0";

	if (Near(m_fR, 1))
	{
		if (m_fR < 0)
			result = "-";
	}
	else
	{
		result = std::to_string(m_fR);
	}

	double fA = fmod(m_fTheta, (2 * c_fPI));
	if (NearZero(fA) || NearZero(fabs(fA) - 2 * c_fPI))
	{
		// e
	}
	else
	{
		result += "e^i" + std::to_string(fA);
	}

	return result;
}

ComplexIndex operator -(const ComplexIndex& rIndex)
{
	ComplexIndex result = rIndex;
	result.m_fR = -result.m_fR;
	return result;
}

ComplexIndex W(int n)
{
	return ComplexIndex(1.0f, 2 * c_fPI / n);
}