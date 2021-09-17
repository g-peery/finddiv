/*
 * ./finddiv.c
 *
 * Reads lines of non-negative integers from stdin and prints a contiguous of 
 * subset of them on stdout such that their sum is divisible by the number of 
 * integers provided.
 *
 * Author: Gabriel Peery
 * Date: 9/17/21
 */
#include <stdio.h>
#include <stdlib.h>

#define UNUSED __attribute__((unused))
#define pg(msg) { printf(msg, argv[0]); goto cleanup; }
#define DEF_SIZE 16

/* Prints numbers in array from indices low to high inclusive. */
void printNumbers(unsigned int *numbers, int low, int high) {
	for (int i = low; i <= high; i++)
		printf("%u\n", numbers[i]);
}

int main(UNUSED int argc, UNUSED char *argv[]) {
	int status = EXIT_FAILURE; /* Assume failure */
	unsigned int *numbersRead = NULL; /* Will store ints found on lines */
	unsigned int *incidence = NULL; /* Will store index+1 of found sums */
	unsigned int num; /* Read from each line */
	int lineCount = 0;
	int spaceAllocated = 0;

	/* Read from stdin */
	while (scanf("%u", &num) == 1) {
		if (spaceAllocated == 0) {
			/* Create space for numbers */
			numbersRead = (unsigned int *)malloc(DEF_SIZE*sizeof(int));
			if (numbersRead == NULL)
				pg("%s: Problem allocating memory.\n")
			spaceAllocated = DEF_SIZE;
		} else if (lineCount == spaceAllocated) {
			/* Grow the array */
			unsigned int *newNumbers = (unsigned int *)realloc(
						numbersRead, 2*spaceAllocated*sizeof(int)
				);
			if (newNumbers == NULL)
				pg("%s: Problem reallocating.\n")
			numbersRead = newNumbers;
			spaceAllocated *= 2;
		}
		numbersRead[lineCount++] = num;
	}

	/*
	 * Scan through sums 
	 */
	/* Create incidence table */
	incidence = (unsigned int *)malloc(lineCount * sizeof(int));
	if (incidence == NULL)
		pg("%s: Problem allocating incidence table.\n")
	for (int i = 0; i < lineCount; i++)
		incidence[i] = 0; /* 0 is sentinal for not yet seen */

	/* Use num as sum this time */
	num = 0;
	for (int i = 0; i < lineCount; i++) {
		num += numbersRead[i];
		num = num % lineCount;
		/* Check if run from 0 to i works */
		if (num == 0) {
			printNumbers(numbersRead, 0, i);
			break;
		} else {
			if (incidence[num]) {/* Already found */
				printNumbers(numbersRead, incidence[num], i);
				break;
			}
			/* Offset by one for nice boolean logic. */
			incidence[num] = i + 1; 
		}
	}

	status = EXIT_SUCCESS;
cleanup:
	if (numbersRead != NULL)
		free(numbersRead);
	if (incidence != NULL)
		free(incidence);
	return status;
}
