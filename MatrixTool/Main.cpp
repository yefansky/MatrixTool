#include <cstdio>
#include <iostream>
#include "Matrix.h"

int main()
{
	int n = 8;
	auto W = ComplexIndex(1, 2 * c_fPI / (2 * n));
	auto Matrix2n = PartitionedMatrix::Build(
		Matrix::I(n), Matrix::DiagonalW(n, W),
		Matrix::I(n), -Matrix::DiagonalW(n, W)
	) * PartitionedMatrix::Build(
		Matrix::F(n), Matrix(n),
		Matrix(n), Matrix::F(n)
	) * Matrix::P(2 * n);


	auto A = PartitionedMatrix::Build(
		Matrix::I(n), Matrix::DiagonalW(n, W),
		Matrix::I(n), -Matrix::DiagonalW(n, W)
	);
	auto B = PartitionedMatrix::Build(
		Matrix::F(n), Matrix(n),
		Matrix(n), Matrix::F(n)
	);
	auto P = Matrix::P(n * 2);

	std::cout << "F" << 2 * n << " = " << "\n" << Matrix::F(2 * n).ToString() << std::endl;
	std::cout << "Matrix2n = " << "\n" << Matrix2n.ToString() << std::endl;

	std::cout << "I = " << "\n" << Matrix::I(n).ToString() << std::endl;
	std::cout << "D = " << "\n" << Matrix::DiagonalW(n, W).ToString() << std::endl;
	std::cout << "F2 = " << "\n" << Matrix::F(2).ToString() << std::endl;

	std::cout << "A = " << "\n" << A.ToString() << std::endl;
	std::cout << "B = " << "\n" << B.ToString() << std::endl;
	std::cout << "P = " << "\n" << P.ToString() << std::endl;

	std::cout << "HA = " << "\n" << A.Hermite().ToString() << std::endl;
	std::cout << "A x B = " << "\n" << (A * B).ToString() << std::endl;

	return 0;
}