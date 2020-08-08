#include "Matrix.h"

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

Matrix Matrix::F(int n)
{
	Matrix m(n);
	ComplexIndex w = W(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			m.Value(i, j) = w.Pow(i * j).ToComplex();
		}
	return m;
}

Matrix Matrix::P(int n)
{
	Matrix m(n);
	for (int i = 0; i < n / 2; i++)
	{
		m.Value(i, i * 2) = 1;
		m.Value(n / 2 + i, i * 2 + 1) = 1;
	}
	return m;
}

Matrix Matrix::D(int n)
{
	Matrix m(n);
	ComplexIndex w = W(n);
	for (int i = 0; i < n; i++)
		m.Value(i, i) = w.Pow(i).ToComplex();
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