#include "Usuarios.H"

///////////////////////////////////////////////////////////////////////////
/////////////////LISTA DE USUARIOS/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

nodoUsuario * inicLista()
{
    return NULL;
}

void recorreListaUsuarios(nodoUsuario * LDL)
{
    if(LDL)
    {
        muestraUsuario(LDL->usr);
        recorreListaUsuarios(LDL->sig);
    }
}

void pasarDeArchivoUsuariosToLDL(char archivo[], nodoUsuario ** listaAlta, nodoUsuario ** listaBaja)///PASA USUARIOS DEL ARCHIVO A LA LISTA
{
    FILE *usuarios;
    stUsuario pasaUsuario;
    usuarios=fopen(archivo, "rb");
        while(!feof(usuarios))
        {
            fread(&pasaUsuario, sizeof(stUsuario), 1, usuarios);
            if(!feof(usuarios))
                if(pasaUsuario.eliminado==0)
                    *listaAlta=agregarAlFinalUsuario(creaNodoUsuario(pasaUsuario), *listaAlta);
                else
                    *listaBaja=agregarAlFinalUsuario(creaNodoUsuario(pasaUsuario), *listaBaja);
        }

    fclose(usuarios);
}

nodoUsuario * creaNodoUsuario(stUsuario usuarioNuevo)///CREA UN NODO DE USUARIO
{
    nodoUsuario * nuevoUsr=malloc(sizeof(nodoUsuario));
    nuevoUsr->usr=usuarioNuevo;
    nuevoUsr->listaPelis=inicLista();
    nuevoUsr->sig=inicLista();
    return nuevoUsr;
}

int consultaExistenciaUsuario(nodoUsuario * LDL, char nombre[])///VERIFICA EXISTENCIA DE USUARIO EN LA LISTA. RETORNA 1 SI EXISTE.
{
    int existe=0;
    if(LDL)
    {
        if(strcmp(LDL->usr.nombreUsuario, nombre)==0)
            existe=1;
        else
            existe=consultaExistenciaUsuario(LDL->sig, nombre);
    }
    return existe;
}

nodoUsuario * agregarAlFinalUsuario(nodoUsuario * nuevoUsr, nodoUsuario * LDL)
{
    nodoUsuario * aux;
    if(!LDL)
        LDL=nuevoUsr;
    else
    {
        aux=buscarUltimoNodoUsuario(LDL);
        aux->sig=nuevoUsr;
        aux->listaPelis=inicLista();
    }
    return LDL;
}

nodoUsuario * agregarUsuario(nodoUsuario * LDL)///AGREGA UN USUARIO A LA LISTA
{
    nodoUsuario * nuevoNodo;
    stUsuario usuarioNuevo;
    usuarioNuevo=crearUsuario(LDL);///SE PASA LA LISTA, DEBIDO A QUE SE NECESITA PARA RECUPERAR EL ÚLTIMO
    nuevoNodo=creaNodoUsuario(usuarioNuevo);
    LDL=agregarAlFinalUsuario(nuevoNodo, LDL);
    return LDL;
}

nodoUsuario * buscarUltimoNodoUsuario(nodoUsuario * LDL)///RETORNA EL ÚLTIMO ID DE USUARIO DE LA LISTA
{
    nodoUsuario * aux=LDL;
    if(aux)
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
    return aux;
}

int devuelveUltimoIDUsuario(nodoUsuario * LDL)///RETORNA EL ÚLTIMO USUARIO DE LA LISTA.
{
    int ultimoID=0;
    nodoUsuario * aux=LDL;
    if(aux)
    {
        while(aux->sig)
        {
            aux=aux->sig;
        }
        ultimoID=aux->usr.idUsuario;
    }
    return ultimoID;
}

nodoUsuario * eliminaNodo(nodoUsuario * LDL)///ELIMINA EL NODO Y DA LA REFERENCIA AL SIGUIENTE
{
    nodoUsuario * aux;
    aux=LDL;
    LDL=LDL->sig;
    free(aux);
    return LDL;
}

