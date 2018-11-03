#include <stdio.h>
#include <stdlib.h>
#include "Usuarios.H"

const char archUsuarios[15]="usuarios.dat";

int main()
{
    printf("Hello world!\n");
    nodoUsuario * listaAltas;
    nodoUsuario * listaBajas;
    listaAltas=inicLista();
    listaBajas=inicLista();
    //cargaArchivoUsuarios(archUsuarios, ListaDeListas);
    //muestraArchivo(archUsuarios);
    pasarDeArchivoUsuariosToLDL(archUsuarios, &listaAltas, &listaBajas);
    //ListaDeListas=agregarUsuario(ListaDeListas);
    recorreListaUsuarios(listaAltas);
    //persisteUsuariosArchivo(archUsuarios, ListaDeListas);
    return 0;
}
