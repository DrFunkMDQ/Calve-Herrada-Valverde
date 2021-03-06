#include "Peliculas.H"
///STPELICULA
stPelicula modificaPelicula(nodoArbol *arbolActivo, nodoArbol *arbolEliminado, stPelicula pelicula)
{
    int opcion;

    printf("Ingrese el campo a modificar\n");
    printf("1_NOMBRE\n2_DIRECTOR\n3_GENERO\n4_PAIS\n5_ANIO\n6_VALORACION\n7_PM\n8_URL\n");
    scanf("%d", &opcion);
    switch(opcion)
    {
    case 1:
        insertarNombre(arbolActivo, arbolEliminado, &pelicula.nombrePelicula);
        break;
    case 2:
        insertarTexto(pelicula.director);
        break;
    case 3:
        insertarGenero(&pelicula.genero);
        break;
    case 4:
        insertarTexto(pelicula.pais);
        break;
    case 5:
        insertarAnio(&pelicula.anio);
        break;
    case 6:
        insertarValoracion(&pelicula.valoracion);
        break;
    case 7:
        insertarPM(&pelicula.pm);
        break;
    case 8:
        insertarTexto(pelicula.url);
        break;
    }
    system("cls");
    printf("Los cambios se aplicaron correctamente\n");
    return pelicula;
}
void mostrarPelicula(stPelicula pelicula) //Muestra una pelicula
{
    printf("............\n\tID-\t%d", pelicula.idPelicula);
    printf("\n\tNOMBRE:\t\t%s\n", pelicula.nombrePelicula);
    printf("\tDIRECTOR:\t%s\n", pelicula.director);
    printf("\tGENERO:\t\t%s\n", pelicula.genero);
    printf("\tPAIS:\t\t%s\n", pelicula.pais);
    printf("\tANIO:\t\t%d\n", pelicula.anio);
    printf("\tVALORACION:\t%d\n", pelicula.valoracion);
    if(pelicula.pm == 0)
        printf("\tPM:\t\tATP\n");
    else if(pelicula.pm == 13)
        printf("\tPM:\t\t+13\n");
    else if(pelicula.pm == 16)
        printf("\tPM:\t\t+16\n");
    else
        printf("\tPM:\t\t+18\n");

    if(pelicula.eliminado == 1)
        printf("ELIMINADO:\tSI\n");
    else
        printf("ELIMINADO:\tNO\n");
    printf("URL:\n%s\n", pelicula.url);
}
stPelicula crearPelicula(nodoArbol *arbolActivo, nodoArbol *arbolEliminado) //Crea unSTPELICULA y lo retorna evaluando existencia
{
    int existencia;
    stPelicula peliNueva;
    insertarNombre(arbolActivo, arbolEliminado, &peliNueva.nombrePelicula); //Ingresa nombre a la pelicula
    peliNueva.idPelicula = ultimoIDPelicula(arbolActivo, arbolEliminado) + 1; //Se le asigna un ID
    insertarTexto(peliNueva.director); //Se le ingresa director
    insertarGenero(&peliNueva.genero); //Se le ingresa genero(CON MATRIZ)
    insertarTexto(peliNueva.pais); //Se le ingresa pais
    insertarAnio(&peliNueva.anio);                                                      //Se le ingresa a�o
    insertarValoracion(&peliNueva.valoracion);           //Se le ingresa Valoracion
    insertarPM(&peliNueva.pm);                                                        //Se le ingresa PM
    peliNueva.eliminado = 0;                                                    //Se crea sin eliminar
    insertarTexto(peliNueva.url);                  //Se le ingresa URL
    return peliNueva; //Retorna la pelicula
}

