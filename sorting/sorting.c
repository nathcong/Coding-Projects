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

#define OPTIONS "bc"

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
	/* initial loop for number of passes through the array */
	for (int j = 0; j < 25; j++) {
		/* nested loop for comparisons and swapping */
		for (int i = 0; i < 24; i++) {
			if (A[i] > A[i+1]) {
				temp = A[i+1];
				A[i+1] = A[i];
				A[i] = temp;			
			}
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

int main(int argc, char **argv) {
	int opt = 0;
	bool arguments = false;
	
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
		/* print original array */
		fprintf(stdout, "Unsorted Array:\n");
		for (int i = 0; i < 25; i++) {
			fprintf(stdout, "%d ", OA[i]);
		}
		fprintf(stdout, "\n\n");

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
		fprintf(stdout, "No arguments detected. Execution terminated.\n");
		free(A);
		free(OA);
		return -1;
	}

	fprintf(stdout, "Sorts completed, ending program.\n");
	free(A);
	free(OA);
	return 0;
}
