#include "PelisVistas.H"


void pasarDeArchivoPelisVistasToLDL(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja, nodoArbol * arbolAlta, nodoArbol * arbolBaja)
{
    nodoListaPelicula * listaAlta;
    nodoListaPelicula * listaBaja;
    nodoArbol * auxNuevaPeli;
    stPelisVistas auxPeli;
    //auxiliar para buffer
    int flag = 0;
    FILE * pFile = fopen(ruta, "rb");
    //abrir archivo
    if((pFile = fopen(ruta, "rb")) != NULL)
    {
        while (!feof(pFile))
        {
            //recorro archivo
            fread(&auxPeli, sizeof(stPelisVistas), 1, pFile);
            //baja a buffer una pelicula
            if(!feof(pFile))
            {
                //ingresa si no llega al final del archivo
                auxNuevaPeli = buscarPeliID(arbolAlta, auxPeli.idPelicula);///Almacena nodoArbol si la encuentra
                //almacena la pelicula en cuestion
                if(auxNuevaPeli == NULL)
                    auxNuevaPeli = buscarPeliID(arbolBaja, auxPeli.idPelicula);///Almacena nodoArbol si la encuentra
                listaAlta = buscarListaPeliculaUsuarioID(*lDlAlta, auxPeli.idUsuario, &flag);///Almacena lista de peliculas del usuario buscado
                //lista de usuario en cuestion
                if(flag == 1)
                {
                    (*lDlAlta)->listaPelis = agregarPpiolListaPeliculas(listaAlta, crearNodoListaPeliculas(auxNuevaPeli->pelicula, auxPeli.valUser));
                }
                else
                {
                    listaBaja = buscarListaPeliculaUsuarioID(*lDlBaja, auxPeli.idUsuario, &flag);///Almacena lista de peliculas del usuario buscado
                    (*lDlAlta)->listaPelis = agregarPpiolListaPeliculas(listaBaja, crearNodoListaPeliculas(auxNuevaPeli->pelicula, auxPeli.valUser));
                }
            }
        }
        if(fclose(pFile) == -1)
        {
            printf("*ERROR*\n");
            printf("El archivo no se pudo cerrar correctamente.\n");
        }
    }
}

void inicListaPeliculas(nodoListaPelicula ** lista)
{
    *lista = NULL;
}

nodoListaPelicula * buscarListaPeliculaUsuarioID(nodoUsuario * lDl, int idUsuario, int * flag)
{
    nodoListaPelicula * aux;
    inicListaPeliculas(&aux);
    if(lDl)
    {
        if(lDl->usr.idUsuario == idUsuario)
        {
            aux = lDl->listaPelis;
            *flag = 1;
        }
        else
        {
            aux = buscarListaPeliculaUsuarioID(lDl->sig, idUsuario, flag);
        }
    }
    return aux;
}

nodoListaPelicula * crearNodoListaPeliculas(stPelicula peli, int valoracion)
{
    nodoListaPelicula * aux = malloc(sizeof(nodoListaPelicula));
    aux->sig = NULL;
    aux->pelicula = peli;
    aux->valUser = valoracion;
    return aux;
}

stPelisVistas crearPeliVista (int valoracion, int peliID, int usrID, int * peliVIstaID) ///           CHEKEAR
{
    stPelisVistas peliVista;
    peliVista.idPelicula = peliID;
    peliVista.idUsuario = usrID;
    peliVista.valUser = valoracion;
    peliVista.idPeliVista = *peliVIstaID + 1;/// como trabajar ID
    return peliVista;
}

nodoListaPelicula * agregarPpiolListaPeliculas (nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo)
{
    nuevoNodo->sig = lista;
    lista = nuevoNodo;
    return lista;
}

void actualizarPeliculasVistas(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja) /// cuando solucione ID
{
    FILE * archivo;
    int ID = 0;
    if(archivo = fopen(ruta, "wb"))
    {
        actualizarPvAlta(archivo, lDlAlta, &ID);
        actualizarPvBaja(archivo, lDlBaja, &ID);
    }
    fclose(archivo);
}

void actualizarPvAlta (FILE * archivo, nodoUsuario ** lDlAlta, int * peliVistaID) /// cuando solucione ID
{
    stPelisVistas peliVista;
    while(*lDlAlta)
    {
        while((*lDlAlta)->listaPelis)
        {
            nodoListaPelicula * aux = (*lDlAlta)->listaPelis;
            peliVista = crearPeliVista(aux->valUser, aux->pelicula.idPelicula, (*lDlAlta)->usr.idUsuario, peliVistaID);
            fwrite(&peliVista, sizeof(stPelisVistas), 1, archivo);
            borrarPrimerPeliVista(&(*lDlAlta)->listaPelis);
        }
        *lDlAlta = (*lDlAlta)->sig;
    }
}

void actualizarPvBaja (FILE * archivo, nodoUsuario ** lDlBaja, int *peliVistaID) /// cuando solucione ID
{
    stPelisVistas peliVista;
    while(*lDlBaja)
    {
        while((*lDlBaja)->listaPelis)
        {
            nodoListaPelicula * aux = (*lDlBaja)->listaPelis;
            peliVista = crearPeliVista(aux->valUser, aux->pelicula.idPelicula, (*lDlBaja)->usr.idUsuario, peliVistaID);
            fwrite((*lDlBaja)->listaPelis, sizeof(stPelisVistas), 1, archivo);
            borrarPrimerPeliVista(&(*lDlBaja)->listaPelis);
        }
        *lDlBaja = (*lDlBaja)->sig;
    }
}

