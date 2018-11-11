#include "structs.h"

stPelisVistas valoracionPorUsuario(stPelisVistas peliVista);
///retorna un stpelicula con la calificacion de usuario ingresada
void pasarDeArchivoPelisVistasToLDL(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja, nodoArbol * arbolAlta, nodoArbol * arbolBaja);///REVISAR
//
void actualizarPeliculasVistas(char ruta [], nodoUsuario ** lDlAlta, nodoUsuario ** lDlBaja);
//
void actualizarPvAlta (FILE * archivo, nodoUsuario ** lDlAlta);
void actualizarPvBaja (FILE * archivo, nodoUsuario ** lDlBaja);
nodoListaPelicula * buscarUsuarioID(nodoUsuario * lDl, int idUsuario);
///Busca usuario por ID y retorna el mismo si es que existe, si no NULL
void agregarPpiolListaPeliculas (nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo);
///Agrega nodo al Ppio de lista de peliculas
nodoListaPelicula * crearNodoListaPeliculas(stPelicula peli, int valoracion);
///Retorna un nodoListaPelicula
void borrarUltimaPeliVista(nodoListaPelicula ** lista);
void reproducirPelicula(nodoListaPelicula ** listaUsr, int peliID);

/// //////////////////////////////////////////////////////////////////////////////////////

void inicListaPeliculas(nodoListaPelicula ** lista);///ok
nodoListaPelicula * crearNodoLista(stPelicula peli, int valUser);///ok
void agregarAlPrincipio(nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo);///ok
void agregarAlFinal(nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo);///ok
void agregarEnOrdenPorNombreDePelicula(nodoListaPelicula ** lista, nodoListaPelicula * nuevoNodo);///ok
void mostrarLista(nodoListaPelicula * lista);/// SAKE // modularizar
void borrarNodoPorIdPelicula(nodoListaPelicula ** lista, int id);///ok
//void archivoTo;
persistirPeliculasVistas(); // esta funci�n realizar� la persistencia de todas las pel�culas vistas en el archivo correspondiente
