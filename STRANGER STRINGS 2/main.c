#include "structs.h"


int main()
{
    int i;
    nodoArbol *arbolActivo = inicArbol();
    nodoArbol *arbolEliminado = inicArbol();

    arbolActivo = creaYcargaPeliculaAlArbol(arbolActivo, arbolEliminado);

preorder(arbolActivo);
//system("cls");
//modificarNodoArbol(arbolActivo, arbolEliminado);
//preorder(arbolActivo);
    return 0;
}
