#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menuGestionClientes(){

    int opc;
    printf("Menu:\n");
    printf("1. Agregar Cliente\n");
    printf("2. Modificar Cliente\n"); 
    printf("3. Mostrar clientes\n");
    printf(">>> ");
    opc = ValidarFloatRango(1, 3);
    return opc;
}

void AgregarCliente() {
    Cliente cliente;

    printf("Ingrese el numero de cedula del cliente (SOLO NUMEROS): ");
    cliente.nmrCedula = ValidarFloatRango(1000000, 999999999);

    
    if (CedulaYaRegistrada(cliente.nmrCedula)) {
        printf("\n El cliente con cédula %d ya está registrado.\n", cliente.nmrCedula);
        return;
    }

    printf("Ingrese el nombre del cliente: ");
    leerCadena(cliente.nombre, 50);

    printf("Ingrese el apellido del cliente: ");
    leerCadena(cliente.apellido, 50);

    printf("Ingrese el telefono del cliente: ");
    cliente.telefono = ValidarFloatRango(10000000, 999999999);

    printf("Ingrese el presupuesto del cliente: ");
    cliente.presupuesto = ValidarFloatRango(0, 10000000);

    printf("Ingrese la marca preferida del cliente: ");
    leerCadena(cliente.preferenciaMarca, 20);

    printf("Ingrese el uso preferido del cliente (nuevo/usado): ");
    leerCadena(cliente.preferenciaUso, 20);

    printf("Ingrese el anioo preferido del cliente: ");
    cliente.preferenciaAnio = ValidarFloatRango(1800, 2026);


    printf("Ingrese el color preferido del cliente: ");
    leerCadena(cliente.preferenciaColor, 20);

    guardarClienteDentroDelArchivo(&cliente);
}

int CedulaYaRegistrada(int cedula) {
    FILE *c = fopen("clientes.dat", "rb");
    if (c == NULL) {
        return 0; // Si el archivo no existe, no hay registros
    }

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, c)) {
        if (cliente.nmrCedula == cedula) {
            fclose(c);
            return 1; // Encontrad
        }
    }

    fclose(c);
    return 0; // No encontrado
}

void guardarClienteDentroDelArchivo(Cliente *cliente){

    FILE *c = fopen("clientes.dat", "ab+");

    if (c == NULL){ // Verificar si el archivo se abrió correctamente
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(cliente, sizeof(Cliente), 1, c);
    fclose(c);
}

void modificarCliente(Cliente *cliente){

    FILE *f = fopen("clientes.dat", "rb+"); // abrir para lectura y escritura binaria
    if (f == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    int cedulaBuscada;
    int encontrado = 0;

    printf("Ingrese el número de cédula del cliente a modificar: ");
    cedulaBuscada = ValidarFloatRango(1000000, 999999999);

    while (fread(cliente, sizeof(Cliente), 1, f) == 1) {
        if (cliente->nmrCedula == cedulaBuscada) {
            encontrado = 1;
            int opcion2;

            do {
                printf("Cliente encontrado. ¿Qué desea modificar?\n");
                printf("1. Nombre\n");
                printf("2. Apellido\n");
                printf("3. Teléfono\n");
                printf("4. Presupuesto\n");
                printf("5. Marca preferida\n");
                printf("6. Uso preferido\n");
                printf("7. Año preferido\n");
                printf("8. Color preferido\n");
                printf(">>> ");
                int opcion = ValidarFloatRango(1, 8);

                switch (opcion) {
                    case 1:
                        printf("Nuevo nombre: ");
                        leerCadena(cliente->nombre, 50);
                        break;
                    case 2:
                        printf("Nuevo apellido: ");
                        leerCadena(cliente->apellido, 50);
                        break;
                    case 3:
                        printf("Nuevo teléfono: ");
                        cliente->telefono = ValidarFloatRango(100000000, 999999999);
                        break;
                    case 4:
                        printf("Nuevo presupuesto: ");
                        cliente->presupuesto = ValidarFloatRango(0, 10000000);
                        break;
                    case 5:
                         printf("Nueva marca preferida: ");
                        leerCadena(cliente->preferenciaMarca, 20);
                        break;
                    case 6:
                        printf("Nuevo uso preferido (nuevo/usado): ");
                        leerCadena(cliente->preferenciaUso, 20);
                        break;
                    case 7:
                        printf("Nuevo año preferido: ");
                        cliente->preferenciaAnio = ValidarFloatRango(1800, 2026);
                        break;
                    case 8:
                        printf("Nuevo color preferido: ");
                        leerCadena(cliente->preferenciaColor, 20);
                        break;
                    
                    default:
                        printf("Opción inválida.\n");
                        break;
                }

                fseek(f, sizeof(Cliente), SEEK_SET);
                fwrite(cliente, sizeof(cliente), 1, f);
                
                printf("Desea seleccionar otra opcion a editar? (1 = sí, 0 = no): ");
                opcion2 = ValidarFloatRango(0, 1);

            } while(opcion2 == 1);

        }
    }

    if (encontrado == 0) {
        printf("No se encontró un vehículo con ese ID.\n");
    }

    fclose(f);
}   
    
void mostrarClientes(){
    FILE *c = fopen("clientes.dat", "rb");
    if (c == NULL){
        printf("Aun no hay clientes registrados\n");
        fclose(c);
        return;
    } 

    Cliente cliente;
    printf("\n--- LISTA DE CLIENTES ---\n");
    while (fread(&cliente, sizeof(Cliente), 1, c)){
        printf("Cedula: %d | Nombre: %s %s | Telefono: %d | Presupuesto: %.2f\n",
               cliente.nmrCedula, cliente.nombre, cliente.apellido,
               cliente.telefono, cliente.presupuesto);

        printf("Preferencias:\n");
        printf("  Marca: %s\n", cliente.preferenciaMarca);
        printf("  Uso: %s\n", cliente.preferenciaUso);
        printf("  Anio mínimo: %d\n", cliente.preferenciaAnio);
        printf("  Color: %s\n", cliente.preferenciaColor);
        printf("-------------------------------------------\n");
    }

    fclose(c);
}

