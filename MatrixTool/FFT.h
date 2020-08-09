#pragma once

#include "Matrix.h"
#include "Complex.h"

typedef Matrix<Complex> ComplexMatrix;

class FFT
{
public:
	static ComplexMatrix FourierTransformMatrix(int n);
	static ComplexMatrix FFTMatrix(int n);
	static ComplexMatrix FFTMatrix2(int n);
private:
	static ComplexMatrix ParityPermutationMatrix(int n);
	static ComplexMatrix DiagonalW(int n, const ComplexIndex& w);
};