///ARBOLES
nodoArbol *crearNodoArbol(stPelicula pelicula) //Crea un nodoArbol desde un structPelicula
{
    nodoArbol *nuevoArbol = (nodoArbol*)malloc(sizeof(nodoArbol));
    nuevoArbol->izq = NULL;
    nuevoArbol->der = NULL;
    nuevoArbol->pelicula = pelicula;
    return nuevoArbol;
}
void preorder(nodoArbol *arbol) //Muestra el arbol completo preorder
{
    if(arbol)
    {

      mostrarPelicula(arbol->pelicula);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoArbol *arbol) //Muestra el arbol completo inorder
{
    if(arbol)
    {
        inorder(arbol->izq);
        mostrarPelicula(arbol->pelicula);
        inorder(arbol->der);
    }
}

void postorder(nodoArbol *arbol) //Muestra el arbol completo postorder
{
    if(arbol)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        mostrarPelicula(arbol->pelicula);
    }
}
nodoArbol *inicArbol() //La mas importante
{
    return NULL;
}
int ultimoIDPelicula(nodoArbol *arbolActivo, nodoArbol *arbolEliminado) //Busca el ultimo ID entre todas las pelis y lo retorna
{
    int a1 = 0;
    int a2 = 0;
    int id;
    nodoArbol *aux = nodoMasDerecho(arbolActivo);
    if(aux)
        a1 = aux->pelicula.idPelicula;
    aux = nodoMasDerecho(arbolEliminado);
    if(aux)
        a2 = aux->pelicula.idPelicula;
    if(a1 >= a2)
        id = a1;
    else
        id = a2;

    return id;
}
nodoArbol * nodoMasDerecho(nodoArbol * arbol) //Retorna el nodo mas derecho(el de mayor id)
{
    nodoArbol * nmd = NULL;
    if(arbol)
    {
        if(arbol->der==NULL)
            nmd=arbol;
        else
        {
            nmd=nodoMasDerecho(arbol->der);
        }
    }
    return nmd;

}

nodoArbol *buscarPeliNombre(nodoArbol *arbol, char nombre[]) //Busca y retorna un nodo por 'NOMBRE'
{
    nodoArbol *aux = NULL;
    if(arbol)
    {
        if(strcmpi(arbol->pelicula.nombrePelicula, nombre) == 0)
        {
            aux = arbol;
        }
        else
        {
            aux = buscarPeliNombre(arbol->izq, nombre);
            if(!aux)
                aux = buscarPeliNombre(arbol->der, nombre);
        }
    }
    return aux;
}

nodoArbol *creaYcargaPeliculaAlArbol(nodoArbol *arbolActivo, nodoArbol *arbolEliminado)//subprograma crea y carga una pelicula en un arbol(siempre debe ser el activo
{
    nodoArbol *aux;
    stPelicula nueva = crearPelicula(arbolActivo, arbolEliminado);
    aux = crearNodoArbol(nueva);
    arbolActivo = insertarNuevoArbol(arbolActivo, aux);

    return arbolActivo;
}

nodoArbol *insertarNuevoArbol(nodoArbol *arbolDestino, nodoArbol *nuevoArbol)//Inserta un nuevo nodo en el arbol
{


    if(arbolDestino)
    {
        if(nuevoArbol->pelicula.idPelicula > arbolDestino->pelicula.idPelicula)
        {
            arbolDestino->der = insertarNuevoArbol(arbolDestino->der, nuevoArbol);
        }
        else
        {
            arbolDestino->izq = insertarNuevoArbol(arbolDestino->izq, nuevoArbol);
        }
    }
    else
        arbolDestino = nuevoArbol;
    return arbolDestino;
}

nodoArbol *buscarPeliID(nodoArbol *arbol, int id) //Busca y retorna una pelicula por 'ID'
{
    nodoArbol *aux = NULL;
    if(arbol)
    {
        if(arbol->pelicula.idPelicula == id)
        {
            aux = arbol;
        }
        else
        {
            aux = buscarPeliID(arbol->izq, id);
            if(!aux)
                aux = buscarPeliID(arbol->der, id);
        }
    }
    return aux;
}

//retorna 1 o 0 dependiendo si esta o no.
int existenciaArbolPeliculaNombre(nodoArbol *arbol, char nombre[])//Verifica la existencia de una pelicula en un arbol por nombre y devuelve 1 o 0
{
    int existe = 0;
    if(arbol)
    {
        if(strcmpi(arbol->pelicula.nombrePelicula, nombre) == 0)
        {
            existe = 1;
        }
        else
        {
            existe = existenciaArbolPeliculaNombre(arbol->izq, nombre);
            if(existe == 0)
                existe = existenciaArbolPeliculaNombre(arbol->der, nombre);
        }
    }
    return existe;
}

int existenciaPeliculaNombre(nodoArbol *arbolActivo, nodoArbol *arbolEliminado, char nombre[])//Verifica la existencia de una pelicula en ambos arboles por nombre y devuelve 1 o 0
{
    int existe;
    existe = existenciaArbolPeliculaNombre(arbolActivo, nombre);
    if(existe == 0)
    {
        existe = existenciaArbolPeliculaNombre(arbolEliminado, nombre);
    }
    return existe;
}

