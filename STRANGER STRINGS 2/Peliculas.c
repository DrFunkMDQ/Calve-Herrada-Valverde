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
        insertarDirector(&pelicula.director);
        break;
    case 3:
        insertarGenero(&pelicula.genero);
        break;
    case 4:
        insertarPais(&pelicula.pais);
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
        fflush(stdin);
        gets(pelicula.url);
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
    insertarDirector(&peliNueva.director); //Se le ingresa director
    insertarGenero(&peliNueva.genero); //Se le ingresa genero(CON MATRIZ)
    insertarPais(&peliNueva.pais); //Se le ingresa pais
    insertarAnio(&peliNueva.anio);                                                      //Se le ingresa año
    insertarValoracion(&peliNueva.valoracion);           //Se le ingresa Valoracion
    insertarPM(&peliNueva.pm);                                                        //Se le ingresa PM
    peliNueva.eliminado = 0;                                                    //Se crea sin eliminar
    printf("Ingrese URL\n");
    scanf("%s", &peliNueva.url);                    //Se le ingresa URL
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

nodoArbol *creaYcargaPeliculaAlArbol(nodoArbol *arbolActivo, nodoArbol *arbolEliminado)//Debe igualarse al arbolActivo
{
    nodoArbol *aux;
    stPelicula nueva = crearPelicula(arbolActivo, arbolEliminado);
    aux = crearNodoArbol(nueva);
    arbolActivo = insertarNuevoArbol(arbolActivo, aux);

    return arbolActivo;
}

nodoArbol *insertarNuevoArbol(nodoArbol *arbolDestino, nodoArbol *nuevoArbol)
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
int existenciaArbolPeliculaNombre(nodoArbol *arbol, char nombre[])
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

int existenciaPeliculaNombre(nodoArbol *arbolActivo, nodoArbol *arbolEliminado, char nombre[])
{
    int existe;
    existe = existenciaArbolPeliculaNombre(arbolActivo, nombre);
    if(existe == 0)
    {
        existe = existenciaArbolPeliculaNombre(arbolEliminado, nombre);
    }
    return existe;
}

nodoArbol * nodoMasIzquierdo(nodoArbol * arbol)
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

nodoArbol * borrarNodoArbolPelicula(nodoArbol * arbol, int id)
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

nodoArbol *borrarArbol(nodoArbol *arbol)
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



void insertarNombre(nodoArbol *arbolActivo, nodoArbol *arbolEliminado, char *nombre[])
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

void modificarNodoArbol(nodoArbol *arbolActivo, nodoArbol *arbolEliminado)
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
        scanf("%d", &id);
        if(id <= ultimoIDPelicula(arbolActivo, arbolEliminado))
        {
            aux = buscarPeliID(arbolActivo, id);
            if(!aux)
                aux = buscarPeliID(arbolEliminado, id);
        }
        break;

        aux->pelicula = modificaPelicula(arbolActivo, arbolEliminado, aux->pelicula);
    }
}

void insertarDirector(char *director)
{
    printf("Ingrese director\n");
    fflush(stdin);
    gets(director);
}

void insertarPM(int *pm)
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

void insertarValoracion(int *valoracion)
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

void insertarAnio(int *anio)
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

void insertarGenero(char *genero)
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

nodoArbol *pasarNodoOtroArbol(nodoArbol *arbol1, nodoArbol **arbol2, int id)
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

void altaBajaPelicula(nodoArbol **arbolActivo, nodoArbol **arbolEliminado)
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
