#include <stdio.h>
#include "struct.h"
#include <string.h>
#include <stdlib.h>
#include <locale.h>

Nodo* cargar(char nombre[])
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de entrada.

    archivo = fopen (nombre, "r"); // Estamos abriendo el archivo en modo lectura

    Nodo* listaPersonas = NULL;
    int cantidadDePeronas;
    fscanf(archivo, "%d", &cantidadDePeronas);

    //Declaramos cada una de las variables a utilizar y le asignamos memoria 
    char *primerNombre;
    primerNombre = (char*)calloc(100,sizeof(char));
    char *segundoNombre;
    segundoNombre = (char*)calloc(100,sizeof(char));
    char *primerApellido;
    primerApellido = (char*)calloc(100,sizeof(char));
    char *segundoApellido;
    segundoApellido = (char*)calloc(100,sizeof(char));
    char *parte1;
    parte1 = (char*)calloc(20,sizeof(char));
    char *parte2;
    parte2 = (char*)calloc(20,sizeof(char));
    char *parte3;
    parte3 = (char*)calloc(20,sizeof(char));
    char *parte4;
    parte4 = (char*)calloc(20,sizeof(char));
    char *numero;
    numero = (char*)calloc(100,sizeof(char));

    struct Informacion* auxNodo;
    int contador = 0 ;

    //Hacemos un ciclo, que lea el archivo hasta que llegue hasta el final de el
    while (!feof(archivo)) 
    {
        //Capturamos el contenido del arhivo y lo almacenamos dentro de las variables corresondientes
        fscanf(archivo, "%s %s %s %s %s %s %s %s",primerNombre,segundoNombre,primerApellido,segundoApellido,parte1,parte2,parte3,parte4);
        //Creamos el numero concatenado
        numero = strcat(strcat(parte1,parte2),strcat(parte3,parte4));
        //Creamos el nodo que contendra la informacion capturada
        auxNodo = crearInformacion(primerNombre,segundoNombre,primerApellido,segundoApellido,numero); // Creamos un nuevo nodo con lo caputrado desde el archivo
        // Empezamos a crear el arbol binario ordenado desde un principio 
        listaPersonas = agregarNodo(listaPersonas,auxNodo);
    }
    fclose(archivo); // Cerramos el archivo
 
    return listaPersonas;
}

void mostrarPersonasBuscadas(Lista *lista)
{
	int j;
    //Hacemos un ciclo for que dure hasta el largo de la lista, con le fin de mostrar cada una de las personas que estan contenidas
    //dentro de ella
    for (j = 0; j < lista->largo-1; j++)
    {
        printf("%s ", lista->nodo[j].info->primerNombre);
        printf("%s ", lista->nodo[j].info->segundoNombre);
        printf("%s ", lista->nodo[j].info->primerApellido);
        printf("%s ", lista->nodo[j].info->segundoApellido);
        printf("El numero es: %s ", lista->nodo[j].info->numero);   
        printf("%s ", lista->nodo[j].info->nombreCompleto);
        printf("\n");
    }   
}

Lista* cargarNombresBuscados(char nombre[])
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de entrada.

    archivo = fopen (nombre, "r"); // Estamos abriendo el archivo en modo lectura

    int cantidadDePeronas;
    fscanf(archivo, "%d", &cantidadDePeronas);

    //Pedimos memoria para cada una de las variables que vamos a utilizar
    char *primerNombre;
    primerNombre = (char*)calloc(100,sizeof(char));
    char *segundoNombre;
    segundoNombre = (char*)calloc(100,sizeof(char));
    char *primerApellido;
    primerApellido = (char*)calloc(100,sizeof(char));
    char *segundoApellido;
    segundoApellido = (char*)calloc(100,sizeof(char));

    struct Nodo* auxNodo = crearNodo();
    int contador = 0 ;
    Lista* listaPersonas = crearLista();

    //Hacemos un ciclo, que lea el archivo hasta que llegue hasta el final de el
    while (!feof(archivo)) 
    {
        //Leemos todo el contednio del archivo y lo almacenados dentro de las variables correspondientes
        fscanf(archivo, "%s %s %s %s",primerNombre,segundoNombre,primerApellido,segundoApellido);
        // Creamos la informacion de noso y la almacenamos en el 
        auxNodo->info = crearInformacion(primerNombre,segundoNombre,primerApellido,segundoApellido,""); // Creamos un nuevo nodo con lo caputrado desde el archivo
        // Agregamos a la lista cada una de los nombres rescatados desde el archivo 
        agregarNodoLista(listaPersonas,auxNodo);
        contador++;
    }
    fclose(archivo); // Cerramos el archivo
 
    return listaPersonas;
}

