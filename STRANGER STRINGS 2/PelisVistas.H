#include "structs.h"


void pasarDeArchivoPelisVistasToLDL(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja, nodoArbol * arbolAlta, nodoArbol * arbolBaja);///REVISAR
//
void actualizarPeliculasVistas(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja);
//
void actualizarPvAlta (FILE * archivo, nodoUsuario ** lDlAlta, int * peliVistaID);
void actualizarPvBaja (FILE * archivo, nodoUsuario ** lDlBaja, int * peliVistaID);
nodoListaPelicula * buscarListaPeliculaUsuarioID(nodoUsuario * lDl, int idUsuario, int * flag);
///Busca usuario por ID y retorna el mismo si es que existe, si no NULL
nodoListaPelicula * agregarPpiolListaPeliculas (nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo);
///Agrega nodo al Ppio de lista de peliculas
nodoListaPelicula * crearNodoListaPeliculas(stPelicula peli, int valoracion);
///Retorna un nodoListaPelicula
void borrarUltimaPeliVista(nodoListaPelicula ** lista);
void reproducirPelicula(nodoListaPelicula ** listaUsr, int peliID, stPelicula peli);
stPelisVistas crearPeliVista(int valoracion, int peliID, int usrID, int * peliVistaID);
int existePeliVista(nodoListaPelicula * listaUsr, stPelicula nuevaPeli);
void subProgramaReproduccion (nodoListaPelicula ** listaUsr, nodoArbol * arbolAlta);

/// //////////////////////////////////////////////////////////////////////////////////////

void inicListaPeliculas(nodoListaPelicula ** lista);///ok
nodoListaPelicula * crearNodoLista(stPelicula peli, int valUser);///ok
nodoListaPelicula * agregarAlFinal(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo);///ok
nodoListaPelicula * agregarEnOrdenPorNombreDePelicula(nodoListaPelicula * lista, nodoListaPelicula * nuevoNodo);///ok
void mostrarLista(nodoListaPelicula * lista);/// SAKE // modularizar
nodoListaPelicula * borrarNodoPorIdPelicula(nodoListaPelicula * lista, int id);///ok
//void archivoTo;
persistirPeliculasVistas(); // esta funci�n realizar� la persistencia de todas las pel�culas vistas en el archivo correspondiente
