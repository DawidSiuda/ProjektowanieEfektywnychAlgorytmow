#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "BrutalForce.h"

int readGrapgFromFile(std::string path, int**& array, int& width);
void printArray(int** array, int width);

int main()
{
	int** array = nullptr;
	int width;

	readGrapgFromFile("br6.atsp", array, width);

	printArray(array, width);

	brutalForce(array, width);

}

int readGrapgFromFile(std::string path, int**& array, int& width)
{

	array = nullptr;
	width = -1;

	std::string line;
	std::string temp;

	std::fstream file;

	file.open(path, std::ios::in);

	if (file.good() == false)
	{
		std::cout << "Cannot read file.\n";

		return -1;
	}


	while (getline(file, line))
	{
		//
		// search for dimension
		//

		if (line.find("DIMENSION:") != std::string::npos)
		{
			std::cout << "Found DIMENSION parameter in file.\n";

			temp = line.substr(11, 5);

			width = atoi(temp.c_str());


			std::cout << "Number of cities: " << width << "\n";

			array = new int* [width];

			for (int i = 0; i < width; ++i)
			{
				array[i] = new int[width];

				memset(array[i], 0, width * sizeof(int));
			}
		}

		//
		// Read value from file to graph.
		//

		if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos)
		{
			int row = 0;
			int collumn = 0;
			int value;

			while (file >> value)
			{
				array[row][collumn] = value;

				collumn++;

				if (collumn == width)
				{
					collumn = 0;
					row++;

					if (row == width)
					{
						break;
					}
				}

			}

		}
	}

	file.close();

	return 0;
}

void printArray(int** array, int width)
{

	if (array == nullptr)
	{
		std::cout << "printArray(): ERROR: array is nulptr.";

		return;
	}

	std::cout << "printArray(): TABLE:\n";

	for (int i = 0; i < width; i++)
	{
		std::string line;

		for (int j = 0; j < width; j++)
		{
			std::cout.width(5);

			std::cout << array[i][j];
		}

		std::cout << std::endl;

	}
}