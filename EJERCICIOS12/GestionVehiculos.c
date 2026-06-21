#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menuGestionVehiculos(){

    int opc;
    printf("Menu:\n");
    printf("1. Agregar Vehiculo\n");
    printf("2. Consultar Vehiculo\n");
    printf("3. Modificar Vehiculo\n");
    printf("4. Buscar Vehiculo por preferencias\n"); 
    printf("5. Vender Vehiculo\n");
    printf("6. Mostrar Vehiculos\n");
    printf(">>> ");
    opc = ValidarFloatRango(1, 6);
    return opc;
}

void AgregarVehiculo() {
    Vehiculo vehiculo;

    printf("Ingrese el ID del vehiculo (SOLO NUMEROS): ");
    vehiculo.id = ValidarFloatRango(1, 1000);

    // Verificar si el ID ya existe
    if (IdVehiculoYaRegistrada(vehiculo.id)) {
        printf("\n El vehículo con ID %nf ya está registrado.\n", vehiculo.id);
        return; // Salir sin guardar
    }

    printf("Ingrese la marca del vehiculo: ");
    leerCadena(vehiculo.marca, 30);

    printf("Ingrese el modelo del vehiculo: ");
    leerCadena(vehiculo.modelo, 30);

    printf("Ingrese el uso del vehiculo (nuevo/usado): ");
    leerCadena(vehiculo.uso, 20);

    printf("Ingrese el anio de fabricacion del vehiculo: ");
    vehiculo.aniofabricacion = ValidarFloatRango(1900, 2024);

    printf("Ingrese el precio del vehiculo: ");
    vehiculo.precio = ValidarFloatRango(0, 1000000);

    vehiculo.disponibilidad = 0; // 0 = disponible, 1 = vendido

    printf("Ingrese el color del vehiculo: ");
    leerCadena(vehiculo.color, 20);

    guardarVehiculoDentroDelArchivo(&vehiculo);
}

int IdVehiculoYaRegistrada(int id) {
    FILE *f = fopen("vehiculos.dat", "rb");
    if (f == NULL) {
        return 0; // Si el archivo no existe, no hay registros
    }

    Vehiculo vehiculo;
    while (fread(&vehiculo, sizeof(Vehiculo), 1, f)) {
        if (vehiculo.id == id) {
            fclose(f);
            return 1; // ID encontrada
        }
    }

    fclose(f);
    return 0; // No encontrada
}

void guardarVehiculoDentroDelArchivo(Vehiculo *vehiculo){

    FILE *f = fopen("vehiculos.dat", "ab+");

    if (f == NULL){ // Verificar si el archivo se abrió correctamente
        printf("Error al abrir el archivo\n");
        return;
    
    }

    fwrite(vehiculo, sizeof(Vehiculo), 1, f);

    fclose(f);
}

void ConsultarVehiculo(Vehiculo *vehiculo){

    int id;
    printf("Ingrese el ID del vehiculo que desea consultar: ");
    id = ValidarFloatRango(1, 1000);

    FILE *f = fopen("vehiculos.dat", "rb+");

    if (f == NULL){ // Verificar si el archivo se abrió correctamente
        printf("Error al abrir el archivo\n");
        return;
    
    }

    while (fread(vehiculo, sizeof(Vehiculo), 1, f) == 1){
        if (vehiculo->id == id){
            printf("ID: %d\n", vehiculo->id);
            printf("Marca: %s\n", vehiculo->marca);
            printf("Modelo: %s\n", vehiculo->modelo);
            printf("Uso: %s\n", vehiculo->uso);
            printf("Anio de fabricacion: %d\n", vehiculo->aniofabricacion);
            printf("Precio: %.2f\n", vehiculo->precio);
            printf("Disponibilidad: %s\n", vehiculo->disponibilidad = 0);
            if (vehiculo->disponibilidad = 0){
                printf("Disponible\n");
            } else {
                printf("Vendido a: %s\n", vehiculo->comprador);
            }
            printf("Color: %s\n", vehiculo->color);
            break;
        }
    }

    fclose(f);

}

