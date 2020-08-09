#pragma once
#include <assert.h>
#include "Complex.h"

template<typename Element>
class Matrix
{
public:
	int m_nRow = 0;
	int m_nCol = 0;
	
private:	
	Element* m_pcData = nullptr;

public:
	Matrix() {}

	Matrix(int nR, int nC) : m_nRow(nR), m_nCol(nC) 
	{
		assert(m_nRow > 0);
		assert(m_nCol > 0);
		m_pcData = new Element[m_nRow * m_nCol];
		assert(m_pcData);
	}

	Matrix(int n) : Matrix(n, n) {}

	Matrix(const Matrix& m) : m_nRow(m.m_nRow), m_nCol(m.m_nCol)
	{
		if (m_pcData)
			delete[] m_pcData;

		m_pcData = new Element[m_nRow * m_nCol];

		if (m_pcData)
			for (int i = 0; i < m_nRow; i++)
				for (int j = 0; j < m_nCol; j++)
					Value(i, j) = m.Value(i, j);
	}

	Matrix(Matrix&& m) : m_nRow(m.m_nRow), m_nCol(m.m_nCol)
	{
		if (m_pcData)
			delete[] m_pcData;

		m_pcData = m.m_pcData;
		m.m_pcData = nullptr;
	}

	~Matrix()
	{
		if (m_pcData)
		{
			delete[] m_pcData;
			m_pcData = nullptr;
		}
		m_nRow = m_nCol = 0;
	}

	Matrix& operator =(Matrix&& m)
	{
		if (m_pcData)
			delete[] m_pcData;
		m_pcData = nullptr;
		m_nRow = m.m_nRow;
		m_nCol = m.m_nCol;
		m_pcData = new Element[m_nRow * m_nCol];
	
		if (m_pcData)
			for (int i = 0; i < m_nRow; i++)
				for (int j = 0; j < m_nCol; j++)
					Value(i, j) = m.Value(i, j);
		return *this;
	}

	Element& Value(int i, int j)
	{
		assert(i >= 0 && i < m_nRow);
		assert(j >= 0 && j < m_nCol);
		assert(m_pcData);
		return m_pcData[i * m_nCol + j];
	}

	const Element& Value(int i, int j) const
	{
		assert(i >= 0 && i < m_nRow);
		assert(j >= 0 && j < m_nCol);
		assert(m_pcData);
		return m_pcData[i * m_nCol + j];
	}

	Matrix operator * (const Matrix& rM)
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
	bool operator == (const Matrix& rM) const
	{
		for (int i = 0; i < m_nRow; i++)
			for (int j = 0; j < m_nCol; j++)
				if (Value(i, j) != rM.Value(i, j))
					return false;
		return true;
	}

	Matrix Transpose() const
	{
		Matrix m = *this;

		for (int i = 0; i < m_nRow; i++)
			for (int j = 0; j < m_nCol && j < i; j++)
				std::swap(m.Value(i, j), m.Value(j, i));
		return m;
	}

	Matrix Conjugation() const
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

	Matrix Hermite() const
	{
		return Conjugation().Transpose();
	}

	std::string ToString();

	static Matrix Identity(int n)
	{
		Matrix m(n);
		for (int i = 0; i < n; i++)
			m.Value(i, i) = 1;
		return m;
	}

	static Matrix Zero(int n)
	{
		return Matrix(n);
	}
};

template<typename T>
Matrix<T> operator - (const Matrix<T>& m)
{
	Matrix<T> result = m;
	for (int i = 0; i < result.m_nRow; i++)
		for (int j = 0; j < result.m_nCol; j++)
			result.Value(i, j) = -result.Value(i, j);
	return result;
}

template<typename Element>
class PartitionedMatrix
{
	typedef Matrix<Element> _Matrix;
private:
	static void CopySubMatrix(_Matrix& father, const _Matrix& son, int nStartRow, int nStartCol)
	{
		assert(nStartRow >= 0);
		assert(nStartCol >= 0);
		assert(nStartRow + son.m_nRow <= father.m_nRow);
		assert(nStartCol + son.m_nCol <= father.m_nCol);

		for (int i = 0; i < son.m_nRow; i++)
			for (int j = 0; j < son.m_nCol; j++)
				father.Value(nStartRow + i, nStartCol + j) = son.Value(i, j);
	}

public:	
	static _Matrix Build(const _Matrix& A, const _Matrix& B, const _Matrix& C, const _Matrix& D)
	{
		assert(A.m_nRow == B.m_nRow);
		assert(C.m_nRow == D.m_nRow);
		assert(A.m_nCol == C.m_nCol);
		assert(B.m_nCol == D.m_nCol);

		_Matrix result(A.m_nRow + C.m_nRow, A.m_nCol + B.m_nCol);

		CopySubMatrix(result, A, 0, 0);
		CopySubMatrix(result, B, 0, A.m_nCol);
		CopySubMatrix(result, C, A.m_nRow, 0);
		CopySubMatrix(result, D, A.m_nRow, C.m_nCol);

		return result;
	}
};
