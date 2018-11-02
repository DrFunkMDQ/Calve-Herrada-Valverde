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

nodoArbol *insertarNuevoArbol(nodoArbol *arbolActivo, nodoArbol *nuevoArbol)
{


    if(arbolActivo)
    {
        if(nuevoArbol->pelicula.idPelicula > arbolActivo->pelicula.idPelicula)
        {
            arbolActivo->der = insertarNuevoArbol(arbolActivo->der, nuevoArbol);
        }
        else
        {
            arbolActivo->izq = insertarNuevoArbol(arbolActivo->izq, nuevoArbol);
        }
    }
    else
        arbolActivo = nuevoArbol;
    return arbolActivo;
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

nodoArbol *modificarPeliNombre(nodoArbol *arbol, char nombre[]) //Busca y retorna una pelicula por 'NOMBRE'
{
    int cambio = 0;
    if(arbol)
    {
        if(strcmpi(arbol->pelicula.nombrePelicula, nombre) == 0)
        {

            int opcion;
            int numero;
            char nombre[60];
            char control;
            mostrarPelicula(arbol->pelicula);
            printf("Que campo desea modificar?\n");
            printf("1_NOMBRE\n2_DIRECTOR\n3_GENERO\n4_PAIS\n5_ANIO\n6_VALORACION\n7_PM\n8_ELIMINADO\n9_URL\n");
            scanf("%d", &opcion);
            switch(opcion)
            {
            case 1:
                do
                {
                    printf("Ingrese Nuevo NOMBRE\n");
                    fflush(stdin);
                    gets(nombre);
                    printf("El NOMBRE ingresado es :\t'%s'\nEs correcto?s/n\n", nombre);
                    fflush(stdin);
                    scanf("%c", &control);
                }
                while(control != 's');
                if(!buscarPeliNombre(arbol, nombre))
                {
                    strcpy(arbol->pelicula.nombrePelicula, nombre);
                    cambio = 1;
                }
                else
                    printf("Ese nombre de pelicula ya existe\n");
                break;
            case 2:
                do
                {
                    printf("Ingrese nuevo DIRECTOR\n");
                    fflush(stdin);
                    gets(nombre);
                    printf("El DIRECTOR ingresado es :\t'%s'\nEs correcto?s/n\n", nombre);
                    fflush(stdin);
                    scanf("%c", &control);
                }
                while(control != 's');
                strcpy(arbol->pelicula.director, nombre);
                cambio = 1;
                break;
            case 3:
                do
                {
                    printf("Ingrese nuevo GENERO\n");
                    fflush(stdin);
                    gets(nombre);
                    printf("El GENERO ingresado es :\t'%s'\nEs correcto?s/n\n", nombre);
                    fflush(stdin);
                    scanf("%c", &control);
                }
                while(control != 's');
                strcpy(arbol->pelicula.genero, nombre);
                cambio = 1;
                break;
            case 4:
                do
                {
                    printf("Ingrese nuevo PAIS\n");
                    fflush(stdin);
                    gets(nombre);
                    printf("El PAIS ingresado es :\t'%s'\nEs correcto?s/n\n", nombre);
                    fflush(stdin);
                    scanf("%c", &control);
                }
                while(control != 's');
                strcpy(arbol->pelicula.pais, nombre);
                cambio = 1;
                break;
            case 5:
                do
                {
                    do
                    {
                        fflush(stdin);
                        printf("Ingrese nuevo ANIO\n");
                        scanf("%d", &numero);
                        if(numero < 1895 || numero > 2018)
                        {
                            system("cls");
                            printf("El anio %d no es un anio valido\n", numero);
                        }
                    }
                    while(numero < 1895 || numero > 2018);
                    printf("El ANIO ingresado es :\t'%d'\nEs correcto?s/n\n", numero);
                    fflush(stdin);
                    scanf("%c", &control);
                }
                while(control != 's');
                arbol->pelicula.anio = numero;
                cambio = 1;
                break;
            case 6:
                do
                {
                    fflush(stdin);
                    printf("Ingrese la nueva VALORACION\n");
                    scanf("%d", &numero);
                    if(numero < 1 || numero > 5)
                        printf("No es una valoracion valida\n");
                }
                while(numero < 1 || numero > 5);
                printf("la VALORACION ingresada es :\t'%d'\nEs correcto?s/n\n", numero);
                fflush(stdin);
                scanf("%c", &control);
                while(control != 's');
                arbol->pelicula.valoracion = numero;
                cambio = 1;
                break;
            case 7:
                do
                {
                    fflush(stdin);
                    printf("Ingrese nuevo PM\n0: ATP\n13: +13\n16: +16\n18: +18\n");
                    scanf("%d", &numero);
                    if(numero != 0 && numero != 13 && numero != 16 && numero != 18)
                        printf("No es un PM valido\n");
                }
                while(numero != 0 && numero != 13 && numero != 16 && numero != 18);
                arbol->pelicula.pm = numero;
                cambio = 1;
                break;
            case 8:
                if(arbol->pelicula.eliminado == 1)
                {
                    printf("Desea dar de alta esta pelicula?\n");
                    fflush(stdin);
                    scanf("%c", &control);
                    if(control == 's')
                    {
                        arbol->pelicula.eliminado = 0;
                        cambio = 1;
                    }
                }
                else
                {
                    printf("Desea dar de baja esta pelicula?\n");
                    fflush(stdin);
                    scanf("%c", &control);
                    if(control == 's')
                    {
                        arbol->pelicula.eliminado = 1;
                        cambio = 1;
                    }
                }
                break;
            case 9:
                printf("Ingrese el nuevo URL\n");
                fflush(stdin);
                gets(nombre);
                printf("El URL ingresado es:\n%s\nEs correcto?\n", nombre);
                fflush(stdin);
                scanf("%c", &control);
                if(control == 's')
                {
                    strcpy(arbol->pelicula.url, nombre);
                    cambio = 1;
                }
                else
                    printf("No se modifico el URL\n");
                break;
            }
        }
        else
        {

            arbol->izq = buscarPeliNombre(arbol->izq, nombre);
            arbol->der = buscarPeliNombre(arbol->der, nombre);
        }
    }
    else if(!arbol)
    {
        printf("No se encontro la pelicula deseada\n");
    }
    if(cambio == 1)
    {
        system("cls");
        printf("Los cambios se modificaron correctamente\n");
    }
    return arbol;
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

void insertarValoracion(int *valoracion){
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

void insertarAnio(int *anio){
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

void insertarGenero(char *genero){

    int topic;
//Se utilizara como fila a copiarse de la matriz
    char genderFilm[9][11] = {{"DRAMA"}, {"TERROR"}, {"ACCION"}, {"CS FICCION"},
        {"SUSPENSO"}, {"ROMANCE"}, {"TRILLER"}, {"FANTASIA"}, {"COMEDIA"}};
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
    }while(topic < 1 || topic > 9);
strcpy(genero, genderFilm[topic-1]);
}

void insertarPais(char *pais){
printf("Ingrese Pais\n");
fflush(stdin);
gets(pais);
}
