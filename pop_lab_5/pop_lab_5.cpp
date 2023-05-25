#include <iostream>
#include"omp.h"

using namespace std;

const int arr_size_rows = 20000;
const int arr_size_columns = 20000;

int arr[arr_size_rows][arr_size_columns];

void init_arr();
int row_with_min_sum(int num_threads);
long long sum( int num_threads);

int main()
{
    init_arr();

    omp_set_nested(1);
    double t1 = omp_get_wtime();
#pragma omp parallel sections
    {
#pragma omp section
        {
            std::cout << "sum with 1 thread" << sum( 1) << endl;
            std::cout << "sum with 2 threads" << sum( 2) << endl;
            std::cout << "sum with 3 threads" << sum( 3) << endl;
            std::cout << "sum with 4 threads" << sum( 4) << endl;
            std::cout << "sum with 8 threads" << sum( 8) << endl;
            std::cout << "sum with 10 threads" << sum( 10) << endl;
            std::cout << "sum with 16 threads" << sum( 16) << endl;
            std::cout << "sum with 32 threads" << sum( 32) << endl;
        }
#pragma omp section
        {
            std::cout << "row with min sum with 1 thread" << row_with_min_sum( 1) << endl;
            std::cout << "row with min sum with 2 thread" << row_with_min_sum(2) << endl;
            std::cout << "row with min sum with 3 thread" << row_with_min_sum( 3) << endl;
            std::cout << "row with min sum with 4 thread" << row_with_min_sum( 4) << endl;
            std::cout << "row with min sum with 8 thread" << row_with_min_sum( 8) << endl;
            std::cout << "row with min sum with 10 thread" << row_with_min_sum( 10) << endl;
            std::cout << "row with min sum with 16 thread" << row_with_min_sum( 16) << endl;
            std::cout << "row with min sum with 32 thread" << row_with_min_sum( 32) << endl;
        }
    }
    double t2 = omp_get_wtime();

    cout << "Total time - " << t2 - t1 << " seconds" << endl;
}
void init_arr() {

    for (int i = 0; i < arr_size_rows; i++)
    {
        for (int j = 0; j < arr_size_columns; j++)
        {
            arr[i][j]=rand();
        }
    }
}
long long sum(int num_threads) {

    long long res = 0;

    double t1 = omp_get_wtime();
#pragma omp parallel for reduction(+:res) num_threads(num_threads)
    for (int i = 0; i < arr_size_rows; i++)
    {
        for (int j = 0; j < arr_size_columns; j++)
        {
            res += arr[i][j];
        }
    }
    double t2 = omp_get_wtime();

    cout << "sum " << num_threads << " threads worked - " << t2 - t1 << " seconds" << endl;

    return res;
}
int row_with_min_sum(int num_threads) {
    int row_sums[arr_size_rows];
    double t1 = omp_get_wtime();
#pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < arr_size_rows; i++)
    {
        int sum = 0;
        for (int j = 0; j < arr_size_columns; j++)
        {
            sum += arr[i][j];
        }
        row_sums[i] = sum;
    }
   int  index_row_with_min_sum = 0;
    //find row with min sum
    for (int i = 1; i < arr_size_rows; i++)
    {
        if (row_sums[index_row_with_min_sum] > row_sums[i]) index_row_with_min_sum = i;
    }
    //return sum
    double t2 = omp_get_wtime();

    cout << "row with min sum " << num_threads << " threads worked - " << t2 - t1 << " seconds" << endl;

    return index_row_with_min_sum;
}