nodoArbol * nodoMasIzquierdo(nodoArbol * arbol)//retorna el nodo mas izquierdo del arbol
{
    nodoArbol * nmi;
    if(arbol)
    {
        if(arbol->izq==NULL)
            nmi=arbol;
        else
        {
            nmi=nodoMasIzquierdo(arbol->izq);
        }
        return nmi;
    }

}

nodoArbol * borrarNodoArbolPelicula(nodoArbol * arbol, int id) //(horrorosa funcion) borra un nodo del arbol por id
{
    if(arbol)
    {
        if(arbol->pelicula.idPelicula == id)
        {
            if(arbol->izq)
            {
                nodoArbol * nmd = nodoMasDerecho(arbol->izq);
                arbol->pelicula = nmd->pelicula;
                arbol->izq = borrarNodoArbolPelicula(arbol->izq, nmd->pelicula.idPelicula);
            }
            else if(arbol->der)
            {
                nodoArbol * nmi = nodoMasIzquierdo(arbol->der);
                arbol->pelicula = nmi->pelicula;
                arbol->der = borrarNodoArbolPelicula(arbol->der, nmi->pelicula.idPelicula);
            }
            else
            {
                free(arbol);
                arbol=NULL;
            }
        }
        else if(id > arbol->pelicula.idPelicula)
            arbol->der = borrarNodoArbolPelicula(arbol->der, id);
        else if(id < arbol->pelicula.idPelicula)
            arbol->izq = borrarNodoArbolPelicula(arbol->izq, id);
    }
    return arbol;
}

nodoArbol *borrarArbol(nodoArbol *arbol) //Borra todo el arbol(nose cuando lo usaria por fue facil de codear) XD
{
    if(arbol)
    {
        arbol->izq = borrarArbol(arbol->izq);
        arbol->der = borrarArbol(arbol->der);
        free(arbol);
        arbol = NULL;
    }

    return arbol;
}



void insertarNombre(nodoArbol *arbolActivo, nodoArbol *arbolEliminado, char *nombre[]) //Pide un nombre para la pelicula y valida que no exista anteriormente
{
    int existencia;
    char nuevoNombre[60];
    do
    {

        printf("Ingrese nombre\n");
        fflush(stdin);
        gets(nuevoNombre);
        existencia = existenciaPeliculaNombre(arbolActivo, arbolEliminado, nuevoNombre);
        if(existencia)
        {
            system("cls");
            printf("Ingrese otro nombre, ya hay una pelicula con ese nombre\n");
        }
    }
    while(existencia);
    strcpy(nombre, nuevoNombre);
}

void modificarNodoArbol(nodoArbol *arbolActivo, nodoArbol *arbolEliminado) //Busca una pelicula en ambos arboles por nombre o id y le modifica un campo
{
    nodoArbol *aux = NULL;
    int opcion;
    int id;
    int existencia;
    char nombre[60];
    printf("Buscar por:\n1_NOMBRE\n2_ID\n");
    scanf("%d", &opcion);
    switch(opcion)
    {
    case 1:
        printf("Ingrese nombre a buscar\n");
        fflush(stdin);
        gets(nombre);
        existencia = existenciaPeliculaNombre(arbolActivo, arbolEliminado, nombre);
        if(existencia)
        {
            aux = buscarPeliNombre(arbolActivo, nombre);
            if(!aux)
                aux = buscarPeliNombre(arbolEliminado, nombre);

        }
        else
            printf("No se encontro la pelicula buscada\n");
        break;
    case 2:
        printf("Ingrese ID a buscar\n");
        fflush(stdin);
        scanf("%d", &id);
        if(id <= ultimoIDPelicula(arbolActivo, arbolEliminado))
        {
            aux = buscarPeliID(arbolActivo, id);
            if(!aux)
                aux = buscarPeliID(arbolEliminado, id);
        }
        break;


    }
aux->pelicula = modificaPelicula(arbolActivo, arbolEliminado, aux->pelicula);
}

void insertarTexto(char texto[])
{
    printf("Ingrese %s\n", texto);
    fflush(stdin);
    gets(texto);
}

