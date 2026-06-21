#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menuCliente(){
    
    int opc;
    printf("Menu:\n");
    printf("1. Mostrar Todos los vehiculos (Sin preferencias)\n");
    printf("2. Buscar Vehiculo por preferencias\n");
    printf(">>> ");
    opc = ValidarFloatRango(1, 2);
    return opc;

}


void consultarVehiculosPorPreferencias(Vehiculo vehiculo, Cliente cliente) {
    int cedulaBuscada;
    int encontrado = 0;

    printf("Ingrese el número de cédula del cliente: ");
    cedulaBuscada = ValidarFloatRango(1000000,99999999);

    FILE *c = fopen("clientes.dat", "rb");
    if (c == NULL) {
        printf("Error al abrir clientes.dat\n");
        return;
    }

    
    while (fread(&cliente, sizeof(Cliente), 1, c)) {
        if (cliente.nmrCedula == cedulaBuscada) {
            encontrado = 1;
            break;
        }
    }
    fclose(c);

    if (!encontrado) {
        printf("Cliente no encontrado.\n");
        return;
    }

    printf("\nPreferencias del cliente %s %s:\n", cliente.nombre, cliente.apellido);
    printf("Marca: %s | Uso: %s | Año >= %d | Presupuesto <= %.2f | Color: %s\n",
           cliente.preferenciaMarca, cliente.preferenciaUso,
           cliente.preferenciaAnio, cliente.presupuesto,
           cliente.preferenciaColor);

    FILE *f = fopen("vehiculos.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir vehiculos.dat\n");
        return;
    }

    printf("\nVehículos que cumplen las preferencias:\n");
    int coincidencias = 0;

    // Usamos tu variable global 'vehiculo'
    while (fread(&vehiculo, sizeof(Vehiculo), 1, f)) {
        if (vehiculo.disponibilidad == 1 && // SOLO si está disponible
            strcmp(vehiculo.marca, cliente.preferenciaMarca) == 0 &&
            strcmp(vehiculo.uso, cliente.preferenciaUso) == 0 &&
            vehiculo.aniofabricacion >= cliente.preferenciaAnio &&
            vehiculo.precio <= cliente.presupuesto &&
            strcmp(vehiculo.color, cliente.preferenciaColor) == 0) {

            printf("\nID: %d | %s %s | Año: %d | Precio: %.2f | Color: %s\n",
                   vehiculo.id, vehiculo.marca, vehiculo.modelo,
                   vehiculo.aniofabricacion, vehiculo.precio, vehiculo.color);
            coincidencias++;
        }
    }
    fclose(f);

    if (coincidencias == 0)
        printf("\nNo hay vehículos disponibles que cumplan las preferencias.\n");
}