void modificarVehiculo(Vehiculo *vehiculo){

    FILE *f = fopen("vehiculos.dat", "rb+"); // abrir para lectura y escritura binaria
    if (f == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    int opcion1;
    int opcion2 = 0;
    
    int idBuscado;
    int encontrado = 0;

    printf("Ingrese el ID del vehiculo a editar: ");
    idBuscado = ValidarFloatRango(1, 1000);

    while (fread(vehiculo, sizeof(Vehiculo), 1, f) == 1){
        if (vehiculo->id == idBuscado){
            encontrado = 1;
            printf("\nVehiculo encontrado:\n");
            printf("Marca: %s\nModelo: %s\nUso: %s\nAño: %d\nPrecio: %.2f\nColor: %s\n",
                   vehiculo->marca, vehiculo->modelo, vehiculo->uso,
                   vehiculo->aniofabricacion, vehiculo->precio, vehiculo->color);

            do {
                printf("\n--- MENU DE EDICION ---\n");
                printf("1. Editar marca\n");
                printf("2. Editar modelo\n");
                printf("3. Editar uso\n");
                printf("4. Editar aNIOo de fabricación\n");
                printf("5. Editar precio\n");
                printf("6. Editar color\n");
                printf(">>> ");
                opcion1 = ValidarFloatRango(1, 6);
            

                switch(opcion1){
                    case 1:
                        printf("Nueva marca: ");
                        leerCadena(vehiculo->marca, 30);
                        break;
                    case 2:
                        printf("Nuevo modelo: ");
                        leerCadena(vehiculo->modelo, 30);
                        break;
                    case 3:
                        printf("Nuevo uso (nuevo/usado): ");
                        leerCadena(vehiculo->uso, 20);
                        break;
                    case 4:
                        printf("Nuevo año de fabricación: ");
                        vehiculo->aniofabricacion = ValidarFloatRango(1900, 2024);
                        break;
                    case 5:
                        printf("Nuevo precio: ");
                        vehiculo->precio = ValidarFloatRango(0, 1000000);
                        break;
                    case 6:
                        printf("Nuevo color: ");
                        leerCadena(vehiculo->color, 20);
                        break;
                    
                    default:
                        printf("Opción inválida.\n");
                        break;
                }

                
                fseek(f, sizeof(Vehiculo), SEEK_SET);
                fwrite(vehiculo, sizeof(Vehiculo), 1, f);
                
                printf("Desea seleccionar otra opcion a editar? (1 = si, 0 = no): ");
                opcion2 = ValidarFloatRango(0, 1);

            } while(opcion2 == 1);

        }
    }

    if (encontrado == 0) {
        printf("No se encontró un vehículo con ese ID.\n");
    }

    fclose(f);
}

void venderVehiculo(Vehiculo *vehiculo) {
    FILE *f = fopen("vehiculos.dat", "r+b"); 
    if (f == NULL) {
        printf("Error al abrir el archivo de vehículos\n");
        return;
    }

    int idBuscado;
    int encontrado = 0;

    printf("Ingrese el ID del vehículo a vender: ");
    idBuscado = ValidarFloatRango(1, 1000);

    while (fread(vehiculo, sizeof(Vehiculo), 1, f) == 1) {
        if (vehiculo->id == idBuscado) {
            encontrado = 1;

            if (vehiculo->disponibilidad == 0) {
                printf("El vehículo ya ha sido vendido a: %s\n", vehiculo->comprador);
                break;
            }

            int numeroCedulaComprador;
            printf("Ingrese la cédula del comprador: ");
            numeroCedulaComprador = ValidarFloatRango(1000000, 999999999);

            int cedulaVendedor;
            printf("Ingrese la cédula del vendedor encargado: ");
            cedulaVendedor = ValidarFloatRango(1000000, 999999999);

            
            vehiculo->disponibilidad = 0;
            sprintf(vehiculo->comprador, "%d", numeroCedulaComprador);

            
            fseek(f, sizeof(Vehiculo), SEEK_SET);
            fwrite(vehiculo, sizeof(Vehiculo), 1, f);

            fclose(f);

            // Actualizar número de ventas del vendedor
            FILE *v = fopen("vendedores.dat", "r+b");
            if (v == NULL) {
                printf("Error al abrir vendedores.dat\n");
                return;
            }

            Vendedor vendedor;
            int vendedorEncontrado = 0;

            while (fread(&vendedor, sizeof(Vendedor), 1, v) == 1) {
                if (vendedor.nmrCedula == cedulaVendedor) {
                    vendedorEncontrado = 1;
                    vendedor.nmrventas++; // incrementar ventas
                    fseek(v, sizeof(Vendedor), SEEK_SET);
                    fwrite(&vendedor, sizeof(Vendedor), 1, v);
                    printf("\nVenta registrada por el vendedor: %s %s\n", vendedor.nombre, vendedor.apellido);
                    break;
                }
            }
            fclose(v);

            if (!vendedorEncontrado)
                printf("No se encontró un vendedor con esa cédula.\n");

            printf("\n Vehículo vendido correctamente.\n");
            printf("Comprador: %d | Vendedor: %d\n", numeroCedulaComprador, cedulaVendedor);
            return;
        }
    }

    if (encontrado == 0)
        printf("No se encontró un vehículo con ese ID.\n");

    fclose(f);
}

void mostrarVehiculos(){
    FILE *f = fopen("vehiculos.dat", "rb");
    if (f == NULL){
        printf("Error al abrir el archivo de vehículos\n");
        return;
    }

    Vehiculo vehiculo;
    printf("\n--- LISTA DE VEHICULOS ---\n");
    while (fread(&vehiculo, sizeof(Vehiculo), 1, f)){
        printf("ID: %d | Marca: %s | Modelo: %s | Uso: %s | Año: %d | Precio: %.2f | Color: %s | Disponibilidad: %s\n",
               vehiculo.id, vehiculo.marca, vehiculo.modelo, vehiculo.uso,
               vehiculo.aniofabricacion, vehiculo.precio, vehiculo.color,
               vehiculo.disponibilidad == 0 ? "Disponible" : "Vendido");
    }

    fclose(f);
}
