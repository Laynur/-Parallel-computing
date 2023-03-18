#include <cmath>
#include <time.h>
#include <omp.h>
#include <stdio.h>
#include <Windows.h>
#define size 500
void getMatrix(double a[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%lf\t", a[i][j]);
        }
        printf("\n");
    }
}
void getCornerElemMatrix(double a[size][size])
{
    printf("%lf\t %lf\t \n %lf\t %lf\t \n", a[0][0], a[0][size-1], a[size-1][0],a[size-1][size-1]);
}
void changeMatrixA(double a[size][size])
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            a[i][j] = 0.;
        }
    }

}
void multMatrix(double a[size][size], double b[size][size], double c[size][size], int q)
{
    double sum = 0.;
    for (int s = 0; s < q; s++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    sum += a[i][k] * b[k][j];
                    
                }
                c[i][j] = sum;
                sum = 0.;
            }
        }
    }
}
void parrmultMatrix(double a[size][size], double b[size][size], double c[size][size], int q)
{
    int k;
    double sum = 0.;
  //  omp_set_num_threads(6);
#pragma omp parallel for 
    for (int s = 0; s < q; s++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
#pragma omp parallel for reduction(+:sum) schedule(static) private(k) 
                for (k = 0; k < size; k++)
                {                  
                    sum += a[i][k] * b[k][j]; 
                }
                c[i][j] = sum;
                sum = 0.;
            }
        }
    }
}

void modiftmultMatrix(double a[size][size], double b[size][size], double c[size][size], int q)
{
    int k;
    double sum = 0.;
    changeMatrixA(a);
  //  omp_set_num_threads(6);
#pragma omp parallel for 
    for (int s = 0; s < q; s++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
#pragma omp parallel for reduction(+:sum) private(k) schedule(static)
                for (k = 0; k < size; k++)
                {
                    sum += a[i][k] * b[k][j];                
                }
                c[i][j] = sum;
                sum = 0.;
            }
        }
    }
}
void creatMatrix(double a[size][size], double b[size][size], double c[size][size])
{
    //srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            a[i][j] = (double)(rand()) / RAND_MAX - 0.5;
            b[i][j] = (double)(rand()) / RAND_MAX - 0.5;
            c[i][j] = 0;
        }
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int q;
    double matrA[size][size];
    double matrB[size][size];
    double matrC[size][size];
    double res1[size][size], res2[size][size], res3[size][size];
    clock_t t1, t2;
    double time1,time2,time3;
    creatMatrix(matrA, matrB, matrC);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            res1[i][j] = matrC[i][j];
            res2[i][j] = matrC[i][j];
            res3[i][j] = matrC[i][j];
        }
    }
    printf("Matrix A:\n");
    getCornerElemMatrix(matrA);
    printf("Matrix B:\n");
    getCornerElemMatrix(matrB);
    printf("Введите кол-во повторений:\n");
    scanf_s("%d", &q);
    
    t1 = clock();
    multMatrix(matrA, matrB, res1, q);
    t2 = clock();
    time1 = ((double)t2 - (double)t1) / (double)CLOCKS_PER_SEC;
    printf("Matrix C:\n");
    getCornerElemMatrix(res1);
    printf("Последова. time:%lf\n", time1);

    t1 = clock();
    parrmultMatrix(matrA, matrB, res2, q);
    t2 = clock();
    time2 = ((double)t2 - (double)t1) / (double)CLOCKS_PER_SEC;
    printf("Matrix C:\n");
    getCornerElemMatrix(res2);
    printf("Распаралл. time:%lf\n", time2);

    t1 = clock();
    modiftmultMatrix(matrA, matrB, res3, q);
    t2 = clock();
    printf("Matrix C:\n");
    time3 = ((double)t2 - (double)t1) / (double)CLOCKS_PER_SEC;;
    getCornerElemMatrix(res3);
    printf("Модифицир. time:%lf\n", time3);

    printf("кол-во повторений:%d\n", q);
}
