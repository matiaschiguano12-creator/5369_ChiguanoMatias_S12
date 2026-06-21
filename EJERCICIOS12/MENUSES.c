#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menuInterfaz(){
    
    int opc;
    printf("Menu:\n");
    printf("1. Trabajador\n");
    printf("2. Cliente\n");
    printf(">>> ");
    opc = ValidarFloatRango(1, 2);
    return opc;

}

int menuTrabajador(){

    
    int opc;
    printf("Menu:\n");
    printf("1. Gestion de Vehiculos\n");
    printf("2. Gestion de Clientes\n");
    printf("3. Gestion de Vendedores\n"); 
    printf(">>> ");
    opc = ValidarFloatRango(1, 3);
    return opc;

}


