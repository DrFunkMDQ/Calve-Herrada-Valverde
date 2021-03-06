#include "structs.h"


///////////////////////////////////////////////////////////////////////////
/////////////////ESTRUCTURA NODO USUARIOS//////////////////////////////////
///////////////////////////////////////////////////////////////////////////

nodoUsuario * inicLista();///INICIALIZA LA LISTA;
void recorreListaUsuarios(nodoUsuario * LDL);///RECORRE Y MUESTRA LA LISTA (UNICAMENTE USUARIOS)
void muestraNodoUsuario(nodoUsuario * usuario);///MUESTRA UN NODO INDIVIDUAL.
void pasarDeArchivoUsuariosToLDL(char archivo[], nodoUsuario ** listaAlta, nodoUsuario ** listaBaja);///PASA USUARIOS DEL ARCHIVO A LA LISTA
nodoUsuario * creaNodoUsuario(stUsuario usuarioNuevo);///CREA UN NODO DE USUARIO
int consultaExistenciaUsuario(nodoUsuario * listaAlta, nodoUsuario * listaBaja, char nombre[]);///VERIFICA EXISTENCIA DE USUARIO EN LA LISTA. RETORNA 1 SI EXISTE.
nodoUsuario * agregarAlFinalUsuario(nodoUsuario * nuevoUsr, nodoUsuario * LDL);
nodoUsuario * agregarUsuario(nodoUsuario * LDL);///AGREGA UN USUARIO A LA LISTA
nodoUsuario * buscarUltimoNodoUsuario(nodoUsuario * LDL);///RETORNA EL �LTIMO ID DE USUARIO DE LA LISTA
int devuelveUltimoIDUsuario(nodoUsuario * listaAlta, nodoUsuario * listaBaja);///RETORNA EL �LTIMO USUARIO DE LA LISTA.
nodoUsuario * agregaUsuarioEnOrden(nodoUsuario *LDL, nodoUsuario * nuevoNodo);
///////////////////////////////////////////////////////////////////////////
/////////////////ESTRUCTURA DE USUARIOS////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

stUsuario crearUsuario(nodoUsuario * listaAlta, nodoUsuario * listaBaja);///CREA UN USUARIO
stUsuario modificaUsuario(stUsuario usuarioAModificar, int opcion);
int validaLongitudPassword(char password[]);///VERIFICA QUE EL PASSWORD TENGA 10 CARACTERES.
stUsuario cargaArchivoUsuarios(char archivoUsuarios[], nodoUsuario * listaAlta, nodoUsuario * listaBaja);
void escribeUsuarioEnArchivo(char archivoUsuarios[], stUsuario usuarioAEscribir);
///////////////////////////////////////////////////////////////////////////
/////////////////FUNCIONES CON ARCHIVOS////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

stUsuario cargaArchivoUsuarios(char archivoUsuarios[], nodoUsuario * listaAlta, nodoUsuario * listaBaja);
void escribeUsuarioEnArchivo(char archivoUsuarios[], stUsuario usuarioAEscribir);
void muestraArchivo(char arch[]);
void persisteUsuariosArchivo(char archivoUsuarios[], nodoUsuario ** listaAlta, nodoUsuario ** listaBaja);
///////////////////////////////////////////////////////////////////////////
/////////////////ENCRIPTACI�N DE CONTRASE�AS///////////////////////////////
///////////////////////////////////////////////////////////////////////////

void contraseniaUsuario(char contrasenia[], int matContrasenia[][5]);///ENCRIPTA LA CONTRASE�A
void cargamatriz (int fila, int columna, int m[][columna]);
void muestraMatriz (int fila, int columna, int m [][columna]);
int multiplicaMatrices(int columna, int m2x2[][columna], int columnaCodigo, int mCodigo[][columnaCodigo], int mEncriptada[][columnaCodigo]);
int determinanteMatriz (int columna, int m [][columna] );
void matrizCofactores (int columna, int m[][columna] );
void cofactoresTraspuesta (int columna, int m[][columna] );
void invierteMatriz (int columna, int fila, int m[][columna], int determinante);
void pasarAscii (char contrasenia [], int pass[10]);
void asciiAmatriz (int columna, int fila, int a[], int mCodigo[][columna]);
void matrizInversa(int matriz[][2]);
