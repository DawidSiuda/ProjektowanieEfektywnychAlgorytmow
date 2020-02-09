#include <iostream>
#include "BrutalForce.h"

using namespace std;

static int currentMin = -1;
static int* finalPath = nullptr;
static int finalCost = INT_MAX;

void swap(int& a, int& b);
void calculatePath(int* a, int n, int** array);
void heapPermutation(int* a, int size, int n, int** array);
int brutalForce(int** array, int width);

void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void calculatePath(int* a, int n, int** array)
{
	int sum = 0;

	sum += array[0][a[0]];

	for (int i = 0; i < n - 1; i++)
	{
		sum += array[a[i]][a[i + 1]];
	}

	sum += array[a[n - 1]][0];

	if (currentMin == -1 || currentMin > sum)
	{
		currentMin = sum;

		//
		// Save path.
		//

		finalPath[0] = 0;
		finalPath[n+1] = 0;

		for (int i = 0; i < n; i++)
			finalPath[i+1] = a[i];

		finalPath[n + 1] = 0;

		finalCost = currentMin;
	}
}

// Generating permutation using Heap Algorithm 
void heapPermutation(int *a, int size, int n, int **array)
{
	// if size becomes 1 then prints the obtained 
	// permutation 
	if (size == 1)
	{
		calculatePath(a, n, array);
		return;
	}

	for (int i = 0; i < size; i++)
	{
		heapPermutation(a, size - 1, n, array);

		// if size is odd, swap first and last 
		// element 
		if (size % 2 == 1)
			swap(a[0], a[size - 1]);

		// If size is even, swap ith and last 
		// element 
		else
			swap(a[i], a[size - 1]);
	}
}

int brutalForce(int** array, int width)
{
	finalPath = new int[width+1];

	int* path = new int[width-1];

	for (int i = 0; i < width-1; i++)
	{
		path[i] = i+1;
	}

	heapPermutation(path, width - 1, width - 1, array);

	//
	// Print path;
	//

	cout << "Brute-Force:\n\t";

	for (int i = 0; i < width; i++)
	{
		cout << finalPath[i] << " -> ";
	}
	cout << finalPath[width];
	cout << endl;

	cout << "\tSum: " << finalCost << endl << endl;
	//cout << finalCost << "; ";


	//
	// Clear vars;
	//

	delete[] finalPath;
	delete[] path;

	currentMin = -1;
	finalPath = nullptr;
	finalCost = INT_MAX;

	return 0;
}