Lista* crearLista() // Creamos la lista nueva 
{
    Lista* lista = (Lista*)malloc(sizeof(Lista)); // Pedimos memoria para la nueva lista 
    lista->nodo = NULL;
    lista->largo = 0 ; // El largo de la lista es igual a "0".
    return lista; // Se retorna la lista creada
}

Lista* agregarNodoLista(Lista* lista , Nodo* aux)
{
    if(lista->largo == 0) //Verificamos si el largo de la lista si es 0
    {
        //Pedimos memoria y asignamos directamente altiro el valor rescatado 
        lista->nodo = (Nodo*)malloc(sizeof(Nodo));
        lista->nodo[0] = *aux;
    }
    else
    {
        //Pedimos nuevament memoria para la lista y hacemos que su largo aumente para poder agregar el nuevo valor 
        lista->nodo = (Nodo*)realloc(lista->nodo, (lista->largo + 1) * sizeof (Nodo)); // Pedimos mas memoria para el arreglo creado
        lista->nodo[lista->largo] = *aux; // Agregamos el nodo que se desea agregar, luego de haber solicitado memoria
    }
    lista->largo++; // aumnetamos el largo de la lista de arreglos
    return lista;
}

Informacion* crearInformacion(char *primerNombre, char *segundoNombre, char *primerApellido,
 char *segundoApellido, char *numero)
{
    //Pedimos memoria para el nuevo nodo 
    Informacion* nuevoNodo = (Informacion*)malloc(sizeof(Informacion)); // Pedimos memoria para el nuevo nodo declarado   
    
    //Declaramos la nueva variable a utilizar
    char *nombreCompleto;
    nombreCompleto = (char*)calloc(100,sizeof(char));

    if (nuevoNodo != NULL)
    {
        //Copiamos el contenido recibido a cada una de las variables que estamos creando 
        strcpy(nuevoNodo->primerNombre,primerNombre);
        strcpy(nuevoNodo->segundoNombre,segundoNombre);
        strcpy(nuevoNodo->primerApellido,primerApellido);
        strcpy(nuevoNodo->segundoApellido,segundoApellido);
        strcpy(nuevoNodo->numero,numero);
        nombreCompleto = strcat(strcat(primerNombre,segundoNombre),strcat(primerApellido,segundoApellido));
        strcpy(nuevoNodo->nombreCompleto,nombreCompleto);
        nuevoNodo->bandera = 0;        
    }
    return nuevoNodo; // Se retorna el nuevo nodo creado
}

