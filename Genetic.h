#pragma once

#define PRINT_WIDTH 7
#define DAW 2

//int genetic(int** aArray, int aWidth, int test);
int genetic(int** aArray, int aWidth, int test, int populationMinSize = 20, int populationMaxSize = 40,
			    float mutateFactor = 0.1, int limitOfWorstSolution = 1500, int* aPopulationCounter = nullptr);

