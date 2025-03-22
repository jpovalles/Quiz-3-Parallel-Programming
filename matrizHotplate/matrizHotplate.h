#ifndef __HOTPLATE_H__
#define __HOTPLATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <iostream>

// Constants
#define MAXROW 1024
#define MAXCOL 1024

// funciones
void initialize(float arr[][MAXCOL]);
void new_values(float arr2[][MAXCOL], float arr1[][MAXCOL]);
int check_convergence(float arr[][MAXCOL]);
double step();

#endif // hotplate.h