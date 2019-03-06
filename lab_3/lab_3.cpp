// lab_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <omp.h>

const int massCount = 100000001;
using namespace std;

void CalculatorWithoutOMP(double *mass, double &massMax, double &massSumm)
{
	for (int i = 0; i < massCount; ++i)
	{
		massSumm += mass[i];
		if (massMax < mass[i])
		{
			massMax = mass[i];
		}
	}
}

void CalculatorWithOMP(double *mass, double &massMax, double &massSumm)
{
	double summ = 0;
	double max = mass[0];
#pragma omp parallel for reduction(+:summ)
	for (int i = 0; i < massCount; ++i)
	{
		summ += mass[i];
		if (max < mass[i])
		{
#pragma omp critical
			if (max < mass[i])
			{
				max = mass[i];
			}
		}
	}

	massMax = max;
	massSumm = summ;
}

int main()
{
	double *mass = new double[massCount];
	double massMax;
	double massSumm;
	long int start;
	long int end;

	omp_set_num_threads(4);
#pragma omp parallel for
	for (int i = 0; i < massCount; ++i)
	{
		mass[i] = (rand() % 100 + 1) / (double)(rand() % 100 + 1);
	}

	massMax = mass[0];
	massSumm = 0;
	cout << "Without openMP\n";
	start = clock();
	CalculatorWithoutOMP(mass, massMax, massSumm);
	end = clock();
	printf_s("Summ %f \n", massSumm);
	printf_s("Max %f \n", massMax);
	printf_s("Time %f sec\n", (end - start) / (float)CLOCKS_PER_SEC);

	massMax = mass[0];
	massSumm = 0;
	cout << "With openMP\n";
	start = clock();
	CalculatorWithOMP(mass, massMax, massSumm);
	end = clock();
	printf_s("Summ %f \n", massSumm);
	printf_s("Max %f \n", massMax);
	printf_s("Time %f sec\n", (end - start) / (float)CLOCKS_PER_SEC);

	system("pause");
	return 0;
}
