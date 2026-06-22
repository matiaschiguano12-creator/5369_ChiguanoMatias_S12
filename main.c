#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]){

    int opc1 = 0;
    int opc2 = 0;
    int opc3 = 0;
    int opc4 = 0;
    int opc5 = 0;
    int opc6 = 0;
    int opc11 = 0;
    int opc12 = 0;
    int opc13 = 0;
    int opc14 = 0;
    int opc15 = 0;
    int opc16 = 0;

    Vehiculo vehiculo;
    Cliente cliente;
    Vendedor vendedor;

    do //opc1, opc2
    {
        opc1 = menuInterfaz();

        
            switch (opc1)
            {
            case 1:

                do{
                   
                    opc3 = menuTrabajador();

                    switch (opc3)
                    {
                    case 1:

                        do {    
                            opc5 = menuGestionVehiculos();

                            switch (opc5)
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
                    
                        
                            printf("Desea seleccionar otra opccion del menu de vehiculos? (1.Si / 2.No)\n");
                            printf(">>> ");
                            opc6 = ValidarFloatRango(1,2);

                        }while (opc6 == 1);

                        break;

                

                    case 2:

                        do{

                            opc11 = menuGestionClientes();

                            switch (opc11)
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

                            printf("Desea Seleccionar otra opcion del menu de clientes? ( 0 = SI, 1 = NO )\n");
                            printf(">>> ");

                            opc12 = ValidarFloatRango(0,1);
                        } while (opc12 == 1);
                    
                        break;
                        
                    case 3:


                        do{

                            opc13 = menuGestionVendedores();

                            switch (opc13)
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

                            printf("Desea Seleccionar otra opcion del menu de vendedores? ( 0 = SI, 1 = NO )\n");
                            printf(">>> ");

                            opc14 = ValidarFloatRango(0,1);
                        } while (opc14 == 0);
                

                        break;

                    default:
                        break;
                    
                    }

                    printf("Desea Seleccionar otra opcion del menu de trabajador( 0 = SI, 1 = NO )\n");
                    printf(">>> ");
                    opc4 = ValidarFloatRango(0,1);

                }while (opc4 == 0);
            
            case 2:
        
                do
                {
                    opc15 = menuCliente();
                    
                    switch (opc15)
                    {
                    case 1 :

                        mostrarVehiculos();

                        break;
                    
                    case 2:

                        consultarVehiculosPorPreferencias(vehiculo, cliente);
                    default:
                        break;
                    }
                    
                    printf("Desea Seleccionar otra opcion del menu Clientela ( 0 = SI, 1 = NO )\n");
                    printf(">>> ");

                    
                    opc16 = ValidarFloatRango(0,1);
                } while (opc16 == 0);
                
                break;
            default:
                break;
            }

        printf("Desea entrar como Trabajador o cliente ( 1 =  TRABAJADOR, 2 = CLIENTE )\n");
        printf(">>> ");
        opc2 = ValidarFloatRango(1,2);
    } while (opc2 == 1);
    

    return 0;

}