#include "Peliculas.H"
///Struct Pelis---------------------------------------------------
void mostrarPelicula(stPelicula pelicula)
{
    printf("............\n\t-\t%d", pelicula.idPelicula);
    printf("\n\tNOMBRE:\t%s\n", pelicula.nombrePelicula);
    printf("\tDIRECTOR:\t%s\n", pelicula.director);
    printf("\tGENERO:\t%s\n", pelicula.genero);
    printf("\tPAIS:\t%s\n", pelicula.pais);
    printf("\tAÑO:\t%d\n", pelicula.anio);
    printf("\tVALORACION:\t%d\n", pelicula.valoracion);
    printf("\tPM:\t%d\n", pelicula.pm);
    if(pelicula.eliminado == 1)
        printf("ELIMINADO:\tSI\n");
    else
        printf("ELIMINADO:\tNO\n");
}
stPelicula crearPelicula(char nombre[], nodoArbol *arbol)
{
    int pm; //Variable para igualar al pm de la peli nueva;
    stPelicula peliNueva;
    strcpy(peliNueva.director, nombre);
    printf("Ingrese director\n");
    fflush(stdin);
    scanf("%s", &peliNueva.director);
    printf("Ingrese genero\n");
    fflush(stdin);
    scanf("%s", &peliNueva.genero);
    printf("Ingrese pais\n");
    fflush(stdin);
    scanf("%s", &peliNueva.pais);
    printf("Ingrese año\n");
    scanf("%d", &peliNueva.anio);
    do
    {
        printf("Ingrese valoracion\n");
        scanf("%d", &peliNueva.valoracion);
    }
    while(peliNueva.valoracion < 1 || peliNueva.valoracion > 5);
    do
    {
        printf("Ingrese PM\n0: ATP\n1: +13\n2: +16\n3: +18\n");
        scanf("%d", &pm);
        if(pm != 0 || pm != 1 || pm != 2 || pm != 3)
            printf("No es un PM valido, por favor ingreselo nuevamente.\n");

    }
    while(pm != 0 || pm != 1 || pm != 2 || pm != 3);
    switch(pm)
    {
    case 0:
        peliNueva.pm = 0;
        break;
    case 1:
        peliNueva.pm = 13;
        break;
    case 2:
        peliNueva.pm = 16;
        break;
    case 3:
        peliNueva.pm = 18;
        break;
    }
    peliNueva.eliminado = 0;
    nodoArbol *aux = nodoMasDerecho(arbol);
    peliNueva.idPelicula = aux->pelicula.idPelicula + 1;
    return peliNueva;
}
///ARBOLES DE PELIS----------------------------------------
nodoArbol *inicArbol() //EL MAS IMPORTANTE
{
    return NULL;
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

nodoArbol *buscarPeliID(nodoArbol *arbol, int peliId) //Busca y retorna una pelicula por 'ID'
{
    nodoArbol *aux = NULL;
    if(arbol)
    {
        if(peliId == arbol->pelicula.idPelicula)
        {
            aux = arbol;
        }
        else if(peliId < arbol->pelicula.idPelicula)
        {
            aux = buscarPeliID(arbol->izq, peliId);
        }
        else
        {
            aux = buscarPeliID(arbol->der, peliId);
        }
    }
    return aux;
}

nodoArbol *buscarPeliNombre(nodoArbol *arbol, char nombre[]) //Busca y retorna una pelicula por 'NOMBRE'
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

nodoArbol *crearNodoArbol(stPelicula pelicula) //Crea un nodo arbol con una pelicula pasada por parametro
{
    nodoArbol *nuevoArbol = (nodoArbol*)malloc(sizeof(nodoArbol));
    nuevoArbol->pelicula = pelicula;
    nuevoArbol->izq = NULL;
    nuevoArbol->der = NULL;
    return nuevoArbol;
}

nodoArbol *insertarNuevoArbol(nodoArbol *arbol, nodoArbol *nuevoArbol)
{
    if(!arbol)
        arbol = nuevoArbol;
    else
    {
        if(nuevoArbol->pelicula.idPelicula <= arbol->pelicula.idPelicula)
            arbol->izq = insertarNuevoArbol(arbol->izq, nuevoArbol);
        else
            arbol->der = insertarNuevoArbol(arbol->der, nuevoArbol);
    }
    return arbol;
}

nodoArbol *nodoMasDerecho(nodoArbol *arbol)
{
    nodoArbol *aux;
    if(arbol)
    {
        if(arbol->der)
            arbol = nodoMasDerecho(arbol->der);
    }
    else
        aux = arbol;
    return aux;
}
///SUBPROGRAMAS:-------------------------------------------------------------------------------
void creaYcargaPeliculaAlArbol(nodoArbol **arbolActivo, nodoArbol **arbolEliminado)
{
    char nombre[60];
    nodoArbol *aux;
    printf("Ingrese nombre de la pelicula\n");
    fflush(stdin);
    scanf("%s", &nombre);
    aux = buscarPeliNombre(arbolActivo, nombre);
    if(!aux)
    {
        aux = buscarPeliNombre(arbolEliminado, nombre);
        if(!aux)
        {
            stPelicula nueva = crearPelicula(nombre, arbolActivo);
            aux = crearNodoArbol(nueva);
            *arbolActivo = insertarNuevoArbol(arbolActivo, aux);
        }
        else
        {
            printf("La pelicula ya existe\n");
        }
    }
}
