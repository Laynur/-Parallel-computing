#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
double Sum = 0;
int main(int *argc, char* argv[])
{
	int N;
	int rank, p, h, m;
	int start = 0, end = 0;
	double t1 = 0, t2 = 0;

	MPI_Status status;
	MPI_Init(argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if (rank == 0)
	{
		printf("Enter count N:\n");
		std::cin >> N;
		t1 = MPI_Wtime();
		if (p > 1)
		{
			for (int i = 1; i < p; i++)
			{
				MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
		}
		h = N / p;
		m = N % p;
		if (m == 0)
		{
			start = rank * h + 1;
			end = (rank + 1) * h + 1;
		}
		else
		{
			if (rank < m)
			{
				start = rank * (h + 1) + 1;
				end = (rank + 1) * (h + 1) + 1;
			}
			else
			{
				start = rank * h + 1;
				end = (rank + 1) * h + 1;
			}
		}
		double sum = 0;
		for (int n = start; n < end; n++)
		{
			sum += pow(-1, (n - 1)) / pow((2 * n - 1), 2);
		}

		double prtsm;
		for (int i = 1; i < p; i++)
		{
			MPI_Recv(&prtsm, 1, MPI_DOUBLE, MPI_ANY_SOURCE,
				0, MPI_COMM_WORLD, &status);
			int sender = status.MPI_SOURCE;
			sum += prtsm;
		}
		t2 = MPI_Wtime();
		printf("Sum = %f\n", sum);
		printf("Time = %f\n", (t2 - t1));
	}
	else
	{
		MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
			&status);
		double PartSum = 0;
		h = N / p;
		m = N % p;
		if (m == 0)
		{
			start = rank * h + 1;
			end = (rank + 1) * h + 1;
		}
		else
		{
			if (rank < m)
			{
				start = rank * (h + 1) + 1;
				end = (rank + 1) * (h + 1) + 1;
			}
			else
			{
				start = rank * h + 1;
				end = (rank + 1) * h + 1;
			}
		}
		for (int n = start; n < end; n++)
		{
			PartSum += pow(-1, (n - 1)) / pow((2 * n - 1), 2);
		}
		MPI_Send(&PartSum, 1, MPI_DOUBLE, 0, 0,
			MPI_COMM_WORLD);
	}
	MPI_Finalize();


	// Коллективное взаимодействие
	/*if (rank == 0)
	{
		printf("Enter count N:\n");
		scanf("%d", N);
		t1 = MPI_Wtime();
	}
	MPI_Bcast(&N, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	h = N / p;
	m = N % p;
	if (m == 0)
	{
		start = rank * h + 1;
		end = (rank + 1) * h + 1;
	}
	else
	{
		if (rank < m)
		{
			start = rank * (h + 1) + 1;
			end = (rank + 1) * (h + 1) + 1;
		}
		else
		{
			start = rank * h + 1;
			end = (rank + 1) * h + 1;
		}
	}
	double PartSum = 0;
	for (int n = start; n < end; n++)
	{
		PartSum += pow(-1, (n - 1)) / pow((2 * n - 1), 2);
	}
	MPI_Reduce(&PartSum, &Sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
t2 = MPI_Wtime();
		printf("Sum = %f\n", Sum);
		printf("Time = %f\n", (t2 - t1));
	}
	MPI_Finalize();*/
}


