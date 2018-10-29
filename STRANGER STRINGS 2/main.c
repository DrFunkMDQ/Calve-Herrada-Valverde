#include <stdio.h>
#include <stdlib.h>
#include "Usuarios.H"

const char archUsuarios[15]="usuarios.dat";

int main()
{
    printf("Hello world!\n");
    nodoUsuario * ListaDeListas;
    ListaDeListas=inicLista();
    //cargaArchivoUsuarios(archUsuarios, ListaDeListas);
    //muestraArchivo(archUsuarios);
    ListaDeListas=pasarDeArchivoUsuariosToLDL(archUsuarios, ListaDeListas);
    ListaDeListas=agregarUsuario(ListaDeListas);
    recorreListaUsuarios(ListaDeListas);
    return 0;
}
