#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


int main(int argc, char *argv[]) {
    int rows = 3;
    int cols = 3;

    srand(time(0));


    int matrix[rows][cols];
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
    

    int vector[cols];
    for (int i = 0; i < cols; i++) {
        vector[i] = rand() % 10;
    }

    cout << "VECTOR"<< endl;
    for (int i = 0; i < cols; i++) {
        cout << vector[i] << " ";
    }
    cout << endl;


    int result[rows];
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    cout << "RESULT"<< endl;
    for (int i = 0; i < rows; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;

}