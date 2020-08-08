#include <cstdio>
#include <iostream>
#include "Matrix.h"

int main()
{
	std::cout << "F4 = " <<"\n" << Matrix::F(4).ToString() << std::endl;
	auto Matrix2n = PartitionedMatrix::Build(
		Matrix::I(2), Matrix::D(2),
		Matrix::I(2), -Matrix::D(2)
	) * PartitionedMatrix::Build(
		Matrix::F(2), Matrix(2),
		Matrix(2), Matrix::F(2)
	) * Matrix::P(4);
	std::cout << "Matrix2n = " << "\n" << Matrix2n.ToString() << std::endl;

	auto A = PartitionedMatrix::Build(
		Matrix::I(2), Matrix::D(2),
		Matrix::I(2), -Matrix::D(2)
	);
	auto B = PartitionedMatrix::Build(
		Matrix::F(2), Matrix(2),
		Matrix(2), Matrix::F(2)
	);
	auto P = Matrix::P(4);

	std::cout << "I = " << "\n" << Matrix::I(2).ToString() << std::endl;
	std::cout << "D = " << "\n" << Matrix::D(2).ToString() << std::endl;
	std::cout << "F2 = " << "\n" << Matrix::F(2).ToString() << std::endl;

	std::cout << "A = " << "\n" << A.ToString() << std::endl;
	std::cout << "B = " << "\n" << B.ToString() << std::endl;
	std::cout << "P = " << "\n" << P.ToString() << std::endl;

	std::cout << "A x B = " << "\n" << (A * B).ToString() << std::endl;

	return 0;
}