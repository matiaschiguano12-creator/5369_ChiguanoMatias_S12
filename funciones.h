#define MAX_LIBROS 10

typedef struct {
    char id [10];
    char titulo [100];
    char autor [50];
    int anioPublicacion;
    char estado [10];
} RequerimientosLibro;

int menu ();//menu
int validarIntRango (int a, int b);//validacion
void RegistrarLibro(RequerimientosLibro biblioteca[], int *cantidad);//#1
void mostrarLibros(RequerimientosLibro biblioteca[], int cantidad);//#2
void buscarLibro(RequerimientosLibro biblioteca[], int cantidad);//#3
void actualizarEstado(RequerimientosLibro biblioteca[], int cantidad);//#4
void eliminarLibro(RequerimientosLibro biblioteca[], int *cantidad);//#5