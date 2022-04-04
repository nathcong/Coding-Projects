// This is a C program with various sorts, all runnable under the main program
// This program will generate a random array of 25 int values and sort it with the selected method(s)
// Created by Nathan Ong, 2022

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <getopt.h>
#include <stdbool.h>

#define OPTIONS "bch:is"

void help(void) {
	fprintf(stdout, "\nSYNOPSIS\n");
	fprintf(stdout, "  A library of sorting algorithms, all sorting a unique array of 25 integers.\n");
	fprintf(stdout, "USAGE\n");
	fprintf(stdout, "  ./sorting [sorting algorithm options]\n");
	fprintf(stdout, "OPTIONS\n");
	fprintf(stdout, "  -b: Bubble Sort\n");
	fprintf(stdout, "  -c: Cocktail Shaker Sort\n");
	fprintf(stdout, "  -h [min/max]: Heap Sort, option of minimum and maximum heap\n");
	fprintf(stdout, "  -i: Insertion Sort\n");
	fprintf(stdout, "  -s: Selection Sort\n");
	fprintf(stdout, "DESCRIPTION\n");
	fprintf(stdout, "Run without options to display this help message.\n\n");
	fprintf(stdout, "WIP, more algorithms and optimizations to come.\n\n");
}

/* reset array to original */
void reset(int *A, int *OA) {
	for (int i = 0; i < 25; i++) {
		A[i] = OA[i];
	}
}
/* print array for debugging/after sorting */
void printarray(int *A) {
	for (int i = 0; i < 25; i++) {
                fprintf(stdout, "%d ", A[i]);
        }
	fprintf(stdout, "\n\n");
}

void bubblesort(int *A) {
	int temp;
	bool swapped = false;

	/* initial loop for number of passes through the array */
	for (int j = 0; j < 25; j++) {
		/* nested loop for comparisons and swapping */
		for (int i = 0; i < 24; i++) {
			if (A[i] > A[i+1]) {
				temp = A[i+1];
				A[i+1] = A[i];
				A[i] = temp;
				swapped = true;
			}
		}
		if (swapped == false) {
			return;
		}
	}
}

void cocktailshakersort(int *A) {
	int temp;
	bool swapped = true;
	
	/* repeat back and forth passes until sorted */	
	while (swapped == true) {
		/* forward pass */
		swapped = false;
		for (int i = 0; i < 24; i++) {
			if (A[i] > A[i+1]) {
				temp = A[i+1];
				A[i+1] = A[i];
				A[i] = temp;
				swapped = true;	
			}
		}

		/* check if sorted */
		if (swapped == false) {
			return;
		}
	
		/* backwards pass */	
		swapped = false;
		for (int i = 23; i >= 0; i--) {
			if (A[i] > A[i+1]) {
				temp = A[i+1];
				A[i+1] = A[i];
				A[i] = temp;
				swapped = true;
			}
		}

		/* check if sorted */
		if (swapped == false) {
			return;
		}
	}
}

void heapsort(int *A, bool min/max) {
	
}

void insertionsort(int *A) {
	int temp;
	int j;

	/* initial loop to go through array in order */
	for (int i = 0; i < 25; i++) {
		j = i;
		temp = A[i];
		/* nested while to go through array backwards from i index until no swap is needed */
		while (j > 0 && temp < A[j-1]) {
			A[j] = A[j-1];
			j--;
		}
		A[j] = temp;
	}
}

void selectionsort(int *A) {
	int min;
	int temp;

	/* initial loop to track what indices have been sorted already */	
	for (int i = 0; i < 25; i++) {
		min = i;

		/* nested loop to start from first unsorted indice and find minimum value */
		for (int j = i; j < 25; j++) {
			if (A[min] > A[j]) {
				min = j;
			}
		}

		/* swap only if start point of search is not minimum (already in correct position */
		if (min != A[i]) {
			temp = A[i];
			A[i] = A[min];
			A[min] = temp;
		}
	}
}

int main(int argc, char **argv) {
	int opt = 0;
	bool arguments = false;
	bool first = true;
	bool max = false;

	/* guarantees unique numbers from previous runs */
        srand(time(0));

        /* generate random array */
        int *A =  malloc(sizeof(int) * 25);
        for (int i = 0; i < 25; i++) {
                A[i] = rand() % 1000000;
        }

        /* duplicate array to reset if multiple arguments inputted */
        int *OA = malloc(sizeof(int) * 25);
        for (int i = 0; i < 25; i++) {
                OA[i] = A[i];
        }

	/* check arguments to run appropriate sorts */
	while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
		arguments = true;
		
		if (first == true) {
			/* print original array */
			fprintf(stdout, "Unsorted Array:\n");
			printarray(OA);
			first = false;
		}

		switch (opt) {
			case 'b': {
				bubblesort(A);
				fprintf(stdout, "Bubble Sorted Array:\n");
				printarray(A);
				reset(A, OA);	
				break;
			}
			case 'c': {
				cocktailshakersort(A);
				fprintf(stdout, "Cocktail Shook Array:\n");
				printarray(A);
				reset(A, OA);
				break;
			}
			case 'h': {
				if (strcmp("min", optarg) == 0) {
					max = false;
				}
				else if (strcmp("max", optarg) == 0) {
					max = true;
				}
				else {
					fprintf(stdout, "Invalid parameters for -h. Execution terminated.\n");
				}
				heapsort(A, max);
				fprintf(stdout, "Heap Sorted Array:\n");
				printarray(A);
				reset(A, OA);
				break;
			}
			case 'i': {
				insertionsort(A);
				fprintf(stdout, "Insertion Sorted Array:\n");
				printarray(A);
				reset(A, OA);
				break;
			}
			case 's': {
				selectionsort(A);
				fprintf(stdout, "Selection Sorted Array:\n");
				printarray(A);
				reset(A, OA);
				break;
			}	  
			default: {
				fprintf(stdout, "Invalid argument detected. Execution terminated.\n");
				free(A);
				free(OA);
				return -1;
			}
		}
	}
	
	/* checks if arguments were detected, if not end program */
	if (arguments == false) {
		help();
		free(A);
		free(OA);
		return 0;
	}

	fprintf(stdout, "Sorts completed, ending program.\n");
	free(A);
	free(OA);
	return 0;
}