void borrarPrimerPeliVista(nodoListaPelicula ** lista)
{
    nodoListaPelicula * aux = *lista;
    if(lista)
    {
        *lista = (*lista)->sig;
        free(aux);
    }
}

void borrarUltimaPeliVista(nodoListaPelicula ** lista)
{
    if(lista)
    {
        nodoListaPelicula * seg = *lista;
        nodoListaPelicula * ant;
        if(!seg->sig)
        {
            *lista = seg->sig;
        }
        else
        {
            while(seg->sig)
            {
                ant = seg;
                seg = seg->sig;
            }
            ant->sig = seg->sig;
        }
        free(seg);
    }
}

void reproducirPelicula(nodoListaPelicula ** listaUsr, int peliID, stPelicula peli)
{
    nodoListaPelicula * auxPeliVista;
    char start[10]= {"START "};
    int valoracion;
    if(existePeliVista(*listaUsr, peli) == 0)
    {
        strcat(start, peli.url);
        system(start);
        printf("Que te ha parecido la pelicula?\n");
        printf("Ingresa un valor del 1 al 5.\n");
        scanf("%d", &valoracion);
        system("cls");
        printf("Muchas Gracias!!");
        auxPeliVista = crearNodoListaPeliculas(peli, valoracion);
        *listaUsr = agregarAlFinal(*listaUsr, auxPeliVista);
    }
    /// EMI URL
}

void subProgramaReproduccion (nodoListaPelicula ** listaUsr, nodoArbol * arbolAlta)
{
    int peliID;
    char control = 's';
    nodoArbol * auxPeliArbol;
    printf("Ingrese el ID de la pelicula deseada\n");
    scanf("%d", &peliID);
    auxPeliArbol = buscarPeliID(arbolAlta, peliID);
    if(!auxPeliArbol)
    {
        printf("*ERROR*\n");
        printf("El ID no existe\n");
        printf("Desea ingresar otro ID s/n?\n");
        fflush(stdin);
        scanf("%c", &control);
        while(control == 's')
        {
            printf("Ingrese el ID de la pelicula deseada\n");
            scanf("%d", &peliID);
            if((auxPeliArbol = buscarPeliID(arbolAlta, peliID)) == NULL)
            {
                printf("*ERROR*\n");
                printf("El ID no existe\n");
                printf("Desea ingresar otro ID s/n?\n");
                fflush(stdin);
                scanf("%c", &control);
            }
            else
            {
                control = 'n';
                reproducirPelicula(listaUsr, peliID, auxPeliArbol->pelicula);
            }
        }
    }
    else
        reproducirPelicula(listaUsr, peliID, auxPeliArbol->pelicula);
}

int existePeliVista(nodoListaPelicula * listaUsr, stPelicula nuevaPeli)
{
    int flag = 0;
    while(listaUsr)
    {
        if(listaUsr->pelicula.idPelicula == nuevaPeli.idPelicula)
            flag = 1;
        listaUsr = listaUsr->sig;
    }
    return flag;
}
/// ///////////////////////////////////////////////////////////////////////


nodoListaPelicula * agregarEnOrdenPorNombreDePelicula(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo)
{
    nodoListaPelicula * seg = lista;
    nodoListaPelicula * ant;
    if(lista == NULL)
        lista = nuevoNodo;
    else
    {
        if(strcmpi(seg->pelicula.nombrePelicula, nuevoNodo->pelicula.nombrePelicula) == 1)
            lista =  agregarPpiolListaPeliculas (lista, nuevoNodo);
        else
        {
            ant = lista;///si entra en segundo lugar necesio el primero para apuntarlo
            seg = lista->sig;///salteo primer nodo
            while(seg != NULL && strcmpi(seg->pelicula.nombrePelicula, nuevoNodo->pelicula.nombrePelicula) == -1)
            {
                ant = seg;
                seg = seg->sig;
            }
            ant->sig = nuevoNodo;
            nuevoNodo->sig = seg;
        }
    }
    return lista;
}

nodoListaPelicula * ultimoNodo(nodoListaPelicula * lista)
{
    nodoListaPelicula * aux = lista;
    while(aux->sig != NULL)
    {
        aux = aux->sig;
    }
    return aux;
}

nodoListaPelicula * agregarAlFinal(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo)
{
    if(lista == NULL)
        lista = nuevoNodo;
    else
    {
        nodoListaPelicula * aux = ultimoNodo(lista);
        aux->sig = nuevoNodo;
    }
    return lista;
}

void mostrarLista(nodoListaPelicula * lista)
{
    nodoListaPelicula * seg = lista;
    while(seg != NULL)
    {
        mostrarPelicula(seg->pelicula);
        seg = seg->sig;
    }
}

nodoListaPelicula * borrarNodoPorIdPelicula(nodoListaPelicula * lista, int id)
{
    nodoListaPelicula * seg = lista;
    if(lista != NULL && lista->pelicula.idPelicula == id)
    {
        lista = lista->sig;
        free(seg);
    }
    else
    {
        nodoListaPelicula * ant;
        while(seg != NULL && seg->pelicula.idPelicula != id)
        {
            ant = seg;
            seg = seg->sig;
        }
        if(seg != NULL)
        {
            ant->sig = seg->sig;
            free(seg);
        }
    }
    return lista;
}




