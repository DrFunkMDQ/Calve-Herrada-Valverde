#include "Peliculas.H"
///Struct Pelis
void mostrarPelicula(stPelicula pelicula){
printf("............\n\t-\t%d", pelicula.idPelicula);
printf("\n\tNOMBRE:\t%s\n", pelicula.nombrePelicula);
printf("\tDIRECTOR:\t%s\n", pelicula.director);
printf("\tGENERO:\t%s\n", pelicula.genero);
printf("\tPAIS:\t%s\n", pelicula.pais);
printf("\tAÑO:\t%d\n", pelicula.anio);
printf("\tVALORACION:\t%d\n", pelicula.valoracion);
printf("\tPM:\t%d\n", pelicula.pm);
if(pelicula.eliminado == 1)
printf("ELIMINADO:\tSI\n");
else
    printf("ELIMINADO:\tNO\n");
}
stPelicula crearPelicula()//En esto hay que agregar lo de meterse a buscar a ver si existe ya y lo del id autoincremental
{
stPelicula peliNueva;
printf("Ingrese nombre de pelicula\n");
scanf("%s", &peliNueva.nombrePelicula);
printf("Ingrese director\n");
scanf("%s", &peliNueva.director);
printf("Ingrese genero\n");
scanf("%s", &peliNueva.genero);
printf("Ingrese pais\n");
scanf("%s", &peliNueva.pais);
printf("Ingrese año\n");
scanf("%d", &peliNueva.anio);
printf("Ingrese valoracion\n");
scanf("%d", &peliNueva.valoracion);
printf("Ingrese PM\n");
scanf("%d", &peliNueva.pm);
peliNueva.eliminado = 0;
return peliNueva;}
///ARBOLES DE PELIS
nodoArbol *inicArbol()
{
    return NULL;
}

void preorder(nodoArbol *arbol)
{
    if(arbol)
    {
        mostrarPelicula(arbol->pelicula);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoArbol *arbol)
{
    if(arbol)
    {
        inorder(arbol->izq);
        mostrarPelicula(arbol->pelicula);
        inorder(arbol->der);
    }
}

void postorder(nodoArbol *arbol)
{
    if(arbol)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        mostrarPelicula(arbol->pelicula);
    }
}

