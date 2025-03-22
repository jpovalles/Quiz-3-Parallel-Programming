#include "matrizHotplate.h"
#include <iomanip>
using namespace std;

/*
    @param arr 2D-Matrix
*/

void initialize(float arr[][MAXCOL]){
    for(int i = 0; i < MAXROW; i++){
        for(int j = 0; j < MAXCOL; j++){
            if (i == 0 || j == 0 || j == (MAXCOL - 1)){
                arr[i][j] = 0.0;    // Cold state
            } else if (i == (MAXROW - 1)){
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

void new_values(float arr2[][MAXCOL], float arr1[][MAXCOL]){
    for(int i = 0; i < MAXROW; i++){
        //cout << "i " << i << "     lim " << MAXROW << endl;
        for(int j = 0; j < MAXCOL; j++){
            //cout << "j " << i << "     lim " << MAXCOL << endl;
            if (i == 0 || j == 0 || i == (MAXROW - 1) || (i == 400 && j < 500) || (i == 512 && j == 512)){
                // Skip
            } else {
                arr2[i][j] = ((arr1[i][j+1] + arr1[i][j-1] + arr1[i-1][j] + arr1[i+1][j]) + (4.0*(arr1[i][j])))/ 8.0;
                //cout << "arr[" << i <<"][" << j <<"] = " << arr2[i][j] << endl;
            }
        }
    }

}

int check_convergence(float arr[][MAXCOL]){
    float convergence;
    for(int i = 0; i < MAXROW; i++){
        for(int j = 0; j < MAXCOL; j++){
            if (i == 0 || j == 0 || i == (MAXROW - 1) || (i == 400 && j < 500) || (i == 512 && j == 512)){
                // Skip
            } else {
                convergence = arr[i][j] - ((arr[i][j-1] + arr[i][j+1] + arr[i+1][j] + arr[i-1][j]) / 4.0);
                if (fabs(convergence) > 0.1){
                    return 1; // status
                } 
            }
   
        }
    }

    return 0; // status

}

/*
    Step
*/ 

double step(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

int main(){
	float arr1[MAXROW][MAXCOL];
	float arr2[MAXROW][MAXCOL];

    
    initialize(arr1);
    initialize(arr2);

    int it = 0;
    const int MAX_IT = 1000;
    int maxHeat = 30;
    int hotCells;


    double start_time = step();

    
    while(check_convergence(arr1) && it < MAX_IT){
        
        /*
        cout << "MATRIZ "<<it << endl;
        for(int i = 0; i < MAXROW; i++){
            for(int j = 0; j < MAXCOL; j++){
                cout << setprecision(2) << arr1[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;
        */

        hotCells = 0;
        new_values(arr2, arr1);
        
        for(int i = 0; i < MAXROW; i++){
            for(int j = 0; j < MAXCOL; j++){
                arr1[i][j] = arr2[i][j];
                if(arr1[i][j] >= maxHeat) hotCells++;
            }
        }

        it++;
    }

    /*
    cout << "MATRIZ FINAL" << endl;
    for(int i = 0; i < MAXROW; i++){
        for(int j = 0; j < MAXCOL; j++){
            cout << setprecision(2) << arr1[i][j] << " ";
        }
        cout << endl;
    }
    */

    double end_time = step();
    cout << "Número de celdas con temp mayor a " << maxHeat << "°: " <<hotCells << "/" << MAXCOL*MAXROW<<endl << endl;
 
    cout << "Tiempo de ejecucion: " << end_time - start_time << "s" << endl;
    return 0;


}
