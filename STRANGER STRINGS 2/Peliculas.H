#include "structs.h"

///PELICULA
void mostrarPelicula(stPelicula pelicula);  //Muestra una pelicula
stPelicula crearPelicula();
///ARBOLES
nodoArbol *inicArbol(); //LA MAS IMPORTANTE
void preorder(nodoArbol *arbol);    //Muestra preorder todo el arbol
void inorder(nodoArbol *arbol);     //Muestra inorder todo el arbol
void postorder(nodoArbol *arbol);   //Muestra postorder todo el arbol
nodoArbol *modificarArbol(nodoArbol *arbol, int peliId);    //Modifica una pelicula en un campo especifico (si es q existe)
nodoArbol *borrarArbol(nodoArbol *arbol, int peliId);   //Borra una pelicula(nodoArbol)
nodoArbol *buscarPeliID(nodoArbol *arbol, int peliId);  //Busca la existencia de una pelicula por 'ID' y la retorna
nodoArbol *buscarPeliNombre(nodoArbol *arbol, char nombre[]); //Busca la existencia de una pelicula por 'NOMBRE' y la retorna
nodoArbol *insertarNuevoArbol(nodoArbol *arbol, nodoArbol *nuevoArbol); //Inserta una nueva pelicula en el arbol
nodoArbol *nodoMasDerecho(nodoArbol *arbol); //Busca y retorna el nodo mas derecho