void insertarPM(int *pm) //Valida que el pm sea ATP, +13, +16, +18
{
    int numero;
    do
    {

        printf("Ingrese nuevo PM\n0: ATP\n13: +13\n16: +16\n18: +18\n");
        fflush(stdin);
        scanf("%d", &numero);
        if(numero != 0 && numero != 13 && numero != 16 && numero != 18)
            printf("No es un PM valido\n");
    }
    while(numero != 0 && numero != 13 && numero != 16 && numero != 18);
    *pm = numero;
}

void insertarValoracion(int *valoracion) //Valida que la valoracion sea entre 1 y 5
{
    int numero;
    do
    {
        printf("Ingrese valoracion\n");
        fflush(stdin);
        scanf("%d", &numero);
        if(numero < 1 || numero > 5)
            printf("No es una valoracion valida\n");
    }
    while(numero < 1 || numero > 5);
    *valoracion = numero;
}

void insertarAnio(int *anio) //Valida que el a�o ingresado comienze desde la primera pelicula existente en 1895
{
    int num;
    do
    {
        printf("Ingrese anio\n");
        fflush(stdin);
        scanf("%d", &num);
        if(num > 2018 || num < 1895)
            printf("El anio %d es invalido, por favor ingrese un anio valido.\n", num);
    }
    while(num > 2018 || num < 1895);


    *anio = num;
}

void insertarGenero(char *genero) //Escoge un genero de la matriz y lo copia en el campo de genero
{

    int topic;
//Se utilizara como fila a copiarse de la matriz
    char genderFilm[9][11] = {{"DRAMA"}, {"TERROR"}, {"ACCION"}, {"CS FICCION"},
        {"SUSPENSO"}, {"ROMANCE"}, {"TRILLER"}, {"FANTASIA"}, {"COMEDIA"}
    };
    printf("Seleccione genero\n");
    do
    {
        //Matriz de generos de peliculas
        printf("1_DRAMA\n");
        printf("2_TERROR\n");
        printf("3_ACCION\n");
        printf("4_CS FICCION\n");
        printf("5_SUSPENSO\n");
        printf("6_ROMANCE\n");
        printf("7_TRILLER\n");
        printf("8_FANTASIA\n");
        printf("9_COMEDIA\n");
        fflush(stdin);
        scanf("%d",&topic);
        if(topic < 1 || topic > 9)
        {
            system("cls");
            printf("La opcion no es correcta\n");
        }
    }
    while(topic < 1 || topic > 9);
    strcpy(genero, genderFilm[topic-1]);
}

void insertarPais(char *pais)
{
    printf("Ingrese Pais\n");
    fflush(stdin);
    gets(pais);
}

nodoArbol *pasarNodoOtroArbol(nodoArbol *arbol1, nodoArbol **arbol2, int id) //busca una pelicula por id la borra y la cambia de arbol
{
    nodoArbol *aux = buscarPeliID(arbol1, id);
    if(aux->pelicula.eliminado == 0)
        aux->pelicula.eliminado = 1;
    else
        aux->pelicula.eliminado = 0;
    stPelicula newPeli = aux->pelicula;
    *arbol2 = insertarNuevoArbol(*arbol2, crearNodoArbol(newPeli));
    arbol1 = borrarNodoArbolPelicula(arbol1, id);
    return arbol1;
}

void altaBajaPelicula(nodoArbol **arbolActivo, nodoArbol **arbolEliminado) //subPrograma busca la pelicula, muestra su estado y al cambiarlo la cambia de arbol
{
    int id;
    char control;
    int existe;
    nodoArbol *aux = NULL;
    printf("Que pelicula desea dar de baja o alta ?\nIngrese id:");
    scanf("%d", &id);
    printf("\n");
    if(id <= ultimoIDPelicula(*arbolActivo, *arbolEliminado))
    {
        aux = buscarPeliID(*arbolActivo, id);
        printf("Su pelicula seleccionada es: %s\n", aux->pelicula.nombrePelicula);
        if(aux)
        {
            printf("Esta pelicula esta dada de alta, desea darla de baja?s/n\n");
            fflush(stdin);
            scanf("%c", &control);
            if(control == 's')
            {
                *arbolActivo = pasarNodoOtroArbol(*arbolActivo, arbolEliminado, id);
                printf("Su pelicula se ah dado de baja con exito\n");
            }
        }
        else
        {
            aux = buscarPeliID(*arbolEliminado, id);
            printf("Esta pelicula esta dada de baja, desea darla de alta?\n");
            fflush(stdin);
            scanf("%c", &control);
            if(control == 's')
            {
                *arbolEliminado = pasarNodoOtroArbol(*arbolEliminado, arbolActivo, id);
                printf("Su pelicula se ah dado de alta con exito\n");
            }
        }
    }
    else
        printf("No es una pelicula valida\n");
}
/////////////////////////////////////////////////// ARCHIVOS
void persistirPeliculas(nodoArbol *arbol, FILE *archi) //Persiste un arbol en el archivo
{
    stPelicula pelicula;
    if(arbol)
    {
        pelicula = arbol->pelicula;
        fwrite(&pelicula, 1, sizeof(stPelicula), archi);
        persistirPeliculas(arbol->izq, archi);
        persistirPeliculas(arbol->der, archi);
    }
}

