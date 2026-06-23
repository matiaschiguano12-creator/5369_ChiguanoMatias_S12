#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>

/* Implementación de utilidades de entrada */
int readIntInRange(int min, int max) {
    int val;
    char buf[64];
    while (1) {
        if (!fgets(buf, sizeof(buf), stdin)) return min;
        if (sscanf(buf, "%d", &val) != 1) {
            printf("Entrada invalida. Intente de nuevo: ");
            continue;
        }
        if (val < min || val > max) {
            printf("Valor fuera de rango (%d - %d). Intente de nuevo: ", min, max);
            continue;
        }
        return val;
    }
}

float readFloatInRange(float min, float max) {
    float val;
    char buf[64];
    while (1) {
        if (!fgets(buf, sizeof(buf), stdin)) return min;
        if (sscanf(buf, "%f", &val) != 1) {
            printf("Entrada invalida. Intente de nuevo: ");
            continue;
        }
        if (val < min || val > max) {
            printf("Valor fuera de rango (%.2f - %.2f). Intente de nuevo: ", min, max);
            continue;
        }
        return val;
    }
}

void readString(char *buffer, size_t size, const char *prompt) {
    printf("%s", prompt);
    if (!fgets(buffer, (int)size, stdin)) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    } else {
        /* Si no se leyó el '\n', la entrada excedió el buffer; limpiar resto de la línea */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
}

/* Append a un archivo binario */
static int appendRecord(const char *filename, const void *record, size_t recSize) {
    FILE *f = fopen(filename, "ab");
    if (!f) return -1;
    size_t written = fwrite(record, recSize, 1, f);
    fclose(f);
    return written == 1 ? 0 : -1;
}

int addVehiculo(const Vehiculo *v) {
    Vehiculo copy = *v;
    copy.disponible = 1;
    return appendRecord(VEHICULOS_FILE, &copy, sizeof(Vehiculo));
}

int addCliente(const Cliente *c) {
    return appendRecord(CLIENTES_FILE, c, sizeof(Cliente));
}

int addVenta(const Venta *v) {
    int res = appendRecord(VENTAS_FILE, v, sizeof(Venta));
    if (res != 0) return res;
    return markVehiculoVendido(v->placa_vehiculo);
}

int encontrarVehiculoPorPlaca(const char *placa, long *offset_out) {
    FILE *f = fopen(VEHICULOS_FILE, "rb");
    if (!f) return -1;
    Vehiculo tmp;
    long offset = 0;
    while (fread(&tmp, sizeof(Vehiculo), 1, f) == 1) {
        if (strncmp(tmp.placa, placa, sizeof(tmp.placa)) == 0) {
            if (offset_out) *offset_out = offset;
            fclose(f);
            return 0;
        }
        offset += sizeof(Vehiculo);
    }
    fclose(f);
    return -1;
}

int markVehiculoVendido(const char *placa) {
    long offset;
    if (encontrarVehiculoPorPlaca(placa, &offset) != 0) return -1;
    FILE *f = fopen(VEHICULOS_FILE, "r+b");
    if (!f) return -1;
    if (fseek(f, offset, SEEK_SET) != 0) { fclose(f); return -1; }
    Vehiculo v;
    if (fread(&v, sizeof(Vehiculo), 1, f) != 1) { fclose(f); return -1; }
    v.disponible = 0;
    if (fseek(f, offset, SEEK_SET) != 0) { fclose(f); return -1; }
    size_t written = fwrite(&v, sizeof(Vehiculo), 1, f);
    fclose(f);
    return written == 1 ? 0 : -1;
}

void listarVehiculosPorPreferencias(const char *tipo, const char *marca, const char *estado, float precio_max) {
    FILE *f = fopen(VEHICULOS_FILE, "rb");
    if (!f) { printf("No se pudo abrir %s\n", VEHICULOS_FILE); return; }
    Vehiculo v;
    int found = 0;
    while (fread(&v, sizeof(Vehiculo), 1, f) == 1) {
        /* Omitir vehiculos ya vendidos */
        if (v.disponible == 0) continue;
        if (tipo && tipo[0] != '\0' && strcasecmp(v.tipo, tipo) != 0) continue;
        if (marca && marca[0] != '\0' && strcasecmp(v.marca, marca) != 0) continue;
        if (estado && estado[0] != '\0' && strcasecmp(v.estado, estado) != 0) continue;
        if (precio_max > 0 && v.precio > precio_max) continue;
        printf("Placa: %s | Tipo: %s | Marca: %s | Precio: %.2f | Estado: %s | %s\n",
               v.placa, v.tipo, v.marca, v.precio, v.estado, v.disponible ? "Disponible" : "Vendido");
        found = 1;
    }
    if (!found) printf("No se encontraron vehiculos que cumplan las preferencias.\n");
    fclose(f);
}

/* Mostrar todo el inventario (incluye vendidos) */
void mostrarInventario(void) {
    FILE *f = fopen(VEHICULOS_FILE, "rb");
    if (!f) { printf("No se pudo abrir %s\n", VEHICULOS_FILE); return; }
    Vehiculo v;
    int found = 0;
    /* Encabezado de tabla */
    printf("%-10s | %-12s | %-15s | %10s | %-8s | %-10s\n", "Placa", "Tipo", "Marca", "Precio", "Estado", "Disponible");
    printf("-----------------------------------------------------------------------------------------\n");
    while (fread(&v, sizeof(Vehiculo), 1, f) == 1) {
        printf("%-10s | %-12s | %-15s | %10.2f | %-8s | %-10s\n",
               v.placa, v.tipo, v.marca, v.precio, v.estado, v.disponible ? "Si" : "No");
        found = 1;
    }
    if (!found) {
        printf("Inventario vacio.\n");
    }
    fclose(f);
}

/* Mostrar clientes en formato de tabla */
void mostrarClientes(void) {
    FILE *f = fopen(CLIENTES_FILE, "rb");
    if (!f) { printf("No se pudo abrir %s\n", CLIENTES_FILE); return; }
    Cliente c;
    int found = 0;
    printf("%-12s | %-30s | %-4s\n", "Cedula", "Nombre", "Edad");
    printf("---------------------------------------------------------------\n");
    while (fread(&c, sizeof(Cliente), 1, f) == 1) {
        printf("%-12s | %-30s | %-4d\n", c.cedula, c.nombre, c.edad);
        found = 1;
    }
    if (!found) printf("No hay clientes registrados.\n");
    fclose(f);
}

/* Mostrar historial de ventas en formato tabla */
void mostrarVentas(void) {
    FILE *f = fopen(VENTAS_FILE, "rb");
    if (!f) { printf("No se pudo abrir %s\n", VENTAS_FILE); return; }
    Venta v;
    int found = 0;
    printf("%-10s | %-10s | %-12s | %-20s | %10s\n", "ID", "Placa", "Cedula", "Vendedor", "Monto");
    printf("--------------------------------------------------------------------------\n");
    while (fread(&v, sizeof(Venta), 1, f) == 1) {
        printf("%-10s | %-10s | %-12s | %-20s | %10.2f\n", v.id_venta, v.placa_vehiculo, v.cedula_cliente, v.vendedor, v.monto_final);
        found = 1;
    }
    if (!found) printf("No hay ventas registradas.\n");
    fclose(f);
}
