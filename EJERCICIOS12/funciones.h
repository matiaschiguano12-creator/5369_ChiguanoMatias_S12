typedef struct {
    int id;
    char marca[30];
    char modelo[30];
    char uso[20]; // nuevo, usado
    int aniofabricacion;
    float precio;
    int disponibilidad; // 1 = disponible, 0 = vendido
    char color[20];
    char comprador[50];
} Vehiculo;

typedef struct {
    int nmrCedula; //ID
    char nombre[50];
    char apellido[50];
    int telefono;
    float presupuesto;
    char preferenciaMarca[20]; 
    char preferenciaUso[20]; 
    int preferenciaAnio; 
     
    char preferenciaColor[20]; 
} Cliente;

typedef struct {
    int nmrCedula; //ID
    char nombre[50];
    char apellido[50];
    int nmrventas;
} Vendedor;


void leerCadena (char *cadena, int n);
float ValidarFloatRango (float a, float b);
void AgregarVehiculo();
void ConsultarVehiculo(Vehiculo *vehiculo);
void modificarVehiculo(Vehiculo *vehiculo);
void guardarVehiculoDentroDelArchivo(Vehiculo *vehiculo);
int menuInterfaz();
int menuTrabajador();
int menuCliente();
int menuGestionVehiculos();
int menuGestionClientes();
int menuGestionVendedores();
void AgregarCliente();
void guardarClienteDentroDelArchivo(Cliente *cliente);
void modificarCliente(Cliente *cliente);
void venderVehiculo(Vehiculo *vehiculo);
void mostrarVehiculos();
void consultarVehiculosPorPreferencias(Vehiculo vehiculo, Cliente cliente);
void mostrarClientes();
void AgregarVendedor();
void editarVendedor();
void mostrarVendedores();
int CedulaYaRegistrada(int cedula);
int IdVehiculoYaRegistrada(int id);