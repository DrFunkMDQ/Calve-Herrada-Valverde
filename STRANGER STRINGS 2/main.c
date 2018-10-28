#include <stdio.h>
#include <stdlib.h>
#include "Usuarios.H"

const char archUsuarios[15]="usuarios.dat";

int main()
{
    printf("Hello world!\n");
    nodoUsuario * ListaDeListas;
    ListaDeListas=inicLista();
    pasarDeArchivoUsuariosToLDL(archUsuarios, ListaDeListas);
    muestraNodoUsuario(ListaDeListas);
    printf("aaaa");
    recorreListaUsuarios(ListaDeListas);
    return 0;
}
