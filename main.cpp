#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <chrono> 
#include <conio.h>

#include "BrutalForce.h"
#include "DynamicPrograming.h"

using namespace std;
using namespace std::chrono;

int readGrapgFromFile(std::string path, int**& array, int& width);
void printArray(int** array, int width);
void emptyArray(int**& array, int width);

int main()
{
	int** array = nullptr;
	int width;
	int returnValue;
	int option;

	do
	{
		cout << "========================================\n" 
			<< "MENU\n"
			<< "1) Wczytaj graf \"graf.txt\"\n"
			<< "2) Wyswietl graf\n"
			<< "3) Brute-Force\n"
			<< "4) Programowanie dynamiczne\n"
			<< "0) Wyjscie\n";

		option = _getch();

		
		system("cls");

		switch (option)
		{
			case '0':
			{
				if (array != nullptr)
					emptyArray(array, width);
				exit(0);
				break;
			}
			case '1':
			{
				if (array != nullptr)
					emptyArray(array, width);

				//string defaultName("graf.txt");
				string defaultName("tsp_10b.txt");
				
				cout << "File name (" << defaultName <<"): ";

				std::string input;
				std::getline(std::cin, input);

				if (input.empty()) 
				{
					input = defaultName;
				}

				returnValue = readGrapgFromFile(input, array, width);

				if (returnValue == -1)
				{
					cout << "ERROR: Cannot read graph.\n";
				}

				break;
			}
			case '2':
			{
				if (array != nullptr)
					printArray(array, width);
				else
					cout << "ERROR: No load graph.\n";
				break;
			}
			case '3':
			{
				if (array != nullptr)
				{
					auto start = high_resolution_clock::now();
					brutalForce(array, width);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "Time: " << duration.count() << " microseconds" << endl;
				}
				else
					cout << "ERROR: No load graph.\n";
				break;
			}
			case '4':
			{
				if (array != nullptr)
				{
					auto start = high_resolution_clock::now();
					dynamicPrograming(array, width);
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<microseconds>(stop - start);
					cout << "Time: " << duration.count() << " microseconds" << endl;
				}
				else
					cout << "ERROR: No load graph.\n";
				break;
			}
		}
	} while (1);
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

	int isFirstLine = true;

	file >> width;

	std::cout << "Number of cities: " << width << "\n";

	array = new int* [width];

	for (int i = 0; i < width; ++i)
	{
		array[i] = new int[width];

		memset(array[i], 0, width * sizeof(int));
	}

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

void emptyArray(int**& array, int width)
{
	for (int i = 0; i < width; ++i)
	{
		delete[] array[i];
	}

	delete[] array;

	array = nullptr;
}