Lista* personasBuscadas(Nodo* listaPersonas, Lista* listaPersonasABuscar, int contador, Lista* auxLista)
{
    //Verificamos si el nombre que andamos buscando es el correcto, verificanod cada uno de sus nombres
    if (listaPersonas != NULL)
    {
        if (strcmp(listaPersonas->info->primerNombre,listaPersonasABuscar->nodo[contador].info->primerNombre) == 0 &&
            strcmp(listaPersonas->info->segundoNombre,listaPersonasABuscar->nodo[contador].info->segundoNombre) == 0 &&
            strcmp(listaPersonas->info->primerApellido,listaPersonasABuscar->nodo[contador].info->primerApellido) == 0 &&
            strcmp(listaPersonas->info->segundoApellido,listaPersonasABuscar->nodo[contador].info->segundoApellido) == 0 )
        {
            //Agregamos el nuevo nodo a la lista, el cual va a contener el numero telefonico 
            auxLista = agregarNodoLista(auxLista,listaPersonas);
        }

        if (mayor(listaPersonas->info,listaPersonasABuscar->nodo[contador].info) == 1)
        {
            //Llamamos recursivamente hasta poder recorrer el arbol completo 
            personasBuscadas(listaPersonas->hijoDerecho,listaPersonasABuscar,contador,auxLista);
        }
        else
        {
            //Llamamos recursivamente hasta poder recorrer el arbol completo 
            personasBuscadas(listaPersonas->hijoIzquierdo,listaPersonasABuscar,contador,auxLista);
        }        
    }
    return auxLista; // Retornamos la nueva lista, con los numero de las personas enontradas 
}

Lista* arreglarLista(Lista* lista, Lista* listaPersonas, int largoLista)
{
    //Declaramos cada una de las variables 
    char *numero;
    numero = (char*)calloc(100,sizeof(char));
    int i,j;

    for (i = 0; i < largoLista; i++)
    {
        for (j = 0; j < lista->largo; j++)
        {
        //Hacemos una comparación para verificar si es el primer numero encontrado o otro, con el fin de agregarlo al archivo
        //con un " - ". 
            if (strcmp(listaPersonas->nodo[i].info->nombreCompleto,lista->nodo[j].info->nombreCompleto) == 0 &&
                listaPersonas->nodo[i].info->bandera == 1)
            {
                numero = strcat( strcat(numero," - ") ,lista->nodo[j].info->numero );
            }

            if (strcmp(listaPersonas->nodo[i].info->nombreCompleto,lista->nodo[j].info->nombreCompleto) == 0 && 
                listaPersonas->nodo[i].info->bandera == 0)
            {
                listaPersonas->nodo[i].info->bandera = 1;
                numero = strcat(numero,lista->nodo[j].info->numero);
            }        
        }
        //Realizamos el reemplazo en el numero y volvemoa a pedir memoria para el siguiente numero
        strcpy(listaPersonas->nodo[i].info->numero,numero);
        numero = (char*)calloc(100,sizeof(char));
    }
    return listaPersonas; // Retornamos la lista con los numeros actualizados
}

int mayor(Informacion* aux, Informacion* aux1 )
{
    //Declaramos las variables a utilizar 
    int largoMinimo;

    //Verificamos si alguno de los ombres ta nulo, para devolver el largo de la otra palabra
    if (aux == NULL)
    {
        return 0;
    }

    if (aux1 == NULL)
    {
        return 1;
    }
    //Verificamos cual de las palabras es mas larga y devolvemos la contraria 
    if (strlen(aux->nombreCompleto) > strlen(aux1->nombreCompleto) )
    {
        //Devolvemos la palabra de menor largo
        largoMinimo = strlen(aux1->nombreCompleto);
    }
    else
    {
        //Devolvemos la palabra de menor largo
        largoMinimo = strlen(aux->nombreCompleto);
    }

    int i ;

    for (i = 0 ; i < largoMinimo ; i++)
    {
        //Vamos verificando caracter a caracter cual es mayor que el otro, para poder tener el orden alfabeticamente dentor del arbol
        if (aux->nombreCompleto[i] > aux1->nombreCompleto[i])
        {
            return 1;
        }

        if (aux1->nombreCompleto[i] > aux->nombreCompleto[i])
        {
            return 0;
        }
    }
    return 0; //Retornamos 0, si ninguna de las anteriores opciones se cumple 
}