void persistirTodo(nodoArbol *arbolActivo, nodoArbol *arbolEliminado) //Subprograma persiste los 2 arboles en el archivo
{
    FILE *archi;
    if(archi = fopen("peliculas.dat", "wb"))
    {
        persistirPeliculas(arbolActivo, archi);
        persistirPeliculas(arbolEliminado, archi);
        if(fclose(archi) == -1)
            printf("No pudo cerrarse el archivo\n");
    }
    else
    {
        printf("El archivo no pudo abrirse correctamente\n");
    }
}

void cantidadPelisArchivo(int *activo, int *eliminado) //Trae 2 punteros a enteros igualadas a 0 e incrementan por cada pelicula
{
    stPelicula peli;
    FILE *archi = fopen("peliculas.dat", "rb");
    if(archi != NULL)
    {
        while(fread(&peli, 1, sizeof(stPelicula), archi) > 0)

        {

            if(peli.eliminado == 1)
                *eliminado = *eliminado + 1;
            else
                *activo = *activo +1;
        }
        if(fclose(archi) == -1)
            printf("El archivo no pudo cerrarse correctamente\n");
    }
    else
        printf("No se pudo abrir el archivo\n");
}

void cargaArreglos(stPelicula activas[], stPelicula eliminadas[]) //Carga los arreglos desde el archivo
{
    int a = 0;
    int b = 0;
    stPelicula peli;
    FILE *archi = fopen("peliculas.dat", "rb");
    if(archi != NULL)
    {
        while(fread(&peli, 1, sizeof(stPelicula), archi) > 0)
        {
            if(peli.eliminado == 0){
                activas[a] = peli;
                a++;}
            else{
                eliminadas[b] = peli;
        b++;
        }}
        if(fclose == -1)
            printf("El archivo no pudo cerrarse correctamente\n");
    }
    else
        printf("El archivo no pudo abrirse correctamente\n");
}

void levantarArboles(nodoArbol **arbolActivo, nodoArbol **arbolEliminado) //Subprograma que abre el archivo, carga arreglos y los pasa a los arboles
{
    int a = 0;//Cantidad de peliculas dadas de alta
    int b = 0;//Cantidad de peliculas dadas de baja
    int i = 0;//contador
    cantidadPelisArchivo(&a, &b);
    stPelicula *activas =(stPelicula*) malloc(sizeof(stPelicula) * a);
    stPelicula *eliminadas = (stPelicula*) malloc(sizeof(stPelicula ) *b );
    cargaArreglos(activas, eliminadas);
    *arbolActivo = arbolBalanceado(activas, i, a);
    i = 0;
    *arbolEliminado = arbolBalanceado(eliminadas, i, b);

}
////
nodoArbol* arbolBalanceado(stPelicula arr[], int i, int validos)
{int medio = (i + validos)/2;
    nodoArbol *arbol= crearNodoArbol(arr[medio]);
    if (i < validos){
    arbol->izq =  arbolBalanceado(arr, i, medio-1);
    arbol->der = arbolBalanceado(arr, medio +1, validos);}
    else
        arbol= NULL;
    return arbol;
}
///// USAR
//altaBajaPelicula
//creaYcargaPeliculaAlArbol
//modificarNodoArbol
//levantarArboles /////INICIAR PROGRAMA SI O SI
//persistirTodo /////CERRAR PROGRAMA SI O SI
//buscarPeliID
//buscarPeliNombre
// preorder
