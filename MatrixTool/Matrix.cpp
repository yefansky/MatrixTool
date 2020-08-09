#include "Matrix.h"
#include <typeindex>

Matrix Matrix::operator * (const Matrix& rM)
{
	Matrix result(m_nRow, rM.m_nCol);

	assert(m_nCol == rM.m_nRow);

	for (int i = 0; i < m_nRow; i++)
		for (int j = 0; j < rM.m_nCol; j++)
			for (int k = 0; k < m_nCol; k++)
			{
				result.Value(i, j) += Value(i, k) * rM.Value(k, j);
			}

	return result;
}

Matrix Matrix::Transpose() const
{
	Matrix m = *this;
	
	for (int i = 0; i < m_nRow; i++)
		for (int j = 0; j < m_nCol && j < i; j++)
			std::swap(m.Value(i,j), m.Value(j, i));
	return m;
}

Matrix Matrix::Conjugation() const
{
	Matrix m = *this;

	for (int i = 0; i < m_nRow; i++)
		for (int j = 0; j < m_nCol && j < i; j++)
		{
			auto& rValue = m.Value(i, j);
			rValue = rValue.Conjugation();
		}
	return m;
}

Matrix Matrix::Hermite() const
{
	return Conjugation().Transpose();
}

std::string Matrix::ToString()
{
	std::string result;

	for (int i = 0; i < m_nRow; i++)
	{
		result += "|";
		for (int j = 0; j < m_nCol; j++)
		{
			if (j > 0)
				result += ",\t";
			result += Value(i, j).ToString();
		}
		result += "\t|\n";
	}

	return result;
}

Matrix Matrix::I(int n)
{
	Matrix m(n);
	for (int i = 0; i < n; i++)
		m.Value(i, i) = 1;
	return m;
}

Matrix operator - (const Matrix& m)
{
	Matrix result = m;
	for (int i = 0; i < result.m_nRow; i++)
		for (int j = 0; j < result.m_nCol; j++)
			result.Value(i, j) = -result.Value(i, j);
	return result;
}