#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <cmath>
int main()
{
    setlocale(LC_ALL, "rus");
    clock_t t1, t2;
    double time;
    double sum=0.;
    int N = 100000000;
    //int N = 200000000;
    //int N = 400000000;
    std::cout << "программная реализация последовательного алгоритма суммирования функц. ряда" << '\n';
    // программная реализация последовательного алгоритма суммирования функц. ряда
    t1 = clock();
    for (int i = 1; i <= N; i++)
    {
        sum += pow(-1, i - 1) / pow(2 * i - 1, 2);
    }
    t2 = clock();
    time = (double)(t2 - t1) / (double)  CLOCKS_PER_SEC;
    std::cout.precision(13);
    std::cout <<"sum="<<'\t' << sum << "\n";
    std::cout << "time="<< '\t' << time<<"\n";
    std::cout << "Распараллеливание путем добавления директив OpenMP" << "\n";
    //Распараллеливание путем добавления директив OpenMP
    clock_t t3, t4;
    sum = 0.;
    time = 0.;
    int countth;
    std::cout << "Cколько потоков хотите задать?\n";
    std::cin >> countth;
    t3 = clock();
#pragma omp parallel for reduction(+:sum) num_threads(countth)
//#pragma omp parallel for reduction(+:sum) 
    for (int i = 1; i <= N; i++)
    {
        sum += pow(-1, i - 1) / pow(2 * i - 1, 2);
    }
    t4 = clock();
    time = (double)(t4 - t3) / (double)CLOCKS_PER_SEC;
    std::cout << "sum=" << '\t' << sum << "\n";
    std::cout << "time=" << '\t' << time << "\n";
    std::cout << "Модифицированный код параллельной программы\n";
    //Модифицированный код параллельной программы
    int chunk1 = 1, chunk2 = 100, chunk3 = 10000;
    clock_t t5, t6;
    sum = 0.;
    time = 0.;
    t5 = clock();
#pragma omp parallel for schedule (guided,chunk1) 
    for (int i = 1; i <= N; i++)
    {
        sum += pow(-1, i - 1) / pow(2 * i - 1, 2);
    }
    t6 = clock();
    time = (double)(t6 - t5) / (double)CLOCKS_PER_SEC;
    std::cout << "sum=" << '\t' << sum << "\n";
    std::cout << "time=" << '\t' << time;
}
