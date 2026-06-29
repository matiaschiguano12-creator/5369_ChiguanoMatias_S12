#include <stdio.h>
#include <string.h>
#include "funciones.h"

void mostrarMenu() {
    printf("\n--- SGIC - Ruedas de Oro ---\n");
        printf("1. Agregar vehiculo\n");
        printf("2. Agregar cliente\n");
        printf("3. Registrar venta\n");
        printf("4. Mostrar inventario\n");
        printf("5. Mostrar clientes\n");
        printf("6. Buscar vehiculos por preferencias\n");
        printf("7. Mostrar historial de ventas\n");
        printf("8. Mostrar comision de ventas por vendedor\n");
        printf("9. Salir\n");
        printf("Elija una opcion: ");
}

int main(void) {
    int opcion;
    char buf[128];

    while (1) {
        mostrarMenu();
        opcion = readIntInRange(1, 9);
        if (opcion == 1) {
            Vehiculo v;
            readString(v.placa, sizeof(v.placa), "Placa: ");
            readString(v.tipo, sizeof(v.tipo), "Tipo: ");
            readString(v.marca, sizeof(v.marca), "Marca: ");
            printf("Precio: "); v.precio = readFloatInRange(0.0f, 10000000.0f);
            readString(v.estado, sizeof(v.estado), "Estado (Nuevo/Usado): ");
            if (addVehiculo(&v) == 0) printf("Vehiculo agregado correctamente.\n"); else printf("Error al agregar vehiculo.\n");
        } else if (opcion == 2) {
            Cliente c;
            readString(c.cedula, sizeof(c.cedula), "Cedula: ");
            readString(c.nombre, sizeof(c.nombre), "Nombre: ");
            printf("Edad: "); c.edad = readIntInRange(0, 120);
            if (addCliente(&c) == 0) printf("Cliente agregado correctamente.\n"); else printf("Error: ya existe un cliente con esa cedula.\n");
        } else if (opcion == 3) {
            Venta v;
            readString(v.id_venta, sizeof(v.id_venta), "ID Venta: ");
            readString(v.placa_vehiculo, sizeof(v.placa_vehiculo), "Placa vehiculo: ");
            readString(v.cedula_cliente, sizeof(v.cedula_cliente), "Cedula cliente: ");
            readString(v.vendedor, sizeof(v.vendedor), "Vendedor: ");
            printf("Monto final: "); v.monto_final = readFloatInRange(0.0f, 10000000.0f);
            if (addVenta(&v) == 0) printf("Venta registrada correctamente.\n"); else printf("Error al registrar venta.\n");
        } else if (opcion == 4) {
            mostrarInventario();
        } else if (opcion == 5) {
            mostrarClientes();
        } else if (opcion == 6) {
            char tipo[32], marca[32], estado[16];
            float precio_max;
            readString(tipo, sizeof(tipo), "Tipo (enter para omitir): ");
            readString(marca, sizeof(marca), "Marca (enter para omitir): ");
            readString(estado, sizeof(estado), "Estado (Nuevo/Usado) (enter para omitir): ");
            printf("Precio maximo (0 para omitir): "); precio_max = readFloatInRange(0.0f, 10000000.0f);
            listarVehiculosPorPreferencias(tipo, marca, estado, precio_max);
        } else if (opcion == 7) {
            mostrarVentas();
        } else if (opcion == 8) {
            mostrarComisionVentas();
        } else if (opcion == 9) {
            printf("Saliendo...\n");
            break;
        }
    }
    return 0;
}
