/**
* @file   main.c
* @author Stavros Giannis
* @date   25 April 2020
* @see    main.h for documenation.
*
* Simple Selection Sort example.
*/

#ifdef __linux__
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#endif

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#endif

/*
Laufzeit Diagramm des Selection Sorts
https://prnt.sc/s4zgpp

comparisons Diagramm des Selection Sorts
https://prnt.sc/s4zhjl
*/

/**
*  computes the factorial of a non-negative integer
*
*  @param n integer for which factorial should be computed
*  @returns 1 if n is negative,
*           MAXINT if factorial of n is greater than MAXINT
*            factorial of n in other cases
*/
void swap(double* xp, double* yp)
{
	double temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(double arr[], int n)
{
	int i, j, min_index;

	for (i = 0; i < n - 1; i++)
	{
		min_index = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;
			}
		}
		swap(&arr[min_index], &arr[i]);
	}
}

void fillArrRandom(double arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = pow(2, (rand() % (17 + 1 - 10) + 10));
	}
}

void printArray(double arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%f ", arr[i]);
	}
	printf("\n");
}

int main()
{
	double* randArr;

	for (int i = 10; i <= 17; i++)
	{
		int size = pow(2, i);
		randArr = (double*)malloc(size * sizeof(double));

		printf("sorting array[%d] with random numbers between 2^10-2^17..\n", size);

		fillArrRandom(randArr, size);
		//printf("Array: \n");
		//printArray(randArr, size);

#ifdef __linux__
		//Laufzeit relevante var
		double start;
		struct timeval tm;
		double duration;
		/////////////////////////////
		//Start der Laufzeit
		gettimeofday(&tm, NULL);
		start = (double)(tm.tv_sec) + ((double)(tm.tv_usec)) / 1.0e6;
		//////////////////////////////

		// function call
		selectionSort(randArr, size);

		//Ende der Laufzeit
		gettimeofday(&tm, NULL);
		duration = (double)(tm.tv_sec) + ((double)(tm.tv_usec)) / 1.0e6 - start;
		/////////////////////////////

		//printArray(randArr, size);
		printf("runtime: %f\n", duration);
#endif

#ifdef _WIN32
		clock_t t1 = clock();

		// function call
		selectionSort(randArr, size);

		clock_t t2 = clock();
		double t3 = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

		//printf("Sorted Array: \n");
		//printArray(randArr, size);
		printf("runtime: %f\n", t3);
#endif

		/*
		* SelectionSort liegt somit in der Komplexitätsklasse O(n^2)
		* Um ein Array mit n Einträgen mittels SelectionSort zu sortieren, muss n-1-mal das Minimum bestimmt und ebenso oft getauscht werden.
		*
		* Bei der ersten Bestimmung des Minimums sind n−1 Vergleiche notwendig, bei der zweiten n-2 Vergleiche usw.
		*
		* Da zum Ermitteln des Minimums immer der komplette noch nicht sortierte Teil des Arrays durchlaufen werden muss,
		* benötigt SelectionSort auch im „besten Fall“ n(n − 1)/2 Vergleiche und im "worse Fall" im „besten Fall“ n(n +1)/2
		*/
		long long anzahlVergleiche = (0.5 * (pow(size, 2) + size));
		printf("comparisons: %lld\n\n", anzahlVergleiche);
	}

#ifdef _WIN32
	getchar();
#endif

	return 0;
}