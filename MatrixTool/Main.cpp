#include <cstdio>
#include <iostream>
#include "FFT.h"

int main()
{
	for (int n = 2; n <= 1024; n *= 2)
	{
		std::cout << "FFT Matrix test" << n << "\t...\t...\t" << std::endl;
		std::cout << "\tcalculate FTM ..." << std::endl;
		auto FTM = FFT::FourierTransformMatrix(n);
		std::cout << "\tcalculate FFTM ..." << std::endl;
		auto FFTM = FFT::FFTMatrix(n);
		std::cout << "\t... compare ...";
		std::cout << ((FTM == FFTM) ? "Pass" : "Fail!") << std::endl;
	}
	return 0;
}