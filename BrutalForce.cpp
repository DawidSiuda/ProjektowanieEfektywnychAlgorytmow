#include "BrutalForce.h"

using namespace std;

void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

//Prints the array 
void printArr(int *a, int n, int value, int **array)
{
	cout << " 0 -> " << a[0] << "   : " << array[0][a[0]] << endl;

	for (int i = 0; i < n-1 ; i++)
	{
		cout << " -> " << a[i+1] << "   : " << array[a[i]][a[i + 1]] << endl;
	}

	cout << " -> 0: " << "   : " << array[a[n - 1]][0] << endl;
	cout << "sum: " << value << "\n";
}

void calculatePath(int* a, int n, int** array)
{
	static int currentMin = -1;

	int sum = 0;

	sum += array[0][a[0]];

	for (int i = 0; i < n - 1; i++)
	{
		//if (array[a[i]][a[i + 1]] == 0)
		//{
		//	return;
		//}

		sum += array[a[i]][a[i + 1]];
	}

	sum += array[a[n - 1]][0];

	if (currentMin == -1 || currentMin > sum)
	{
		currentMin = sum;

		printArr(a, n, currentMin, array);
	}

	//cout << "sum: " << sum << endl;
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

// Driver code 
int brutalForce(int** array, int width)
{
	int* path = new int[width-1];

	for (int i = 0; i < width-1; i++)
	{
		path[i] = i+1;
	}

	heapPermutation(path, width - 1, width - 1, array);

	return 0;
}