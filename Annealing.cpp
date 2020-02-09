#include <iostream>
#include <conio.h>
#include <string> //getline
#include <sstream> //stringstream geek

#include "Annealing.h"
#include "MyVector.h"

#include <time.h>       /* time */


int beginTemperature = 500;
double temperatureChangeFactor = 0.9999;
double worseAcceptableFactor = 30;

using namespace std;

int getParameters(int begTemper, double& temperChangeFac, double& worseAccepFac)
{
	string input;

	cout << "beginTemperature (" << beginTemperature << "): ";

	getline(cin, input);

	if (input.empty())
	{
		stringstream geek(input);
		geek >> begTemper;
	}

	cout << "temperatureChangeFactor (" << temperatureChangeFactor << "): ";

	getline(cin, input);

	if (input.empty())
	{
		stringstream geek(input);
		geek >> temperChangeFac;
	}

	cout << "worseAcceptableFactor (" << worseAcceptableFactor << "): ";

	getline(cin, input);

	if (input.empty())
	{
		stringstream geek(input);
		geek >> worseAccepFac;
	}

	return 0;
}

MyVector<int> randSolution(int vertexNumber, int** inputArray)
{
	int* tab_i = new int[vertexNumber];
	MyVector<int> res;

	for (int i = 0; i < vertexNumber; ++i)
	{
		tab_i[i] = i;
	}

	for (int i = 0; i < vertexNumber; ++i)
	{
		int x = rand() % vertexNumber;

		if (tab_i[x] == -1) 
		{
			--i;
			continue;
		}

		res.push_back(tab_i[x]);
		tab_i[x] = -1;
	}

	int a = res[0];
	res.push_back(a);
	delete[] tab_i;
	return res;
}

int calcCost(MyVector<int> solution, int vertexNumber, int** adjacencyMatrix)
{
	if (solution.size() <= 1)
		return -1;

	int cost = 0;

	for (int i = 0; i != vertexNumber; i++)
	{
		int a = solution[i];
		int b = solution[i + 1];
		cost += adjacencyMatrix[a][b];
	}

	return cost;
}

MyVector<int> getAdjacentSolution(MyVector<int> res)
{
	int x1 = rand() % (res.size() - 1);
	int x2 = rand() % (res.size() - 1);
	if (x1 == x2)
		x2 == res.size() - 2 ? --x2 : ++x2;

	int tmp = res[x1];
	res[x1] = res[x2];
	res[x2] = tmp;

	res[res.size() - 1] = res[0];
	return res;
}

int annealing(int** array, int vertexNumber, int test, double begTemperature, double tempChangeFactor, double worAccepFactor)
{
	srand(time(NULL));

	beginTemperature = begTemperature ? begTemperature : beginTemperature;
	temperatureChangeFactor = tempChangeFactor ? tempChangeFactor : temperatureChangeFactor;
	worseAcceptableFactor = worAccepFactor ? worAccepFactor : worseAcceptableFactor;

	//
	// Set parameters.
	//

	if (beginTemperature == 0 || temperatureChangeFactor == 0 || worseAcceptableFactor == 0 || test ==  false)
		getParameters(beginTemperature, temperatureChangeFactor, worseAcceptableFactor);

	//
	// Set variables.
	//

	int worseSolutionCounter = 0;
	int worseAcceptable = worseAcceptableFactor * vertexNumber;							// Akceptowalna liczba wyszukan gorszych rozwiazan pod rzad
	double temperature = beginTemperature;													// Przypisanie poczatkowej temperatury
	MyVector<int> currentSolution = randSolution(vertexNumber, array);							// Losowanie pierwszego rozwiazania i przypisanie go jako rozwiazanie obecne
	MyVector<int> bestSolution = currentSolution;												// Wylosowane rozwiazanie jest automatycznie najlepszym, poniewaz jest to jedyne rozwiazanie
	MyVector<int> adjacentSolution = currentSolution;											// Przypisanie obecnego rozwiazania jako sasiedniego celem wykonania operacji na nim
	int costCurrentSolution;																// Deklaracja zmiennych przechowujacych koszty rozwiazan
	int costBestSolution;
	int costAdjacentSolution;
	costCurrentSolution = calcCost(currentSolution, vertexNumber, array);					// Wyliczenie kosztu dla obecnego rozwiazania
	costBestSolution = costCurrentSolution;													// Wyliczenie kosztu dla najlepszego rozwiazania
	
	while (worseSolutionCounter < worseAcceptable) // Dopoki licznik gorszych rozwiazan pod rzad jest mniejszy od akceptowalnej
	{												// liczby tych rozwiazan

		adjacentSolution = getAdjacentSolution(currentSolution);	// Znalezienie rozwiazania sasiedniego
		costAdjacentSolution = calcCost(adjacentSolution, vertexNumber, array); // Wyliczenie kosztu dla znalezionego rozwiazania sasiedniego

		if (costAdjacentSolution < costBestSolution) // Jesli znalezione rozwiazanie jest tansze od najlepszego to wykonaj:
		{
			bestSolution = adjacentSolution; // Mianuj znalezione rozwiazanie na najlepsze
			costBestSolution = costAdjacentSolution; // Przypisz jego koszt jako najlepszy
		}

		if (costAdjacentSolution < costCurrentSolution) // Jesli znalezione rozwiazanie jest tansze od obecnego to wykonaj:
		{ 
			currentSolution = adjacentSolution;			// Mianuj znalezione rozwiazanie na obecne
			costCurrentSolution = costAdjacentSolution; // Przypisz jego koszt jako obecny
			worseSolutionCounter = 0;					// Wyzeruj licznik znalezionych gorszych rozwiazan pod rzad
		}
		else
		{
			++worseSolutionCounter;										// Inkrementuj licznik znalezionych gorszych rozwiazan pod rzad
			double delta = costAdjacentSolution - costCurrentSolution;	// Oblicz roznica kosztow (sasiednie rozw. - obecne rozw.)
			double x = (rand() % 100000) / 100000.0;            		// Wylosuj liczba z zakresu <0,1)

			if (x < (exp((-delta) / temperature)))    
			{	
				// Akceptujemy rozwiazanie z pewnym prawdopodobienstwem
				// wyliczonym za pomoca e^(-delta / temperature).
				// Warunek wykona sia z pewnym wyliczonym prawdopodobienstwem zaleznym od 
				// roznicy kosztow sciezki obecnie znalezionej i sciezki obecnej, oraz od temperatury.
				// Prawdopobienstwo zwiaksza sia im mniejsza badzie roznica kosztow i zmniejsza sia wraz z
				// obnizaniem temperatury (temperatura obniza sia stopniowo wraz z kazda iteracja).

				currentSolution = adjacentSolution;			// Mianuj znalezione rozwiazanie na obecne
				costCurrentSolution = costAdjacentSolution; // Przypisz jego koszt jako obecny
			}
		}
		temperature *= temperatureChangeFactor; // Zmniejszanie temperatury wg zadanego wspolczynnika
	}

	if (test == true)
	{
		//cout << vertexNumber << "; "
		//	<< beginTemperature << "; "
		//	<< temperatureChangeFactor << "; "
		//	<< worseAcceptableFactor << "; "
		//	<< costBestSolution;
	}
	else
	{
		//
		// Print path;
		//

		cout << "Annealing:\n\t";

		for (int i = 0; i < vertexNumber; i++)
		{
			cout << bestSolution[i] << " -> ";
		}	

		cout << bestSolution[vertexNumber];
		cout << endl;

		cout << "\tSum: " << costBestSolution << endl << endl;
	}

	return costBestSolution;
}