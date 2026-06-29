#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define VEHICULOS_FILE "vehiculos.dat"
#define CLIENTES_FILE "clientes.dat"
#define VENTAS_FILE "ventas.dat"

typedef struct {
    char placa[10];
    char tipo[20];
    char marca[30];
    float precio;
    char estado[10];
    int disponible; /* 1 = Disponible, 0 = Vendido */
} Vehiculo;

typedef struct {
    char cedula[11];
    char nombre[50];
    int edad;
} Cliente;

typedef struct {
    char id_venta[10];
    char placa_vehiculo[10];
    char cedula_cliente[11];
    char vendedor[50];
    float monto_final;
} Venta;

/* Utilidades de entrada */
int readIntInRange(int min, int max);
float readFloatInRange(float min, float max);
void readString(char *buffer, size_t size, const char *prompt);

/* Operaciones de persistencia y negocio */
int addVehiculo(const Vehiculo *v);
int addCliente(const Cliente *c);
int addVenta(const Venta *v);
int markVehiculoVendido(const char *placa);
void listarVehiculosPorPreferencias(const char *tipo, const char *marca, const char *estado, float precio_max);
int encontrarVehiculoPorPlaca(const char *placa, long *offset_out);
/* Funciones adicionales */
void mostrarInventario(void);
void mostrarClientes(void);
void mostrarVentas(void);
void mostrarComisionVentas(void);

#endif /* FUNCIONES_H */
