#include "structs.h"

///PELICULA
stPelicula modificaPelicula(nodoArbol *arbolActivo, nodoArbol *arbolEliminado, stPelicula pelicula);
void mostrarPelicula(stPelicula pelicula);  //Muestra una pelicula
stPelicula crearPelicula(nodoArbol *arbolActivo, nodoArbol *arbolEliminado);
void insertarNombre(nodoArbol *arbolActivo, nodoArbol *arbolEliminado, char *nombre[]);
void insertarAnio(int *anio);
void insertarDirector(char *director);
void insertarGenero(char *genero);
void insertarPais(char *pais);
void insertarPM(int *pm);
void insertarValoracion(int *valoracion);
///ARBOLES
void preorder(nodoArbol *arbol);    //Muestra preorder todo el arbol
void inorder(nodoArbol *arbol);     //Muestra inorder todo el arbol
void postorder(nodoArbol *arbol);   //Muestra postorder todo el arbol
nodoArbol *borrarNodoArbolPelicula(nodoArbol *arbol, int id);
nodoArbol *insertarNuevoArbol(nodoArbol *arbol, nodoArbol *nuevoArbol); //Inserta una nueva pelicula en el arbol
nodoArbol *nodoMasDerecho(nodoArbol *arbol); //Busca y retorna el nodo mas derecho
nodoArbol *nodoMasIzquierdo(nodoArbol *arbol);
nodoArbol *borrarArbol(nodoArbol *arbol);   //Borra todo el arbol
nodoArbol *inicArbol(); //LA MAS IMPORTANTE
//////// ADMINISTRADOR

//////// USUARIO
nodoArbol *buscarPeliID(nodoArbol *arbol, int id);  //Busca la existencia de una pelicula por 'ID' y la retorna
nodoArbol *buscarPeliNombre(nodoArbol *arbol, char nombre[]); //Busca la existencia de una pelicula por 'NOMBRE' y la retorna
//////// SISTEMA
int ultimoIDPelicula(nodoArbol *arbolActio, nodoArbol *arbolEliminado);
int existenciaArbolPeliculaNombre(nodoArbol *arbol, char nombre[]);
void modificarNodoArbol(nodoArbol *arbolActivo, nodoArbol *arbolEliminado);
int existenciaPeliculaNombre(nodoArbol *arbolActivo, nodoArbol *arbolEliminado, char nombre[]);

