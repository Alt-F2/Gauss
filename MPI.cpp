// Name: Andrew Izedomwen, Student ID: 201187740

#include <stdio.h>
#include <mpi.h>
#include <time.h>

int main() {

	double mA[3][3] = {
		{1, 1, -1},
		{6, 2, 2},
		{-3, 4, 1}
	};

	double mB[3] = { -3, 2, 1 };
	size_t n = sizeof(mB) / sizeof(mB[0]);
	double x[3];
	int k = 0, i = 0, j = 0;

	clock_t timer = clock();

	int ranking, processorNum, part;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &ranking);
	MPI_Comm_size(MPI_COMM_WORLD, &processorNum);
	part = n / processorNum;

	printf("\n ================= Forward Elimination Step =================");

	// Forward Elimination
	for (k = ranking * part; k < ranking * part + part; k++)
	{
		for (i = k + 1; i < ranking * part + part; i++)
		{
			double factor = mA[i][k] / mA[k][k];
			for (j = k; j < ranking * part + part; j++)
			{
				mA[i][j] -= factor * mA[k][j];
			}
			mB[i] -= factor * mB[k];
		}
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n + 1; j++)
		{
			printf("%.2f ", mA[i][j]);
		}

		printf("%.2f \n", mB[i]);
	}

	printf("\n ================= Backward Substitution Step =================");

	// Backward Substitution
	x[n - 1] = mB[n - 1] / mA[n - 1][n - 1];
	for (i = n - 1; i >= 0; i--)
	{
		double Sum = mB[i];
		for (j = i + 1; j < n; j++)
		{
			Sum -= mA[i][j] * x[j];
		}
		x[i] = Sum / mA[i][i];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n + 1; j++)
		{
			printf("%.2f ", mA[i][j]);
		}
		printf("\n");
	}

	// result of X
	for (i = 0; i < n; i++)
	{
		printf("\nResults of X%d: %.2f ", i + 1, x[i]);
	}

	printf("\n");

	return 0;
}