Nodo* agregarNodo(Nodo *arbol, Informacion* dato)
{
    //Vrificamos si el arbole sta nulo
    if(arbol == NULL)
    {
        //Empezamos a creae el nuevo arbol, con el nuevo nodo raiz
        arbol = crearNodo();        
        arbol->info = dato;
        arbol->largo++;
        return arbol;
    }

    else
    {
        if(mayor(arbol->info, dato) == 1)
        {
            //Agregamos el nuevo nodo al hijo correspndiente
            arbol->hijoDerecho = agregarNodo(arbol->hijoDerecho, dato);
            return arbol;
        }

        else
        {
            //Agregamos el nuevo nodo al hijo correspndiente
            arbol->hijoIzquierdo = agregarNodo(arbol->hijoIzquierdo, dato);
            return arbol;
        }
    }    
}

Nodo* crearNodo() // Creamos la lista nueva 
{
    Nodo* nodo = malloc(sizeof *nodo); // Pedimos memoria para la nueva nodo 
    if (nodo != NULL)
    {
        nodo->info = (Informacion*)malloc(sizeof(Informacion));
        nodo->hijoDerecho = NULL;
        nodo->hijoIzquierdo = NULL;
        nodo->largo = 0 ;
    } 
    return nodo; // Se retorna la lista creada
}

void inorden(Nodo *arbol)
{
    //Verificamos que no este nulo el arbol 
    if(arbol != NULL)
    {
        //Mostramos cada uno d los hijos del arbol, haciendo un llamado recursivo a los demas hijos restantes
        inorden(arbol->hijoDerecho);
        printf("%s ", arbol->info->primerNombre);
        printf("%s ", arbol->info->segundoNombre);
        printf("%s ", arbol->info->primerApellido);
        printf("%s ", arbol->info->segundoApellido);
        printf("%s ", arbol->info->numero);        
        printf("  %s ", arbol->info->nombreCompleto);
        printf("\n");
        inorden(arbol->hijoIzquierdo);
    }
}

int largoMenor(Informacion* palabra1, Informacion* palabra2)
{
    //Declaramos las variables a utilizar dentro de la fucnoin
    int largoMinimo = 0;
    //Verificamos los casos primarios, para poder ahorrar las compraciones dentro de nuestro codigo(posibles casos basicos)
    if ((palabra1->nombreCompleto == NULL) && (palabra2->nombreCompleto != NULL))
    {
        largoMinimo = strlen(palabra2->nombreCompleto);
    }

    else if ((palabra2->nombreCompleto == NULL) && (palabra1->nombreCompleto != NULL))
    {
        largoMinimo = strlen(palabra1->nombreCompleto);
    }

    else 
    {
        //Verificamos cual de la dos palabras es mayor que la otra 
        if (strlen(palabra1->nombreCompleto) > strlen(palabra2->nombreCompleto))
        {
            //Devolvermos el largo de la menor palabra de las comparadas
            largoMinimo = strlen(palabra2->nombreCompleto);
        }
        else
        {
            //Devolvermos el largo de la menor palabra de las comparadas
            largoMinimo = strlen(palabra1->nombreCompleto);
        }
    }

    return largoMinimo; //Retornamos el valor minimo de las dos palabras
}

void crearArchivo (Lista* listaPersonas,int largo)
{
    FILE *txt;  // Incialzamos una variable de tipo FILE para poder trabajar con los archivos

    txt = fopen("TelefonosEncontrados.out", "wt"); // Abrimos le archivo en modo escritura y que se cree si no exite el archivo nombrado
	//Declaramos las variables a utilizar dentro de la funcion
    int i;
    for (i = 0 ; i < largo ; i++)
    {
        //Ingresamos los datos al archivo en el orden pedido 
        fprintf(txt,"%s %s %s %s: %s ",listaPersonas->nodo[i].info->primerNombre,listaPersonas->nodo[i].info->segundoNombre,
        listaPersonas->nodo[i].info->primerApellido,listaPersonas->nodo[i].info->segundoApellido,listaPersonas->nodo[i].info->numero); // Se escribe la ruta minima en el archivo
        fprintf(txt,"\n"); //Realizamos un nuevo salto de linea, con el fin de mantener el orden dentro del archivo
    }
    fclose(txt); // Cerramos el archivo
}
