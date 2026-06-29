# Especificación de Requerimientos Funcionales - SGIC "Ruedas de Oro"

Este documento detalla los requerimientos funcionales, el modelo de datos y la arquitectura de persistencia para el Sistema de Gestión de Inventario y Clientes (SGIC).

---

## 1. Modelo de Datos y Estructuras (C)

Para garantizar la persistencia solicitada, el sistema operará mediante archivos planos (`.txt`) o binarios (`.dat`). Las estructuras de datos principales se definen a continuación:

```c
typedef struct {
    char placa[10];
    char tipo[20];       // Ej: "Camioneta", "Sedan"
    char marca[30];      // Ej: "Chevrolet"
    float precio;
    char estado[10];     // "Nuevo" o "Usado"
    int disponible;      // 1 = Disponible, 0 = Vendido
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