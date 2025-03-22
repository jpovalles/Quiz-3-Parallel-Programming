#include <vector>
#include <iostream>
#include <ctime>
#include <pthread.h>
using namespace std;

struct args{
    vector<vector<int>> *A;
    vector<vector<int>> *B;
    vector<vector<int>> *C;
    int rows, cols; 
};

pthread_mutex_t mut;

void initialize(vector<vector<int>> &arr, int rows, int cols){
    int num;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            num = (rand() % 10) + 1;
            arr[i][j] = num;
        }
    }
}

void printMatrix(vector<vector<int>> &arr){
    pthread_mutex_lock(&mut);
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[i].size(); j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    pthread_mutex_unlock(&mut);
}

void *suma(void *arg){
    args *data = (args *)arg;
    int rows1 = data->A->size();
    int cols1 = data->A->at(0).size();
    int rows2 = data->B->size();
    int cols2 = data->B->at(0).size();

    if((rows1 != rows2) || (cols1 != cols2)){
        cout << "Las dimenseiones de <arr1> y <arr2> deben ser iguales." << endl;
        cout << "Dimensiones de <arr1> " << rows1 << "x" << cols1 << "\tDimensiones de <arr2> " << rows2 << "x" << cols2 << endl;
        pthread_exit(nullptr);
    }

    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols1; j++){
            (*data->C)[i][j] = (*data->A)[i][j] + (*data->B)[i][j];
        }
    }
    
    cout << "SUMA" << endl;
    printMatrix((*data->C));
    pthread_exit(nullptr);
}

void *transpose(void *arg){
    args *data = (args *)arg;
    int rows = data->A->size();
    int cols = data->A->at(0).size();

    vector<vector<int>> *ans = data->B;

    *ans = vector<vector<int>>(cols, vector<int>(rows));

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            (*ans)[j][i]= (*data->A)[i][j];
        }
    }
    cout << "TRANSPUESTA de A" << endl;
    printMatrix(*ans);
    pthread_exit(nullptr);
}

void *multiply(void *arg){
    args *data = (args *)arg;
    int cols = data->A->at(0).size();
    int rows = data->B->size();

    if(cols != rows){
        cout << "El número de columnas de <arr1> debe ser igual al número de filas de <arr2>" << endl;
        cout << "Columnas en <arr1> " << cols << "\t" << "Filas en <arr2> " << rows << endl;
        pthread_exit(nullptr);
    }

    rows = data->A->size();
    cols = data->B->at(0).size();

    vector<vector<int>> *ans = data->C;

    *ans = vector<vector<int>>(rows, vector<int>(cols));

    int sum;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            sum = 0;
            for(int k = 0; k < rows; k++){
                sum += (*data->A)[i][k] * (*data->B)[k][j];
            }
            (*ans)[i][j] = sum;
        }
    }
    cout << "MULTIPLICACION" << endl;
    printMatrix(*ans);
    pthread_exit(nullptr);
}



int main(int argc, char *argv[]){
    srand(time(nullptr));
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    vector<vector<int>> arr1(rows, vector<int>(cols));
    vector<vector<int>> arr2(rows, vector<int>(cols));
    vector<vector<int>> sum(rows, vector<int>(cols));
    vector<vector<int>> trans(rows, vector<int>(cols));
    vector<vector<int>> mult(rows, vector<int>(cols));

    initialize(arr1, rows, cols);
    initialize(arr2, rows, cols);

    cout << "MATRIZ A:" << endl;
    printMatrix(arr1);
    cout << "MATRIZ B:" << endl;
    printMatrix(arr2);

    pthread_t threads[3];
    pthread_mutex_init(&mut, nullptr);

    args addData = {&arr1, &arr2, &sum, rows, cols};
    args multData = {&arr1, &arr2, &mult, rows, cols};
    args transData = {&arr1, &trans, nullptr, rows, cols};

    pthread_create(&threads[0], nullptr, suma, &addData);
    pthread_create(&threads[1], nullptr, multiply, &multData);
    pthread_create(&threads[2], nullptr, transpose, &transData);

    pthread_join(threads[0], nullptr);
    pthread_join(threads[1], nullptr);
    pthread_join(threads[2], nullptr);

    pthread_mutex_destroy(&mut);
    return 0;
}