#include "FFT.h"

ComplexMatrix FFT::FourierTransformMatrix(int n)
{
	ComplexMatrix m(n);
	auto W = ComplexIndex(1, 2 * c_fPI / n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			m.Value(i, j) = W.Pow(i * j);
		}
	return m;
}

ComplexMatrix FFT::FFTMatrix(int n)
{
	if (n == 2)
		return FourierTransformMatrix(2);
	int d = n / 2;
	const auto F = FFTMatrix(d);
	const auto W = ComplexIndex(1, 2 * c_fPI / n);
	const auto I = ComplexMatrix::Identity(d);
	const auto D = FFT::DiagonalW(d, W);
	const auto Zero = ComplexMatrix::Zero(d);
	const auto P = FFT::ParityPermutationMatrix(n);

	return PartitionedMatrix<Complex>::Build(
		I, D,
		I, -D
	) * PartitionedMatrix<Complex>::Build(
		F, Zero,
		Zero, F
	) * P;
}

ComplexMatrix FFT::FFTMatrix2(int n)
{	
	auto F = FourierTransformMatrix(2);
	for (int i = 4; i <= n; i *= 2)
	{
		int d = i / 2;
		const auto W = ComplexIndex(1, 2 * c_fPI / i);
		const auto I = ComplexMatrix::Identity(d);
		const auto D = FFT::DiagonalW(d, W);
		const auto Zero = ComplexMatrix::Zero(d);
		const auto P = FFT::ParityPermutationMatrix(i);

		F = PartitionedMatrix<Complex>::Build(
			I, D,
			I, -D
		) * PartitionedMatrix<Complex>::Build(
			F, Zero,
			Zero, F
		) * P;
	}
	return F;
}

ComplexMatrix FFT::ParityPermutationMatrix(int n)
{
	ComplexMatrix m(n);
	for (int i = 0; i < n / 2; i++)
	{
		m.Value(i, i * 2) = 1;
		m.Value(n / 2 + i, i * 2 + 1) = 1;
	}
	return m;
}

ComplexMatrix FFT::DiagonalW(int n, const ComplexIndex& w)
{
	ComplexMatrix m(n);
	for (int i = 0; i < n; i++)
		m.Value(i, i) = w.Pow(i);
	return m;
}