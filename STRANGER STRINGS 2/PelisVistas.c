#include "PelisVistas.H"

stPelisVistas valoracionPorUsuario(stPelisVistas peliVista)
{
    printf("Que te ha parecido la pelicula?\n");
    printf("Ingresa un valor del 1 al 5.\n");
    printf("Muchas Gracias!!");
    scanf("%d", &peliVista.valUser);
    return peliVista;
}
nodoUsuario * pasarDeArchivoPelisVistasToLDL(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja, nodoArbol * arbolAlta, nodoArbol * arbolBaja)
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
    return lDlBaja;
}

void inicListaPeliculas(nodoListaPelicula ** lista)
{
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
            /// aux = buscarListaPelicula(lDl, idUsuario);  EMIII
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

void agregarPpiolListaPeliculas (nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo)
{
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;
}

nodoUsuario * actualizarPeliculasVistas(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja)
{
    actualizarPvAlta(ruta, &lDlAlta);
    actualizarPvBaja(ruta, &lDlBaja);
}

nodoUsuario * actualizarPvAlta (char ruta [], nodoUsuario ** lDlAlta)
{
    while(*lDlAlta)
    {
        while((*lDlAlta)->listaPelis)
        {
            persistirPeliVista(ruta, (*lDlAlta)->listaPelis);
            borrarPrimerPeliVista(&(*lDlAlta)->listaPelis);
        }
        *lDlAlta = (*lDlAlta)->sig;
    }
}

nodoUsuario * actualizarPvBaja (char ruta [], nodoUsuario ** lDlBaja)
{
    while(*lDlBaja)
    {
        while((*lDlBaja)->listaPelis)
        {
            persistirPeliVista(ruta, (*lDlBaja)->listaPelis);
            borrarPrimerPeliVista(&(*lDlBaja)->listaPelis);
        }
        *lDlBaja = (*lDlBaja)->sig;
    }
}

void persistirPeliVista(char ruta[], stPelisVistas * peliVista)
{
    FILE * pFile = fopen(ruta, "wb");
    if((pFile = fopen(ruta, "wb")) != NULL)
    {
        fwrite(peliVista, sizeof(stPelisVistas), 1, pFile);
        if(fclose(pFile) == -1)
        {
            printf("*ERROR*\n");
            printf("El archivo no se pudo cerrar correctamente.\n");
        }
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

void reproducirPelicula(nodoListaPelicula ** listaUsr, int peliID)
{
    ///agregarAlFinal(listaUsr, buscarPeliID(arbolBaja, auxPeli.idPelicula);///SAKE)

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
        //mostrarPelicla(seg->pelicula);                     ///sake
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

<<<<<<< HEAD
nodoRecomendacion * crearRecomendacion(nodoRecomendacion * listaRecomendaciones, char nombreRemitente,nodoUsuario * listaAltas, nodoUsuario * listaBajas, nodoArbol * arbolAltas, nodoArbol * arbolBajas)
{
    char mensaje[100];
    char nombrePelicula[60];
    nodoArbol * peliculaArbol;
    nodoRecomendacion * nuevaRecomendacion=malloc(sizeof(nodoRecomendacion));
    strcpy(nuevaRecomendacion->recomendacion.remitente, nombreRemitente);
    while(!peliculaArbol)
    {
        printf("La pelicula no existe o fue dada de baja. Ingrese otro nombre por favor\n");
        fflush(stdin);
        gets(nombrePelicula);
        peliculaArbol=buscarPeliNombre(arbolAltas, nombrePelicula);
    }
    nuevaRecomendacion->recomendacion.usuarioReceptor;
    printf("Ingrese el nombre de la pelicula que desea recomendar\n");
    fflush(stdin);
    gets(nombrePelicula);
    peliculaArbol=buscarPeliNombre(arbolAltas, nombrePelicula);
    while(!peliculaArbol)
    {
        printf("La pelicula no existe o fue dada de baja. Ingrese otro nombre por favor\n");
        fflush(stdin);
        gets(nombrePelicula);
        peliculaArbol=buscarPeliNombre(arbolAltas, nombrePelicula);
    }
    printf("¿Desea enviarle un mensaje al destinatario?\n");
    fflush(stdin);
    gets(mensaje);
    strcpy(nuevaRecomendacion->recomendacion.mensaje, mensaje);
    nuevaRecomendacion->recomendacion.peli=
        nuevaRecomendacion->recomendacion.mensajeVisto=0;

=======
nodoRecomendacion * crearRecomendacion(nodoRecomendacion * listaRecomendaciones, int idRemitente, nodoUsuario * listaAltas, nodoUsuario * listaBajas)
{
    nodoRecomendacion * nuevaRecomendacion=malloc(sizeof(nodoRecomendacion));
>>>>>>> de19114a7f15ec715afd09763f59dc73ea98dde3

}

void muestraRecomendacionesActivas (stRecomendacion recoActiva)
{
    nodoUsuario * usuario;
    if (recoActiva.mensajeVisto==0)
    {
        printf("--------------------------------------\n");
        printf("De: %s\n", recoActiva.remitente);
        printf("Mensaje: %s\n", usuario.nombreUsuario);
        printf("--------------------------------------\n");
<<<<<<< HEAD
        printf("Te recomiendan ver la siguiente peli:\n");
        mostrarPelicula(recoActiva.peli);
    }
}

void muestraTodasRecomendaciones (stRecomendacion reco)
{

}
=======
        printf("Te recomienda ver la siguiente peli:\n");


    }
>>>>>>> de19114a7f15ec715afd09763f59dc73ea98dde3

}

void muestraTodasRecomendaciones (stRecomendacion reco)
{
    stRecomendacion p_reco;
}