nodoUsuario * buscaUsuarioNombre(nodoUsuario * LDL, char nombreUsuario[])
{
    nodoUsuario * usuarioEncontrado=NULL;
    if(LDL)
    {
        if(strcmp(LDL->usr.nombreUsuario, nombreUsuario)==0)
            usuarioEncontrado=LDL;
        else
            usuarioEncontrado=buscaUsuarioNombre(LDL->sig, nombreUsuario);
    }
    return usuarioEncontrado;
}

nodoUsuario * buscaUsuarioID(nodoUsuario * LDL, int ID)
{
    nodoUsuario * usuarioEncontrado=NULL;
    if(LDL)
    {
        if(LDL->usr.idUsuario==ID)
            usuarioEncontrado=LDL;
        else
            usuarioEncontrado=buscaUsuarioID(LDL->sig, ID);
    }
    return usuarioEncontrado;
}

void cambiaEstadoUsuario(nodoUsuario *LDL)
{
    if(LDL->usr.eliminado==1)
        LDL->usr.eliminado=0;
    else
        LDL->usr.eliminado=1;
}


///////////////////////////////////////////////////////////////////////////
/////////////////ESTRUCTURA DE USUARIOS////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void modificaDatosPersonales(nodoUsuario * LDL)
{
    int opcion;
    printf("Ingrese el numero de opción del campo que desea editar\n");
    printf("[1]Nombre: %s\n", LDL->usr.nombreUsuario);
    printf("[2]Genero: %c\n", LDL->usr.genero);
    printf("[3]Pais: %s\n", LDL->usr.pais);
    printf("[4]A%co de nacimiento: %d\n", 164, LDL->usr.anioNacimiento);
    printf("[5]Cambiar contraseña\n");
    scanf("%d", &opcion);
    while ((opcion<1) && (opcion>6))
    {
        printf("Ingrese una opción v%clida.\n",160);
        scanf("%d", &opcion);
    }
    LDL->usr=modificaUsuario(LDL->usr, opcion);///ENVÍA OPCION Y POSICION, EDITA EL CAMPO INDICADO POR USUARIO.
}

stUsuario modificaUsuario(stUsuario usuarioAModificar, int opcion)
{
    char password[11];
    int passOK;
    switch(opcion)
    {
    case 1:
        printf("Ingrese el nuevo nombre de usuario:\n");
        fflush(stdin);
        gets(usuarioAModificar.nombreUsuario);
        break;
    case 2:
        printf("Ingrese el nuevo genero:\n");
        fflush(stdin);
        scanf("%c", &usuarioAModificar.genero);
        break;
    case 3:
        printf("Ingrese el nuevo pa%cs de nacimiento:\n", 161);
        fflush(stdin);
        gets(usuarioAModificar.pais);
        break;
    case 4:
        printf("Ingrese el nuevo a%co de nacimiento:\n", 164);
        scanf("%d", &usuarioAModificar.anioNacimiento);
        break;
    case 5:
        printf("Ingrese la contrase%ca (DEBE TENER 10 CARACTERES):\n", 164);
        fflush(stdin);
        gets(password);
        passOK=validaLongitudPassword(password);
        while(passOK==0)
        {
            printf("La contrase%ca debe tener 10 caracteres, intente nuevamente. \n",164);
            fflush(stdin);
            gets(password);
            passOK=validaLongitudPassword(password);
        }
        contraseniaUsuario(password, usuarioAModificar.pass);
        break;
    }
    return usuarioAModificar;
}

