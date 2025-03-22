#include <vector>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <iostream>
#include <omp.h>
using namespace std;

/*
    @param arr 2D-Matrix
*/

void initialize(vector<vector<float>> &arr, int maxRow, int maxCol){
    for(int i = 0; i < maxRow; i++){
        for(int j = 0; j < maxCol; j++){
            if (i == 0 || j == 0 || j == (maxCol - 1)){
                arr[i][j] = 0.0;    // Cold state
            } else if (i == (maxRow - 1)){
                arr[i][j] = 100.0;  // Hot state
            } else if (i == 400 && j < 500){
                arr[i][j] = 100.0;  // Hot Zone
            } else if (i == 512 && j == 512){
                arr[i][j] = 100.0;  // Hot Point
            } else {
                arr[i][j] = 0.0;    // Cold state
            }
        }
    }  
}

/*
    @param arr2
    @param arr1
*/

void new_values(vector<vector<float>> &arr1, vector<vector<float>> &arr2, int maxRow, int maxCol){
    #pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        int rows_per_thread = maxRow / num_threads;
        int start_row = thread_id * rows_per_thread;
        int end_row = (thread_id == num_threads - 1) ? maxRow : start_row + rows_per_thread;

        for(int i = start_row; i < end_row; i++){
            
            for(int j = 0; j < maxCol; j++){
                if (i == 0 || j == 0 || i == (maxRow - 1) || (i == 400 && j < 500) || (i == 512 && j == 512)){
                    // Skip
                } else {
                    arr2[i][j] = ((arr1[i][j+1] + arr1[i][j-1] + arr1[i-1][j] + arr1[i+1][j]) + (4.0*(arr1[i][j])))/ 8.0;
                }
            }
        }
    }
}

int check_convergence(vector<vector<float>> &arr, int maxRow, int maxCol){
    float convergence;
    int converged = 0;
    
    #pragma omp parallel reduction(+:converged)
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        
        int rows_per_thread = maxRow / num_threads;
        int start_row = thread_id * rows_per_thread;
        int end_row = (thread_id == num_threads - 1) ? maxRow : start_row + rows_per_thread;

        for(int i = start_row; i < end_row; i++){
            for(int j = 0; j < maxCol; j++){
                if (i == 0 || j == 0 || i == (maxRow - 1) || (i == 400 && j < 500) || (i == 512 && j == 512)){
                    // Skip
                } else {
                    convergence = arr[i][j] - ((arr[i][j-1] + arr[i][j+1] + arr[i+1][j] + arr[i-1][j]) / 4.0);
                    if (fabs(convergence) > 0.1){
                        converged = 1;
                    } 
                }
            }
        }
    }
    return converged; // status
}

/*
    Step
*/ 

double step(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}



int main(int argc, char *argv[]){
    int maxRow = atoi(argv[1]);
    int maxCol = atoi(argv[2]);

	vector<vector<float>> arr1(maxRow, vector<float>(maxCol));
    vector<vector<float>> arr2(maxRow, vector<float>(maxCol));

    
    initialize(arr1, maxRow, maxCol);
    initialize(arr2, maxRow, maxCol);

    int it = 0;
    const int MAX_IT = 1000;
    int maxHeat = 30;
    int hotCells;


    double start_time = step();

    
    while(check_convergence(arr1, maxRow, maxCol) && it < MAX_IT){
        hotCells = 0;
        new_values(arr1, arr2, maxRow, maxCol);
        
        #pragma omp parallel for reduction(+:hotCells)
        for(int i = 0; i < maxRow; i++){
            for(int j = 0; j < maxCol; j++){
                arr1[i][j] = arr2[i][j];
                if(arr1[i][j] >= maxHeat) hotCells++;
            }
        }

        it++;
    }

    double end_time = step();
    cout << "Número de celdas con temp mayor a " << maxHeat << "°: " <<hotCells << "/" << maxRow*maxCol <<endl << endl;
    cout << "Tiempo de ejecucion: " << end_time - start_time << "s" << endl;
    return 0;


}
