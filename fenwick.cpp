/*******************************************************************/
/* This program demonstrates the speedup for a Fenwick tree vs a   */
/* flat array for performing multiple prefix sums.  It generates a */
/* sequence of random numbers, then performs 1000 summations,      */
/* each of which starts and ends at random indices.                */
/*******************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Number of elements in the array
#define N (4*1024*1024)		// Elements in the array
#define COUNTS 1024		// Size of values stored
typedef unsigned long sum_t;	// Should be able to hold N * (COUNTS - 1)

// Number of queries to perform
#define NQUERIES 1000

// Isolate the least significant 1 bit.  E.g. LSB(0x1234) == 4.
#define LSB(i) ((i) & -(i))

// Fen_sum: return the sum of the first i elements, 0 through i-1.
sum_t Fen_sum(sum_t const *a, unsigned int i) 
{
	sum_t sum = 0;
	while (i) {
		sum += a[i-1];
		i -= LSB(i);
	}
	return sum;
}

// Fen_add: add k to element i (and thus Fen_sum(a, j) for all j > i)
void Fen_add(sum_t *a, unsigned int size, sum_t delta, unsigned int i) 
{
	while (i < size) {
		a[i] += delta;
		i += LSB(i+1);
	}
}

// Fen_range: Returns the sum of the elements [i..j-1]
// This could be written as "Fen_sum(a, j) - Fen_sum(a, i)",
// but it is possible to do it in less time (particularly for
// small ranges) by avoiding the terms that the two sums have
// in common.
sum_t Fen_range(sum_t const *a, unsigned int i, unsigned int j)
{
	sum_t sum = 0;

	while (j > i) {
		sum += a[j-1];
		j -= LSB(j);
	}

	while (i > j) {
		sum -= a[i-1];
		i -= LSB(i);
	}
	return sum;
}

// Fen_get: Returns the value of the element at index i
// (The time is proportional to the number of trailing 1 bits
// in i.  So even numbers are fast, and i = 0xffff takes 16 steps.)
sum_t Fen_get(sum_t const *a, unsigned int i)
{
	return Fen_range(a, i, i+1);
}

// Fen_set: sets the value of the element at index i
void Fen_set(sum_t *a, unsigned int size, sum_t value, unsigned int i)
{
	Fen_add(a, size, value - Fen_get(a, i), i);
}

// It's possible to initialize a Fenwick tree using Fen_add or
// Fen_set (you can even do the latter in-place if you go backward
// through the array), but for bulk initialization, this is faster.
void Fen_init(sum_t *a, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++) {
		unsigned int j = i + LSB(i+1);
		if (j < size)
			a[j] += a[i];
	}
}

// main: allocates an array of numbers and fills it with a sequence of
// random numbers, then performs a series of summations (queries).  It
// then repeats the process using a Fenwick tree rather than a flat
// array.  The sequence of random numbers and the bounds of each query
// are identical for the flat array and the Fenwick tree.  The time
// required to populate the data structure and the total time required
// for all queries is calculated and reported for the flat array and
// for the Fenwick tree.

int main(void)
{
	sum_t *a;
	unsigned int queries[NQUERIES*2];
	clock_t time1, time2, time3;
	time_t seed = time(NULL);

	// generate the bounds for all of the queries
	srandom(seed + 1);
	for (unsigned int i = 0; i < NQUERIES * 2; i += 2) {
		unsigned int q = random() % N, r = random() % N;
		bool reverse = q > r;

		queries[i +  reverse] = q;
		queries[i + !reverse] = r;
	}

	// allocate the array of sums
	a = (sum_t*)malloc(N * sizeof *a);

	// The following loop forces all pages into memory (otherwise the
	// timing of the algorithm could include a lot of page faults)
	for (unsigned int i = 0; i < N; i++)
		a[i] = 0;

	/*****************************************************************/
	/*   FLAT ARRAY METHOD                                           */
	/*****************************************************************/

	time1 = clock();
	// Store random numbers in a flat array
	srandom(seed);
	for (unsigned int i = 0; i < N; i++)
		a[i] = random() % COUNTS;
	time2 = clock();	// time2 - time1 = time for setup
	// perform the queries
	for (unsigned int j = 0; j < NQUERIES * 2; j += 2) {
		sum_t asum = 0;
		for (unsigned int i = queries[j]; i < queries[j+1]; i++)
			asum += a[i];
		printf(" %lu", asum);
	}
	time3 = clock();	// time3 - time2 = time for queries

	printf("\nFlat Array:\n Build: %f\n Query: %f\n",
		(time2-time1)*(1.0/CLOCKS_PER_SEC),
		(time3-time2)*(1.0/CLOCKS_PER_SEC));

	/*****************************************************************/
	/*   FENWICK TREE METHOD                                         */
	/*****************************************************************/

	time1 = clock();
	// Store the same random numbers in a Fenwick tree
	srandom(seed);
	for (unsigned int i = 0; i < N; i++)
		a[i] = random() % COUNTS;
	Fen_init(a, N);
	time2 = clock();	// time2 - time1 = time for setup
	// perform the queries
	for (unsigned int j = 0; j < NQUERIES * 2; j += 2)
		printf(" %lu", Fen_range(a, queries[j], queries[j+1]));
	time3 = clock();	// time3 - time2 = time for queries

	printf("\nFenwick:\n Build: %f\n Query: %f\n",
		(time2-time1)*(1.0/CLOCKS_PER_SEC),
		(time3-time2)*(1.0/CLOCKS_PER_SEC));

	free(a);
	return 0;
}
