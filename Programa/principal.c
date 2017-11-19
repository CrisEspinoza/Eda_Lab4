#include <stdio.h>
#include "funciones.c"
#include <string.h>
#include <locale.h>
#include <time.h>

int main()
{    
	// Se declaran las variables que se van a utilizar
    char nombre[50];
    char nombreBuscados[50];
    int opcion;
    Nodo* listaPersonas;
    listaPersonas = NULL; // Se inicializa la listaPersonas como nula
    Lista* listaPersonasABuscar;
    listaPersonasABuscar = NULL;
    Lista* auxListaPersonas = crearLista();
    int i,numeroABuscar;
    clock_t comienzo,final; //Declaramos las variables que nos permiten calcular el tiempo de ejecucion
    comienzo = time(NULL);
    
    do
    {
        printf( "\n   1. Cargar numeros telefonicos");
        printf( "\n   2. Mostrar los numeros telefonicos");
        printf( "\n   3. Mostrar el arbol avl (Opcion pedida en el enunciado)");
        printf( "\n   4. Cargar nombres");        
        printf( "\n   5. Mostrar los nombres a buscar");
        printf( "\n   6. Buscar numeros solicitados" );
        printf( "\n   7. Generar archivo " );
        printf( "\n   8. Creditos" );
        printf( "\n   9. Salir" );
        printf( "\n\n   Introduzca opcion (1-9): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: printf("Ingrese nombre del archivo a leer\n");
                    scanf("%s",nombre); // Se carga el nombre del archivo
                    listaPersonas = cargar(nombre); // Se lee el archivo y se almacena en momoria el grafo
                    break;

            case 2: if (listaPersonas != NULL)
            		{            	
                        inorden(listaPersonas); // Se muestra la listaPersonas
                    	break;
                    }
                    printf("Primero debe cargar alguna listaPersonas, elegir opcion 1 \n");
                    break;

            case 3: if (listaPersonas != NULL)
                    {               
                        inordenPedido(listaPersonas); // Se muestra la listaPersonas
                        break;
                    }
                    printf("Primero debe cargar alguna listaPersonas, elegir opcion 1 \n");
                    break;                 	

            case 4: printf("Ingrese nombre del archivo que contiene los nombres a buscar \n");
                    scanf("%s",nombreBuscados); // Se carga el nombre del archivo
                    listaPersonasABuscar = cargarNombresBuscados(nombreBuscados); // Se lee el archivo y se almacena en momoria el grafo
                    numeroABuscar = listaPersonasABuscar->largo;
                    break;

            case 5: if (listaPersonasABuscar != NULL)
                    {               
                        //Hacemos el llamado a la funcion que muestra la lista de personas
                        mostrarPersonasBuscadas(listaPersonasABuscar); // Se muestra la listaPersonas
                        break;
                    }
                    printf("Primero debe cargar alguna listaPersonasABuscar, elegir opcion 1 \n");
                    break; 

            case 6: for ( i = 0 ; i < numeroABuscar ; i++)
                    {
                        //Hacemos el llamado a la busqueda de cada uno de los nombres.
                        auxListaPersonas = personasBuscadas(listaPersonas,listaPersonasABuscar,i, auxListaPersonas);
                    }
                    final = time(NULL);
                    auxListaPersonas = arreglarLista(auxListaPersonas,listaPersonasABuscar,numeroABuscar);
                    printf("El tiempo final fue: %f \n", difftime(final,comienzo));
                    break;

            case 7: crearArchivo(auxListaPersonas,numeroABuscar-1); //Creamos el archivo con la repsuesta solicitada
                    break;

            case 8: printf(" * Autor: CRISTIAN EDUARDO ESPINOZA SILVA \n ");
                    printf(" * Universidad santiago de chile \n");
                    break;
        }

    }while(opcion!=9);

    return 0;
}