stUsuario crearUsuario(nodoUsuario * LDL)///CREA UN TIPO STRUCT USUARIO
{
    stUsuario usuarioVacio;
    int passOK, existe;
    char password[11];
    usuarioVacio.idUsuario=devuelveUltimoIDUsuario(LDL)+1;
    printf("Ingrese el nombre de usuario:\n");
    fflush(stdin);
    gets(usuarioVacio.nombreUsuario);
    existe=consultaExistenciaUsuario(LDL, usuarioVacio.nombreUsuario);
    while(existe==1)
    {
        printf("Ese nombre ya est%c en uso, ingrese otro\n", 160);
        gets(usuarioVacio.nombreUsuario);
        existe=consultaExistenciaUsuario(LDL, usuarioVacio.nombreUsuario);
    }
    printf("Ingrese el genero con el que m%cs se sienta identificado (1 letra porfis):\n",160);
    fflush(stdin);
    scanf("%c", &usuarioVacio.genero);
    printf("Ingrese el pais de origen:\n");
    fflush(stdin);
    gets(usuarioVacio.pais);
    printf("Ingrese el a%co de nacimiento:\n",164);
    scanf("%d", &usuarioVacio.anioNacimiento);
    printf("Ingrese la contrase%ca (DEBE TENER 10 CARACTERES):\n",164);
    fflush(stdin);
    gets(password);
    passOK=validaLongitudPassword(password);
    while(passOK==0)
    {
        printf("La contraseña debe tener 10 caracteres, intente nuevamente. \n");
        fflush(stdin);
        gets(password);
        passOK=validaLongitudPassword(password);
    }
    contraseniaUsuario(password, usuarioVacio.pass);
    usuarioVacio.eliminado=0;
    usuarioVacio.admin=0;
    return usuarioVacio;
}

int validaLongitudPassword(char password[])///VERIFICA QUE EL PASSWORD TENGA 10 CARACTERES.
{
    int si;
    if (strlen(password)==10)
        si=1;
    else
        si=0;
    return si;
}

