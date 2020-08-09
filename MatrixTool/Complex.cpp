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

Complex::Complex(const ComplexIndex& rIndex) : m_fA(rIndex.m_fR* cos(rIndex.m_fTheta)), m_fB(rIndex.m_fR* sin(rIndex.m_fTheta)) {}

Complex& Complex::operator = (double fR)
{
	return *this = Complex(fR);
}

Complex Complex::operator + (const Complex& c)
{
	return Complex(m_fA + c.m_fA, m_fB + c.m_fB);
}

Complex& Complex::operator += (const Complex& c)
{
	m_fA += c.m_fA;
	m_fB += c.m_fB;
	return *this;
}

Complex Complex::operator * (const Complex& c)
{
	return Complex(m_fA * c.m_fA - m_fB * c.m_fB, m_fB * c.m_fA + m_fA * c.m_fB);
}

bool Complex::operator == (const Complex& c) const
{
	return Near(m_fA, c.m_fA) && Near(m_fB, c.m_fB);
}

bool Complex::operator != (const Complex& c) const
{
	return !(*this == c);
}

Complex Complex::Conjugation() const
{
	return Complex(m_fA, -m_fB);
}

Complex Complex::Pow(double fN) const
{
	return ComplexIndex(*this).Pow(fN);
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
	return Complex(-c.m_fA, -c.m_fB);
}

ComplexIndex ComplexIndex::Pow(double fN) const
{
	return ComplexIndex(pow(m_fR, fN), m_fTheta * fN);
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

bool ComplexIndex::operator == (const ComplexIndex& c) const
{
	return Near(m_fR, c.m_fR) && Near(m_fTheta, c.m_fTheta);
}

bool ComplexIndex::operator != (const ComplexIndex& c) const
{
	return !(*this == c);
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