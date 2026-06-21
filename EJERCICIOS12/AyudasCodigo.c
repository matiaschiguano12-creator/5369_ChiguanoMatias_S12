#include <stdio.h>
#include <string.h>
#include "funciones.h"

void leerCadena (char *cadena, int n){

    int len;
    fgets(cadena, n, stdin);
    len = strlen(cadena) - 1;
    cadena[len] = '\0';

}

float ValidarFloatRango (float a, float b){

    float aux, n;
    do{
        aux = scanf("%f", &n);
        while(getchar() != '\n');
        
        if (aux != 1 || n < a || n > b){
            printf("Error, ingrese un numero entre %f y %f: ", a, b);
            printf(">>> ");
        
        }
    } while (aux != 1 || n < a || n > b);
    return n;

}