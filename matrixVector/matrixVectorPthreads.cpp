#include <iostream>
#include <ctime>
#include <cstdlib>
#include <pthread.h>

using namespace std;

int **matrix;
int *vector;
int *result;
int cols;

#define NTHREADS 2

typedef struct {
    int startRow;
    int endRow;
}ThreadData;

void *multiplyRow(void *arg) {
    ThreadData* data = (ThreadData*) arg;
    int start = data->startRow;
    int end = data->endRow;

    for(int i = start; i < end; i++){
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int rows = atoi(argv[1]);
    cols = atoi(argv[2]);

    ThreadData threadData[NTHREADS];
    int rowsPerThread = rows / NTHREADS;
    int exc = rows % NTHREADS;

    srand(time(0));


    matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 10;
        }
    }

    cout << "MATRIX"<< endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    

    vector = (int *)malloc(cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        vector[i] = rand() % 10;
    }

    cout << "VECTOR"<< endl;
    for (int i = 0; i < cols; i++) {
        cout << vector[i] << " ";
    }
    cout << endl;


    result = (int *)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    pthread_t threads[NTHREADS];
    for (int i = 0; i < NTHREADS; i++) {
        threadData[i].startRow = i * rowsPerThread;
        threadData[i].endRow = (i == NTHREADS -1 ) ? rowsPerThread + exc : (i+1) * rowsPerThread;
        pthread_create(&threads[i], NULL, multiplyRow, (void *)&threadData[i]);
    }

    for(int i = 0; i < NTHREADS; i++){
        pthread_join(threads[i], NULL);
    }


    cout << "RESULT"<< endl;
    for (int i = 0; i < rows; i++) {
        cout << result[i] << " ";
    }
    cout << endl;


    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);
    return 0;

}