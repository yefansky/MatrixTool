#pragma once
#include <assert.h>
#include "Complex.h"

class Matrix
{
public:
	int m_nRow = 0;
	int m_nCol = 0;
	
private:	
	Complex* m_pcData = nullptr;

public:
	Matrix(int nR, int nC) : m_nRow(nR), m_nCol(nC) 
	{
		assert(m_nRow > 0);
		assert(m_nCol > 0);
		m_pcData = new Complex[m_nRow * m_nCol];
		assert(m_pcData);
	}

	Matrix(int n) : Matrix(n, n) {}

	Matrix(const Matrix& m)
	{
		m_nRow = m.m_nRow;
		m_nCol = m.m_nCol;

		m_pcData = new Complex[m_nRow * m_nCol];
		for (int i = 0; i < m_nRow; i++)
			for (int j = 0; j < m_nCol; j++)
				Value(i, j) = m.Value(i, j);
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

	Complex& Value(int i, int j)
	{
		assert(i >= 0 && i < m_nRow);
		assert(j >= 0 && j < m_nCol);
		assert(m_pcData);
		return m_pcData[i * m_nCol + j];
	}

	const Complex& Value(int i, int j) const
	{
		assert(i >= 0 && i < m_nRow);
		assert(j >= 0 && j < m_nCol);
		assert(m_pcData);
		return m_pcData[i * m_nCol + j];
	}

	Matrix operator * (const Matrix& rM);

	std::string ToString();

	static Matrix I(int n);
	static Matrix F(int n);
	static Matrix P(int n);
	static Matrix D(int n);
};

Matrix operator - (const Matrix& m);

class PartitionedMatrix
{
private:
	static void CopySubMatrix(Matrix& father, const Matrix& son, int nStartRow, int nStartCol)
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
	static Matrix Build(const Matrix&& A, const Matrix&& B, const Matrix&& C, const Matrix&& D)
	{
		assert(A.m_nRow == B.m_nRow);
		assert(C.m_nRow == D.m_nRow);
		assert(A.m_nCol == C.m_nCol);
		assert(B.m_nCol == D.m_nCol);

		Matrix result(A.m_nRow + C.m_nRow, A.m_nCol + B.m_nCol);

		CopySubMatrix(result, A, 0, 0);
		CopySubMatrix(result, B, 0, A.m_nCol);
		CopySubMatrix(result, C, A.m_nRow, 0);
		CopySubMatrix(result, D, A.m_nRow, C.m_nCol);

		return result;
	}
};
