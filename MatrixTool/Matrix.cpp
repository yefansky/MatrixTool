#include "Matrix.h"

template<typename T>
std::string Matrix<T>::ToString()
{
	std::string result;

	for (int i = 0; i < m_nRow; i++)
	{
		result += "|";
		for (int j = 0; j < m_nCol; j++)
		{
			if (j > 0)
				result += ",\t";
			result += Value(i, j).ToString();
		}
		result += "\t|\n";
	}

	return result;
}
