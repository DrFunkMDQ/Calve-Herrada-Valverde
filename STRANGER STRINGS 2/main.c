#include "structs.h"


int main()
{
    int i;
    nodoArbol *arbolActivo = inicArbol();
    nodoArbol *arbolEliminado = inicArbol();
stPelicula peli;
FILE*archi = fopen("peliculas.bin", "rb");

while(!feof(archi)){
    fread(&peli, 1, sizeof(stPelicula), archi);
    arbolActivo = insertarNuevoArbol(arbolActivo, crearNodoArbol(peli));
}
fclose(archi);


printf("ARBOL ACTIVO\n\n\n");
    preorder(arbolActivo);
    printf("ELIMINADO\n\n\n");
    preorder(arbolEliminado);
//system("cls");
//modificarNodoArbol(arbolActivo, arbolEliminado);
//preorder(arbolActivo);
    return 0;
}
