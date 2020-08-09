#include <cstdio>
#include <iostream>
#include "FFT.h"

int main()
{
	for (int n = 2; n <= 16; n *= 2)
	{
		auto FTM = FFT::FourierTransformMatrix(n);
		auto FFTM = FFT::FFTMatrix(n);

		std::cout << "FTM" << n << " = " << "\n" << FTM.ToString() << std::endl;
		std::cout << "FFTM" << n << " = " << "\n" << FFTM.ToString() << std::endl;
	}
	return 0;
}