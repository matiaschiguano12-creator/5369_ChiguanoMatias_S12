#include <stdio.h>
#include "funciones.h"
#define MAX_LIBROS 10


int main (int argc, char *argv[]) {

    RequerimientosLibro biblioteca[MAX_LIBROS];
    int cantidad = 0; // Variable para llevar el conteo de libros registrados
    int opcion1 = 0, opcion2 = 0;

    do {
        opcion1 = menu();
        switch(opcion1) {
            case 1:
                RegistrarLibro(biblioteca, &cantidad); 
                break;
            case 2:
                mostrarLibros(biblioteca, cantidad); 
                break;
            case 3:
                buscarLibro(biblioteca, cantidad); 
                break;
            case 4:
                actualizarEstado(biblioteca, cantidad); 
                break;
            case 5:
                eliminarLibro(biblioteca, &cantidad); 
                break;
            case 6: 
                printf("Saliendo...\n"); 
                return 0;
            default: printf("Opcion invalida.\n");
        }

        printf("Desea realizar otra operacion? (Si.1/No.2): ");
        opcion2 = validarIntRango(1, 2);
        while (getchar() != '\n'); // limpia el buffer antes de repetir
    } while (opcion2 == 1);

    return 0;
}