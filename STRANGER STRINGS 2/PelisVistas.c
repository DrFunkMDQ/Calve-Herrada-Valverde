#include "PelisVistas.H"


void pasarDeArchivoPelisVistasToLDL(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja, nodoArbol * arbolAlta, nodoArbol * arbolBaja)
{
    nodoListaPelicula * listaAlta;
    nodoListaPelicula * listaBaja;
    nodoArbol * auxNuevaPeli;
    stPelisVistas auxPeli;
    //auxiliar para buffer
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
                ///auxNuevaPeli = buscarPeliID(arbolAlta, auxPeli.idPelicula);///SAKE
                //almacena la pelicula en cuestion
                if(auxNuevaPeli == NULL)
                    ///auxNuevaPeli = buscarPeliID(arbolBaja, auxPeli.idPelicula);///SAKE
                listaAlta = buscarUsuarioID(*lDlAlta, auxPeli.idUsuario);///archivo ordenado, solo comparo que sea igual a USRID o paso al siguiente
                //lista de usuario en cuestion
                if(listaAlta == NULL)
                {
                    listaBaja = buscarUsuarioID(*lDlBaja, auxPeli.idUsuario);///archivo ordenado, solo comparo que sea igual a USRID o paso al siguiente
                    agregarPpiolListaPeliculas(*lDlBaja, crearNodoListaPeliculas(auxNuevaPeli->pelicula, auxPeli.valUser));
                }
                else
                    agregarPpiolListaPeliculas(*lDlAlta, crearNodoListaPeliculas(auxNuevaPeli->pelicula, auxPeli.valUser));
            }
        }
        if(fclose(pFile) == -1)
        {
            printf("*ERROR*\n");
            printf("El archivo no se pudo cerrar correctamente.\n");
        }
    }
}

void inicListaPeliculas(nodoListaPelicula ** lista){
    *lista = NULL;
}

nodoListaPelicula * buscarUsuarioID(nodoUsuario * lDl, int idUsuario)
{
    nodoListaPelicula * aux;
    inicListaPeliculas(&aux);
    if(lDl)
    {
        if(lDl->usr.idUsuario == idUsuario)
            aux = lDl->listaPelis;
        else
        {
            aux = buscarUsuarioID(lDl->sig, idUsuario);
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

stPelisVistas crearPeliVista (int valoracion, int peliID, int usrID, int peliVIstaID){///           CHEKEAR
    stPelisVistas peliVista;
    peliVista.idPelicula = peliID;
    peliVista.idUsuario = usrID;
    peliVista.valUser = valoracion;
    peliVista.idPeliVista = peliVIstaID;/// como trabajar ID
}

void agregarPpiolListaPeliculas (nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo)
{
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;
}

void actualizarPeliculasVistas(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja) /// cuando solucione ID
{
    FILE * archivo;
    if(archivo = fopen(ruta, "wb"))
    {
        actualizarPvAlta(archivo, &lDlAlta);
        actualizarPvBaja(archivo, &lDlBaja);
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
            peliVista = crearPeliVista((*lDlAlta)->listaPelis.valUser, (*lDlAlta)->listaPelis.idPelicula, (*lDlAlta)->usr.idUsuario);
            peliVista = peliVista + 1;///pasar ID por puntero
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
            peliVista = crearPeliVista((*lDlBaja)->listaPelis.valUser, (*lDlBaja)->listaPelis.idPelicula, (*lDlBaja)->usr.idUsuario);
            peliVista = peliVista + 1;///pasar ID por puntero
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

void reproducirPelicula(nodoListaPelicula ** listaUsr, int peliID, nodoArbol * arbolAlta){///chekear si ya vio la peli
    nodoArbol * auxPeliArbol;
    nodoListaPelicula * auxPeliVista;
    int valoracion;
    /// auxPeliArbol = buscaPeliID(arbolAlta, peliID); SAKEE
    if(existePeliVista(*listaUsr, auxPeliArbol->pelicula) == 0){
        printf("Que te ha parecido la pelicula?\n");
        printf("Ingresa un valor del 1 al 5.\n");
        printf("Muchas Gracias!!");
        scanf("%d", &valoracion);
        auxPeliVista = crearNodoListaPeliculas(auxPeliArbol->pelicula, valoracion);
        agregarAlFinal(listaUsr, auxPeliVista);
    }
    /// EMI URL
}

int existePeliVista(nodoListaPelicula * listaUsr, stPelicula nuevaPeli){
    int flag = 0;
    while(listaUsr){
        if(listaUsr->pelicula == nuevaPeli);
            flag = 1;
        listaUsr = listaUsr->sig;
    }
    return flag;
}
/// ///////////////////////////////////////////////////////////////////////

void agregarAlPrincipio(nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo)
{
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;
}

void agregarEnOrdenPorNombreDePelicula(nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo)
{
    nodoListaPelicula * seg = *lista;
    nodoListaPelicula * ant;
    if(*lista == NULL)
        *lista = nuevoNodo;
    else
    {
        if(strcmpi(seg->pelicula.nombrePelicula, nuevoNodo->pelicula.nombrePelicula) == 1)
            agregarAlPrincipio(lista, nuevoNodo);
        else
        {
            ant = *lista;///si entra en segundo lugar necesio el primero para apuntarlo
            seg = (*lista)->sig;///salteo primer nodo
            while(seg != NULL && strcmpi(seg->pelicula.nombrePelicula, nuevoNodo->pelicula.nombrePelicula) == -1)
            {
                ant = seg;
                seg = seg->sig;
            }
            ant->sig = nuevoNodo;
            nuevoNodo->sig = seg;
        }
    }
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

void agregarAlFinal(nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo)
{
    if(*lista == NULL)
        *lista = nuevoNodo;
    else
    {
        nodoListaPelicula * aux = ultimoNodo(*lista);
        aux->sig = nuevoNodo;
    }
}

void mostrarLista(nodoListaPelicula * lista)
{
    nodoListaPelicula * seg = lista;
    while(seg != NULL)
    {
        ///mostrarPelicla(seg->pelicula);                     ///sake
        seg = seg->sig;
    }
}

void borrarNodoPorIdPelicula(nodoListaPelicula ** lista, int id)
{
    nodoListaPelicula * seg = *lista;
    if(*lista != NULL && (*lista)->pelicula.idPelicula == id)
    {
        (*lista)= (*lista)->sig;
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
}



