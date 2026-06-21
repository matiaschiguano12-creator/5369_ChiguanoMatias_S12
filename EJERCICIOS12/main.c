#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]){

    int opc1 = 0;
    int opc2 = 0;
    Vehiculo vehiculo;
    Cliente cliente;
    Vendedor vendedor;

    do
    {
        opc1 = menuInterfaz();

        
            switch (opc1)
            {
            case 1:
                int opcT = 0;
                int opcT2 = 0;
                int opcMT = 0;

                opcMT = menuTrabajador();

                switch (opcMT)
                {
                case 1:

                    do {    
                        opcT = menuGestionVehiculos();

                        switch (opcT)
                        {
                        case 1:
                            
                            AgregarVehiculo();
                            
                            break;

                        case 2:

                            ConsultarVehiculo(&vehiculo);    

                            break;

                        case 3:

                            modificarVehiculo(&vehiculo);

                            break;

                        case 4:

                            consultarVehiculosPorPreferencias(vehiculo, cliente);

                            break;

                        case 5:

                            venderVehiculo(&vehiculo);

                            break;

                        case 6:

                            mostrarVehiculos();

                            break;

                        default:
                            break;
                        }
                
                    
                        printf("Desea seleccionar otra opccion en este menu? (1.Si / 2.No)");
                        printf(">>> ");
                        opcT2 = ValidarFloatRango(1,2);

                    }while (opcT2 == 1);

                case 2:
                    int opcMTC = 0;
                    int opcMTC2 = 0;
                    

                    do{

                        opcMTC = menuGestionClientes();

                        switch (opcMTC)
                        {
                        case 1:

                            AgregarCliente();

                            break;

                        case 2:

                            modificarCliente(&cliente);

                            break;

                        case 3: 

                            mostrarClientes();

                            break;
                        
                        default:
                            break;
                        }

                        printf("Desea Seleccionar otra opcion en este menu? ( 0 = SI, 1 = NO )\n");
                        printf(">>> ");

                        opcMTC2 = ValidarFloatRango(0,1);
                    } while (opcMTC2 == 0);
                
                    break;
                    
                case 3:

                    int opcMTT = 0;
                    int opcMTT2 = 0;

                    do{

                        opcMTT = menuGestionVendedores();

                        switch (opcMTT)
                        {
                        case 1:
                            
                            AgregarVendedor();

                            break;
                        
                        case 2:

                            editarVendedor();

                            break;
                    
                        case 3:
                        
                            mostrarVendedores();

                            break;

                        default:
                            break;
                        }

                        printf("Desea Seleccionar otra opcion en este menu? ( 0 = SI, 1 = NO )\n");
                        printf(">>> ");

                        opcMTT2 = ValidarFloatRango(0,1);
                    } while (opcMTT2 == 0);
            

                    break;

                default:
                    break;
                
                }
            
            case 2:

                int opcMC = 0;
        
                do
                {
                    opcMC = menuCliente();
                    
                    switch (opcMC)
                    {
                    case 1 :

                        mostrarVehiculos();

                        break;
                    
                    case 2:

                        consultarVehiculosPorPreferencias(vehiculo, cliente);
                    default:
                        break;
                    }
                    
                    printf("Desea Seleccionar otra opcion en este menu? ( 0 = SI, 1 = NO )\n");
                    printf(">>> ");

                    
                    opc2 = ValidarFloatRango(0,1);
                } while (opc2 == 0);
                
                break;
            default:
                break;
            }

        printf("Desea Seleccionar otra opcion ( 0 = SI, 1 = NO )");
        printf(">>> ");
        opc2 = ValidarFloatRango(0,1);
    } while (opc2 == 0);
    

    return 0;

}