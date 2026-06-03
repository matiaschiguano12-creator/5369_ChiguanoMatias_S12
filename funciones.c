#include <stdio.h>
#include "funciones.h"
#include <string.h>

#define MAX_LIBROS 10

int menu() {
    int opc = 0;
    printf("\n--- MENU BIBLIOTECA ---\n");
    printf("1. Agregar libro\n");
    printf("2. Mostrar libros\n");
    printf("3. Buscar libro\n");
    printf("4. Actualizar estado\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
    printf("Elige una opcion: ");
    opc = validarIntRango(1, 6);
    return opc;
}


int validarIntRango(int a, int b) {
    int n = 0;
    int aux = 0;
    do {
        aux = scanf("%d", &n);
        if (aux != 1 || n < a || n > b) {
            printf("Numero no valido. Ingrese nuevamente:\n");
            while (getchar() != '\n'); // limpia el buffer
        }
    } while (aux != 1 || n < a || n > b);
    return n;
}



void RegistrarLibro(RequerimientosLibro biblioteca[], int *cantidad) {
    if (*cantidad >= MAX_LIBROS) {
        printf("No se pueden agregar mas libros.\n");
        return;
    }

    RequerimientosLibro Libros;

    // Limpieza del buffer antes de leer texto (por el Enter del menu)
    while (getchar() != '\n' && !feof(stdin));

    printf("Ingrese ID: ");
    fgets(Libros.id, sizeof(Libros.id), stdin);
    Libros.id[strcspn(Libros.id, "\n")] = '\0';

    printf("Ingrese titulo: ");
    fgets(Libros.titulo, sizeof(Libros.titulo), stdin);
    Libros.titulo[strcspn(Libros.titulo, "\n")] = '\0';

    printf("Ingrese autor: ");
    fgets(Libros.autor, sizeof(Libros.autor), stdin);
    Libros.autor[strcspn(Libros.autor, "\n")] = '\0';

    printf("Ingrese anio de publicacion: ");
    Libros.anioPublicacion = validarIntRango(0, 2026);

    // Limpieza del buffer despues de leer numero
    while (getchar() != '\n' && !feof(stdin));

    strcpy(Libros.estado, "Disponible");

    biblioteca[*cantidad] = Libros;
    (*cantidad)++;

    printf("Libro agregado correctamente.\n");
    printf("Cantidad de libros registrados: %d\n", *cantidad);
}




void mostrarLibros(RequerimientosLibro biblioteca[], int cantidad) { //No se crea un arreglo nuevo, se utiliza el existente de main
                                                                     //Int CANTIDAD ahora no es puntero ya que solo se necesita leer su valor, no modificarlo
    if (cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", "ID", "Título", "Autor", "Año", "Estado"); //Que hacen los porsentajes
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        printf("%s\t\t%s\t\t%s\t\t%d\t\t%s\n",
               biblioteca[i].id,
               biblioteca[i].titulo,
               biblioteca[i].autor,
               biblioteca[i].anioPublicacion,
               biblioteca[i].estado);
    }
}

void buscarLibro(RequerimientosLibro biblioteca[], int cantidad) {
    if (cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("Buscar libro por titulo o por ID?\n");
    printf("Para ID selecione 1 Para titulo Seleccione 2\n");
    printf(">>> ");
    int opc1 = 0;

    opc1 = validarIntRango(1,2);

    switch (opc1) 
    {
        case 1:
            char id[10]; //DEFINE PARA Q EL USUARO INGRESE Y ESE Y ID SEA COMPARADO POR LOS DEMAS 
            printf("Ingrese ID del libro:\n");
            printf(">>> ");
            fgets(id, 10, stdin);
            id[strcspn(id, "\n")] = '\0';

            for (int i = 0; i < cantidad; i++) {
                if (strcmp(biblioteca[i].id, id) == 0) {
                printf("Título: %s\nAutor: %s\nAño: %d\nEstado: %s\n",
                    biblioteca[i].titulo,
                    biblioteca[i].autor,
                    biblioteca[i].anioPublicacion,
                    biblioteca[i].estado);
                    return;
                }
            }
        
            printf("Libro no encontrado.\n");
        
            
            break;

        case 2:
            char titulo[100];
            printf("Ingrese Titulo del libro:\n");
            printf(">>> ");
            fgets(titulo, 100, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            for (int i = 0; i < cantidad; i++) {
                if (strcmp(biblioteca[i].titulo, titulo) == 0) {
                printf("Título: %s\nAutor: %s\nAño: %d\nEstado: %s\n",
                    biblioteca[i].titulo,
                    biblioteca[i].autor,
                    biblioteca[i].anioPublicacion,
                    biblioteca[i].estado);
                    return;
                }
            }

            printf("Libro no encontrado.\n");

            break;
    
        default: printf("Opcion No valida\n");
         
    }
    
    
}


void actualizarEstado(RequerimientosLibro biblioteca[], int cantidad) {

    if (cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("Buscar libro por titulo o por ID?\n");
    printf("Para ID selecione 1 Para titulo Seleccione 2\n");
    printf(">>> ");
    int opc1 = 0;

    opc1 = validarIntRango(1,2);

    switch (opc1) 
    {
        case 1:
            char id[10]; //DEFINE PARA Q EL USUARO INGRESE Y ESE Y ID SEA COMPARADO POR LOS DEMAS 
            printf("Ingrese ID del libro:\n");
            printf(">>> ");
            fgets(id, 10, stdin);
            id[strcspn(id, "\n")] = '\0';

            for (int i = 0; i < cantidad; i++) {
                if (strcmp(biblioteca[i].id, id) == 0) {//Elementos a comparar ==0 es si coninciden
                    char respuesta;//la respuesta del usuario a querer cambiar de estado el libro
                    printf("El libro está actualmente '%s'. ¿Desea cambiar su estado? (s/n): ", biblioteca[i].estado);
                    scanf(" %c", &respuesta);
                    
                    if (respuesta == 's' || respuesta == 'S') {
                        if (strcmp(biblioteca[i].estado, "Disponible") == 0)
                            strcpy(biblioteca[i].estado, "Prestado");
                        else
                            strcpy(biblioteca[i].estado, "Disponible");
                
                        printf("Estado actualizado a: %s\n", biblioteca[i].estado);
                    } else {
                        printf("No se realizó ningún cambio.\n");
                    }
                    return;
                }
            }
            
            printf("Libro no encontrado.\n");
            
            break;

        case 2:
            char titulo[100];
            printf("Ingrese Titulo del libro:\n");
            printf(">>> ");
            fgets(titulo, 100, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            for (int i = 0; i < cantidad; i++) {
                if (strcmp(biblioteca[i].titulo, titulo) == 0) {//Elementos a comparar ==0 es si coninciden
                    char respuesta;//la respuesta del usuario a querer cambiar de estado el libro
                    printf("El libro está actualmente '%s'. ¿Desea cambiar su estado? (s/n): ", biblioteca[i].estado);
                    scanf(" %c", &respuesta);
                    

                    if (respuesta == 's' || respuesta  == 'S') {
                        if (strcmp(biblioteca[i].estado, "Disponible") == 0)
                            strcpy(biblioteca[i].estado, "Prestado");
                        else
                            strcpy(biblioteca[i].estado, "Disponible");
                
                        printf("Estado actualizado a: %s\n", biblioteca[i].estado);
                    } else {
                        printf("No se realizó ningún cambio.\n");
                    }
                    return;
                }
            }
            break;
    
        default: printf("Opcion No valida\n");    
    }
}


void eliminarLibro(RequerimientosLibro biblioteca[], int *cantidad) {

    if (cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("Buscar libro por titulo o por ID?\n");
    printf("Para ID selecione 1 Para titulo Seleccione 2\n");
    printf(">>> ");
    int opc1 = 0;

    opc1 = validarIntRango(1,2);

    switch (opc1) 
    {
        case 1:
            char id[10]; //DEFINE PARA Q EL USUARO INGRESE Y ESE Y ID SEA COMPARADO POR LOS DEMAS 
            printf("Ingrese ID del libro:\n");
            printf(">>> ");
            fgets(id, 10, stdin);
            id[strcspn(id, "\n")] = '\0';

            for (int i = 0; i < *cantidad; i++) {
                if (biblioteca[i].id == id) {
                    for (int j = i; j < *cantidad - 1; j++) {
                        biblioteca[j] = biblioteca[j + 1];
                    }
                    (*cantidad)--;
                    printf("Libro eliminado correctamente.\n");
                    return;
                }
            }
            printf("Libro no encontrado.\n");
           
        
            break;

        case 2:
            char titulo[100];
            printf("Ingrese Titulo del libro:\n");
            printf(">>> ");
            fgets(titulo, 100, stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            for (int i = 0; i < *cantidad; i++) {
                if (biblioteca[i].titulo == titulo) {
                    for (int j = i; j < *cantidad - 1; j++) {
                        biblioteca[j] = biblioteca[j + 1];
                    }
                    (*cantidad)--;
                    printf("Libro eliminado correctamente.\n");
                    return;
                }
            }
            printf("Libro no encontrado.\n");

            break;
    
        default: printf("Opcion No valida\n");
         
    }
}