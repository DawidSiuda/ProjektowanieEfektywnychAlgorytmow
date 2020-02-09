#pragma once

int annealing(int** array, int width, int test = 0,
				double begTemperature = 0, double tempChangeFactor = 0, double worAccepFactor = 0);