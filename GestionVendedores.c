#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menuGestionVendedores(){

    int opc;
    printf("Menu:\n");
    printf("1. Agregar Vendedor\n");
    printf("2. Modificar Vendedor\n");
    printf("3. Mostrar Vendedores\n");
    printf(">>> ");
    opc = ValidarFloatRango(1, 3);
    return opc;
}

void AgregarVendedor(){
    Vendedor vendedor;

    printf("Ingrese el número de cédula (ID): ");
    vendedor.nmrCedula = ValidarFloatRango(1, 999999999);

    printf("Ingrese el nombre del vendedor: ");
    leerCadena(vendedor.nombre, 50);

    printf("Ingrese el apellido del vendedor: ");
    leerCadena(vendedor.apellido, 50);

    printf("Ingrese el número de ventas realizadas: ");
    vendedor.nmrventas = ValidarFloatRango (0, 10000);

    FILE *h = fopen("vendedores.dat", "ab");
    if (h == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    fwrite(&vendedor, sizeof(Vendedor), 1, h);
    fclose(h);

    printf("\n Vendedor agregado correctamente.\n");
}

void editarVendedor(){
    FILE *h = fopen("vendedores.dat", "rb+"); // abrir para lectura y escritura binaria
    if (h == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    int cedulaBuscada;
    Vendedor vendedor;
    int encontrado = 0;

    printf("Ingrese el número de cedula del vendedor a editar: ");
    vendedor.nmrCedula = ValidarFloatRango(1000000, 999999999);

    // Buscar el vendedor por cédula
    while (fread(&vendedor, sizeof(Vendedor), 1, h)){
        if (vendedor.nmrCedula == cedulaBuscada){
            encontrado = 1;
            printf("\nVendedor encontrado:\n");
            printf("Nombre: %s\nApellido: %s\nVentas: %d\n",
                   vendedor.nombre, vendedor.apellido, vendedor.nmrventas);

                    int opcion;
                    int opcion2 = 0;
            do {
                printf("\n--- MENU DE EDICION ---\n");
                printf("1. Editar nombre\n");
                printf("2. Editar apellido\n");
                printf("3. Editar número de ventas\n");
                printf("Seleccione una opcion: ");
                opcion = ValidarFloatRango(1,3);

                switch(opcion){
                    case 1:
                        printf("Nuevo nombre: ");
                        leerCadena(vendedor.nombre, 50);
                        break;
                    case 2:
                        printf("Nuevo apellido: ");
                        leerCadena(vendedor.apellido, 50);
                        break;
                    case 3:
                        printf("Nuevo numero de ventas: ");
                        vendedor.nmrventas = ValidarFloatRango(0, 10000);
                        break;
                    default:
                        printf("Opcion inválida.\n");
                }

                fseek(h, sizeof(Vendedor), SEEK_SET);
                fwrite(&vendedor, sizeof(Vendedor), 1, h);

                printf("Desea seleccionar otra opcion a editar? (1 = si, 0 = no): ");
                opcion2 = ValidarFloatRango(0, 1);

            } while(opcion2 == 0);

            break;
        }
    }

    if (!encontrado)
        printf("No se encontro un vendedor con esa cedula.\n");

    fclose(h);
}

void mostrarVendedores(){
    FILE *h = fopen("vendedores.dat", "rb");
    if (h == NULL){
        printf("Error al abrir el archivo de vendedores\n");
        return;
    }

    Vendedor vendedor;
    printf("\n--- LISTA DE VENDEDORES ---\n");
    while (fread(&vendedor, sizeof(Vendedor), 1, h)){
        printf("Cédula: %d | Nombre: %s %s | Ventas: %d\n",
               vendedor.nmrCedula, vendedor.nombre, vendedor.apellido, vendedor.nmrventas);
    }

    fclose(h);
}

