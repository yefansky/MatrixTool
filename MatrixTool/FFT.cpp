#include "FFT.h"

Matrix FFT::FourierTransformMatrix(int n)
{
	Matrix m(n);
	auto W = ComplexIndex(1, 2 * c_fPI / n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			m.Value(i, j) = W.Pow(i * j);
		}
	return m;
}

Matrix FFT::FFTMatrix(int n)
{
	if (n == 2)
		return FourierTransformMatrix(2);
	int d = n / 2;
	const auto F = FourierTransformMatrix(d);
	const auto W = ComplexIndex(1, 2 * c_fPI / n);
	const auto I = Matrix::I(d);
	const auto D = FFT::DiagonalW(d, W);
	const auto Zero = Matrix(d);
	const auto P = FFT::ParityPermutationMatrix(n);

	return PartitionedMatrix::Build(
		I, D,
		I, -D
	) * PartitionedMatrix::Build(
		F, Zero,
		Zero, F
	) * P;
}

Matrix FFT::ParityPermutationMatrix(int n)
{
	Matrix m(n);
	for (int i = 0; i < n / 2; i++)
	{
		m.Value(i, i * 2) = 1;
		m.Value(n / 2 + i, i * 2 + 1) = 1;
	}
	return m;
}

Matrix FFT::DiagonalW(int n, const ComplexIndex& w)
{
	Matrix m(n);
	for (int i = 0; i < n; i++)
		m.Value(i, i) = w.Pow(i);
	return m;
}