#pragma once

#include "Matrix.h"

class FFT
{
public:
	static Matrix FourierTransformMatrix(int n);
	static Matrix FFTMatrix(int n);
private:
	static Matrix ParityPermutationMatrix(int n);
	static Matrix DiagonalW(int n, const ComplexIndex& w);
};

