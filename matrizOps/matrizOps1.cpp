#include <vector>
#include <iostream>
#include <ctime>
using namespace std;


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
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[i].size(); j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> suma(vector<vector<int>> &arr1, vector<vector<int>> &arr2){
    int rows1 = arr1.size();
    int cols1 = arr1[0].size();
    int rows2 = arr2.size();
    int cols2 = arr2[0].size();

    if((rows1 != rows2) || (cols1 != cols2)){
        cout << "Las dimenseiones de <arr1> y <arr2> deben ser iguales." << endl;
        cout << "Dimensiones de <arr1> " << rows1 << "x" << cols1 << "\tDimensiones de <arr2> " << rows2 << "x" << cols2 << endl;
        return {};
    }

    vector<vector<int>> ans(rows1, vector<int>(cols1));

    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols1; j++){
            ans[i][j] = arr1[i][j] + arr2[i][j];
        }
    }
    
    return ans;
}

vector<vector<int>> transpose(vector<vector<int>> &arr){
    int rows = arr.size();
    int cols = arr[0].size();
    vector<vector<int>> ans(cols, vector<int>(rows));

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            ans[j][i] = arr[i][j];
        }
    }
    return ans;
}

vector<vector<int>> multiply(vector<vector<int>> &arr1, vector<vector<int>> &arr2){    
    int cols = arr1[0].size();
    int rows = arr2.size();

    if(cols != rows){
        cout << "El número de columnas de <arr1> debe ser igual al número de filas de <arr2>" << endl;
        cout << "Columnas en <arr1> " << cols << "\t" << "Filas en <arr2> " << rows << endl;
        return {};
    }

    rows = arr1.size();
    cols = arr2[0].size();
    vector<vector<int>> ans(cols, vector<int>(rows));
    int sum;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            sum = 0;
            for(int k = 0; k < rows; k++){
                sum += arr1[i][k] * arr2[k][j];
            }
            ans[i][j] = sum;
        }
    }

    
    return ans;
}

int main(int argc, char *argv[]){
    srand(time(nullptr));
    int rows = 3;
    int cols = 3;

    vector<vector<int>> arr1(rows, vector<int>(cols));
    vector<vector<int>> arr2(rows, vector<int>(cols));

    initialize(arr1, rows, cols);
    initialize(arr2, rows, cols);

    cout << "MATRIZ 1:" << endl;
    printMatrix(arr1);
    cout << "MATRIZ 2:" << endl;
    printMatrix(arr2);


    cout << "SUMA:" << endl;
    vector<vector<int>> sum(rows, vector<int>(cols));
    sum = suma(arr1, arr2);
    printMatrix(sum);

    cout << "TRANSPUESTA:" << endl;
    vector<vector<int>> trans(rows, vector<int>(cols));
    trans = transpose(arr1);
    printMatrix(trans);

    cout << "MULTIPLICACION:" << endl;
    vector<vector<int>> mult(rows, vector<int>(cols));
    mult = multiply(arr1, arr2);
    printMatrix(mult);

    return 0;
}