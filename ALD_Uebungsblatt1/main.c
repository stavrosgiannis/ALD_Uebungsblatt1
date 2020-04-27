/**
* @file   main.c
* @author Stavros Giannis
* @date   25 April 2020
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
*
* Laufzeit Diagramm des Selection Sorts
* https://prnt.sc/s4zgpp
*
* comparisons Diagramm des Selection Sorts
* https://prnt.sc/s4zhjl
*
*/

/**
*  swap to given elements in an array
*
*  @param xp long integer stands for the first item in a list to swap with
*  @param yp stands for the second item to swap with
*  @returns swaps 2 of its given parameters in a list

*/
void swap(long int* xp, long int* yp)
{
	long int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

/**
*  computing selection-sort algorithm
*
*  @param arr stands for an array
*  @param n stands for the size of it's given array
*  @returns sorts an array from MIN to MAX
*
*/
void selectionSort(long int arr[], int n)
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

/**
*  fills the given array with random generated items
*
*  @param arr stands for an array
*  @param n stands for the size of it's given array
*  @returns an array with random filled elements
*
*/
void fillArrRandom(long int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = pow(2, (rand() % (17 + 1 - 10) + 10));
	}
}

/**
*  prints an array for DEBUG purposes
*
*  @param arr stands for an array
*  @param n stands for the size of it's given array
*  @returns printf of the array
*
*/
void printArray(long int arr[], int size)
{
	printf("[ ");
	for (int i = 0; i < size; i++)
	{
		printf("%li ", arr[i]);
		if (i < size - 1) {
			printf(", ");
		}
	}
	printf("]\n");
}

int main()
{
	long int* randArr;

	for (int i = 10; i <= 17; i++)
	{
		int size = pow(2, i);
		randArr = (long int*)malloc(size * sizeof(long int));

		printf("sorting array[%d] with random numbers between 2^10-2^17..\n", size);

		fillArrRandom(randArr, size);
		printf("Array: \n");
		printArray(randArr, size);

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
		float t3 = (float)(t2 - t1) / (float)CLOCKS_PER_SEC;

		printf("Sorted Array: \n");
		printArray(randArr, size);

		printf("runtime: %f\n", t3);
#endif

		/*
		* SelectionSort liegt somit in der Komplexitätsklasse O(n^2)
		* Um ein Array mit n Einträgen mittels SelectionSort zu sortieren, muss n-1-mal das Minimum bestimmt und ebenso oft getauscht werden.
		*
		* Bei der ersten Bestimmung des Minimums sind n−1 Vergleiche notwendig, bei der zweiten n-2 Vergleiche usw.
		*
		* Da zum Ermitteln des Minimums immer der komplette noch nicht sortierte Teil des Arrays durchlaufen werden muss,
		* benötigt SelectionSort auch im „besten Fall“ n(n − 1)/2 Vergleiche und im „schlechtesten Fall“ n(n +1)/2
		*/
		long long anzahlVergleiche = (0.5 * (pow(size, 2) + size));
		printf("comparisons: %lld\n\n", anzahlVergleiche);
	}

#ifdef _WIN32
	// verhindert das window closing
	getchar();
#endif

	return 0;
}