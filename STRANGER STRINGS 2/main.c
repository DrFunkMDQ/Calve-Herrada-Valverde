#include "structs.h"


int main()
{
    int a = 0;
    int b = 0;
    nodoArbol *arbolActivo = inicArbol();
    nodoArbol *arbolEliminado = inicArbol();
    levantarArboles(&arbolActivo, &arbolEliminado);
    inorder(arbolActivo);
    modificarNodoArbol(arbolActivo, arbolEliminado);
    inorder(arbolActivo);

    return 0;
}
