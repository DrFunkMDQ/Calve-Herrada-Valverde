#include "string.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int idPelicula;
    char nombrePelicula[60];
    char director[30];
    char genero[20];
    char pais[20];
    int anio;
    int valoracion;
    int pm;
    int eliminado;
    char url[100];
} stPelicula;

typedef struct
{
    stPelicula pelicula;
    struct nodoArbol *izq;
    struct nodoArbol *der;
} nodoArbol;

typedef struct
{
    int idPeliVista;
    int idUsuario;
    int idPelicula;
    int valUser;
} stPelisVistas;

typedef struct{
    int admin;
    int idUsuario;
    char nombreUsuario[15];
    char genero;
    char pais[20];
    int pass [2][5];
    int anioNacimiento;
    int eliminado;
}stUsuario;

typedef struct{
    stPelicula pelicula;
    stPelicula * sig;
    int valUser;
} nodoListaPelicula;

typedef struct
{
    stUsuario usr;
    nodoListaPelicula * listaPelis;
    struct nodoUsuario * sig;
} nodoUsuario;

typedef struct
{
    char receptor[15];
    char remitente[15];
    stPelicula peli;
    int mensajeVisto; ///0 SI NO FUE VISTO, 1 SI FUE VISTO.
    char mensaje[100];
}stRecomendacion;

typedef struct
{
    stRecomendacion recomendacion;
    struct nodoRecomendacion * sig;
}nodoRecomendacion;

