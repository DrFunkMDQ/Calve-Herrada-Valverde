#include "structs.h"


int main()
{
    int cantidad;
    nodoArbol *arbolActivo = inicArbol();
    nodoArbol *arbolEliminado = inicArbol();
    /*arbolActivo = creaYcargaPeliculaAlArbol(arbolActivo, arbolEliminado);
    arbolActivo = creaYcargaPeliculaAlArbol(arbolActivo, arbolEliminado);
    arbolActivo = creaYcargaPeliculaAlArbol(arbolActivo, arbolEliminado);
    persistirTodo(arbolActivo, arbolEliminado);*/
    cantidad = cantidadPelisArchivo(0);
    printf("%d", cantidad);
    return 0;
}
