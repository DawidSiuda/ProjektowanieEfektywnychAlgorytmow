#include <iostream>
#include <nmmintrin.h>
#include <math.h>

#include "DynamicPrograming.h"

using namespace std;

unsigned setBit(unsigned vector, int possition);
unsigned resetBit(unsigned vector, int possition);
bool isSet(unsigned vector, int possition);
int getNumberOfOnes(unsigned vector);
int** createArray(int height);
int g(int vertex, unsigned bitVector, int** array, int width);


static int** lookupCosts = nullptr;
static int** lookupPath = nullptr;

int dynamicPrograming(int** array, int width, bool test)
{
	lookupPath = createArray(width);
	lookupCosts = createArray(width);

	unsigned vector = 0;

	for (int i = 1; i < width; i++) 
		vector = setBit(vector, i);

	int sum2 = g(0, vector, array, width);

	int* path = new int[width + 1];
	path[0] = 0;

	
	for (int i = 1; getNumberOfOnes(vector) > 0; i++)
	{
		int numberOfOnes = getNumberOfOnes(vector);
		int min = 0;
		for (int j = 0; j < width; j++)
		{
			if (lookupCosts[min][vector] > lookupCosts[j][vector])
				min = j;
		}

		path[i] = lookupPath[min][vector];
		vector = resetBit(vector, lookupPath[min][vector]);
	}
	path[width] = 0;

	int sum = 0;

	if (test == false)
	{
		cout << "Dynamic Programing:\n\t";

		for (int i = 0; i < width; i++)
		{
			cout << path[i] << " -> ";
			sum += array[path[i]][path[i + 1]];
		}
		cout << path[width];
		cout << endl;

		cout << "\tSum: " << sum << endl << endl;

		//cout << sum << ";"; // to del
	}
	else
	{
		for (int i = 0; i < width; i++)
		{
			sum += array[path[i]][path[i + 1]];
		}
	}

	return sum;
}

int g(int vertex, unsigned bitVector, int** array, int width) 
{
	if (lookupCosts[vertex][bitVector] != INT_MAX) 
		return lookupCosts[vertex][bitVector];

	if (isSet(bitVector, vertex)) 
		bitVector = resetBit(bitVector, vertex);

	if (getNumberOfOnes(bitVector) == 0)
	{
		if (vertex == 1)
			int a = 6;
		return array[vertex][0];
	}
	else
	{
		int min = INT_MAX;
		int minVertex = INT_MAX;

		for (int i = 0; i < width; i++) 
		{
			int tmp2 = isSet(bitVector, i);
			if (tmp2) 
			{
				int tmp = g(i, resetBit(bitVector, i), array, width);
				tmp += array[vertex][i];

				//cout << "======================================================================================================================================================" << endl;
				//std::cout << "printArray(): Dawid lookupPath.";
				//printArray(lookupPath);

				//std::cout << "\nprintArray(): Dawid lookupCosts.";
				//printArray(lookupCosts);

				if (tmp < min) 
				{
					min = tmp;
					minVertex = i;
				}
			}
		}
		lookupCosts[vertex][bitVector] = min;
		lookupPath[vertex][bitVector] = minVertex;
		return min;
	}
}

unsigned setBit(unsigned vector, int possition)
{
	return vector | 1 << possition;
}

unsigned resetBit(unsigned vector, int possition)
{
	return vector & ~(1 << possition);
}

bool isSet(unsigned vector, int possition)
{
	if ((vector & (1 << possition)) == 0)
		return false;
	else
		return true;
}

int getNumberOfOnes(unsigned vector) 
{
	return _mm_popcnt_u32(vector);
}

int **createArray(int height) 
{
	int rowsNumber = pow(2, height) +1;
	int** array    = new int* [height];

	for (int i = 0; i < height; i++)
	{
		array[i] = new int[rowsNumber];

		for (int j = 0; j < rowsNumber; j++)
		{
			array[i][j] = INT_MAX;
		}

	}

	return array;
} 