#include "structs.h"


int main()
{
    int i;
    nodoArbol *arbolActivo = inicArbol();
    nodoArbol *arbolEliminado = inicArbol();
    arbolActivo = creaYcargaPeliculaAlArbol(arbolActivo, arbolEliminado);
    altaBajaPelicula(&arbolActivo, &arbolEliminado);
    printf("ACTIVO\n");
    preorder(arbolActivo);
    printf("ELIMINADO\n");
    preorder(arbolEliminado);
//system("cls");
//modificarNodoArbol(arbolActivo, arbolEliminado);
//preorder(arbolActivo);
    return 0;
}
