#include <stdio.h>
#include <stdlib.h>
#include "Usuarios.H"

const char archUsuarios[15]="usuarios.dat";

int main()
{
    printf("Hello world!\n");
    nodoUsuario * usuarioBaja;
    nodoUsuario * listaAltas;
    nodoUsuario * listaBajas;
    listaAltas=inicLista();
    listaBajas=inicLista();
    //cargaArchivoUsuarios(archUsuarios, ListaDeListas);
    //muestraArchivo(archUsuarios);
    pasarDeArchivoUsuariosToLDL(archUsuarios, &listaAltas, &listaBajas);
    //usuarioBaja=buscaUsuarioID(listaBajas, 1);
    //cambiaEstadoUsuario(usuarioBaja);
    //listaAltas=agregaUsuarioEnOrden(listaAltas, extraeNodoUsuarioID(&listaBajas, 1));
    //listaAltas=subProgramaAgregarUsuario(listaAltas, listaBajas);
    recorreListaUsuarios(listaAltas);
    //persisteUsuariosArchivo(archUsuarios, &listaAltas, &listaBajas);
    printf("asddd\n");
    recorreListaUsuarios(listaBajas);
    printf("puto");
    return 0;
}
