#include "mpi.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int n = 250;
    int** a, **b, **c;
    int my_rank;            
    int comm_sz;  
    int i, j, k;
    double start, finish;    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    cout << "check1\n";
    while (n < 2001) {
        a = new int* [n];
        for (i = 0; i < n; i++)
        {
            a[i] = new int[n];
            for (j = 0; j < n; j++)
            {
                a[i][j] = rand() % 10;
            }
        }
	cout << "check2\n";
        b = new int* [n];
        for (i = 0; i < n; i++)
        {
            b[i] = new int[n];
            for (j = 0; j < n; j++)
            {
                b[i][j] = rand() % 10;
            }
        }
	cout << "check3\n";
        c = new int* [n];
        start = MPI_Wtime();

        //Передача данных
        MPI_Bcast(b, n * n,  MPI_INT, 0, MPI_COMM_WORLD);
        for (i = 0; i < n; i++)
        {
            c[i] = new int[n];
            for (j = 0; j < n; j++)
            {
                c[i][j] = 0;
                for (k = 0; k < n; k++)
                    c[i][j] += a[i][k] * b[k][j];
            }
        }
        MPI_Gather(c, n*n, MPI_INT, c, n*n, MPI_INT, 0, MPI_COMM_WORLD);
	cout << "check4\n";
        finish = MPI_Wtime();
        delete[] a;
        delete[] b;
        delete[] c;
        std::cout << "Elapsed time = " << finish - start << " seconds" << std::endl;
	n+=250;
    }
    MPI_Finalize();
    return 0;
}