void muestraUsuario(stUsuario usuario)
{
    printf("--------------------------------------\n");
    printf("ID: %d\n", usuario.idUsuario);
    printf("Nombre: %s\n", usuario.nombreUsuario);
    printf("Genero: %C\n", usuario.genero);
    printf("Pais: %s\n", usuario.pais);
    printf("A%co: %d\n",164, usuario.anioNacimiento);
    if(usuario.admin==0)
        printf("Tipo: Usuario\n");
    else
        printf("Tipo: Admin\n");
    if(usuario.eliminado==1)
        printf("Estado: Inactivo\n");
    else
        printf("Estado: Activo\n");
    printf("--------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////
/////////////////FUNCIONES CON ARCHIVOS////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

stUsuario cargaArchivoUsuarios(char archivoUsuarios[], nodoUsuario * LDL)
{
    stUsuario nuevoUsuario;
    nuevoUsuario=crearUsuario(LDL);
    escribeUsuarioEnArchivo(archivoUsuarios, nuevoUsuario);
    return nuevoUsuario;
}

void escribeUsuarioEnArchivo(char archivoUsuarios[], stUsuario usuarioAEscribir)
{
    FILE *usuarios;
    usuarios=fopen(archivoUsuarios, "ab");
    fwrite(&usuarioAEscribir, sizeof(stUsuario), 1, usuarios);
    fclose(usuarios);
}

void muestraArchivo(char arch[])
{
    FILE *usuarios;
    stUsuario aux;
    usuarios=fopen(arch, "rb");
    while(!feof(usuarios))
    {
        fread(&aux, sizeof(stUsuario), 1, usuarios);
        if(!feof(usuarios))
        {
            muestraUsuario(aux);
        }
    }
}

void persisteUsuariosArchivo(char archivoUsuarios[], nodoUsuario * listaAlta, nodoUsuario * listaBaja)///GUARDA LA LISTA EN EL ARCHIVO.
{
    FILE *usuarios;
    stUsuario pasaUsuario;
    usuarios=fopen(archivoUsuarios, "wb");
    while(listaAlta)
        {
            pasaUsuario=listaAlta->usr;
            fwrite(&pasaUsuario, sizeof(stUsuario), 1, usuarios);
            listaAlta=eliminaNodo(listaAlta);
        }
    while(listaBaja)
        {
            pasaUsuario=listaBaja->usr;
            fwrite(&pasaUsuario, sizeof(stUsuario), 1, usuarios);
            listaBaja=eliminaNodo(listaBaja);
        }
    fclose(usuarios);
}

///////////////////////////////////////////////////////////////////////////
/////////////////ENCRIPTACIÓN DE CONTRASEÑAS///////////////////////////////
///////////////////////////////////////////////////////////////////////////

void contraseniaUsuario(char contrasenia[], int matContrasenia[][5])///ENCRIPTA LA CONTRASEÑA
{
    int passInt[10], matAscii[2][5], matrizBase[2][2]= {{2,1},{7,4}};
    pasarAscii(contrasenia, passInt);
    asciiAmatriz(5, 2, passInt, matAscii);
    multiplicaMatrices(2, matrizBase, 5, matAscii, matContrasenia);
}

void cargamatriz (int fila, int columna, int m[][columna])
{
    int f, c;
    for (c=0; c<columna; c++)
    {
        for (f=0; f<fila; f++)
        {

            scanf("%d", &m[f][c]);
        }
    }
}

void muestraMatriz (int fila, int columna, int m [][columna])
{
    int f, c;
    for (f=0; f< fila; f++)
    {
        for (c=0; c< columna; c++)
        {
            if (m [f][c] <10)
            {
                printf("[0%d]", m[f][c]);
            }
            else
            {
                printf("[%d]", m[f][c]);
            }
        }
        printf("\n");
    }
}

int multiplicaMatrices(int columna, int m2x2[][columna], int columnaCodigo, int mCodigo[][columnaCodigo], int mEncriptada[][columnaCodigo])
{
    int i, m, n;
    i=0;
    m=0;
    for(n=0; n<columnaCodigo; n++)
    {
        mEncriptada[m][n]=((m2x2[i][i]*mCodigo[m][n])+(m2x2[i][i+1]*mCodigo[m+1][n]));
        mEncriptada[m+1][n]=((m2x2[i+1][i]*mCodigo[m][n])+(m2x2[i+1][i+1]*mCodigo[m+1][n]));
    }
}

int determinanteMatriz (int columna, int m [][columna] )
{
    int determinante;

    determinante= ((m[0][0]*m [1][1])-(m[0][1]*m[1][0]));
    return determinante;
}

void matrizCofactores (int columna, int m[][columna] )
{

    int a, b;
    a=m[0][0];
    b=m[0][1];
    m[0][0]= m[1][1];
    m[0][1]= (m[1][0])*-1;
    m[1][0]= b*-1;
    m[1][1]= a;
}

void cofactoresTraspuesta (int columna, int m[][columna] )
{

    int a;
    a=m[0][1];

    m[0][1]=m[1][0];
    m[1][0]=a;
}

void invierteMatriz (int columna, int fila, int m[][columna], int determinante)
{

    int f, c;
    for (c=0; c<columna; c++)
    {
        for (f=0; f<fila; f++)
        {
            m[f][c]=m[f][c]/determinante;
        }
    }
}

void pasarAscii (char contrasenia [], int pass[10])
{
    int i;

    for (i=0; i<10; i++)
    {
        pass[i]=contrasenia[i];
    }
}

void asciiAmatriz (int columna, int fila, int a[], int mCodigo[][columna])
{
    int f, c, i=0;

    for (c=0; c<columna; c++)
    {
        for (f=0; f<fila; f++)
        {
            mCodigo[f][c]= a[i];
            i++;
        }
    }
}

void matrizInversa(int matriz[][2])
{
    int det;
    det=determinanteMatriz(2, matriz);
    matrizCofactores(2, matriz);
    cofactoresTraspuesta(2, matriz);
    invierteMatriz(2, 2, matriz, det);
}
