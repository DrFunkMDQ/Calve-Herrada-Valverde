#include "Usuarios.H"

///////////////////////////////////////////////////////////////////////////
/////////////////ESTRUCTURA DE USUARIOS////////////////////////////////////
///////////////////////////////////////////////////////////////////////////



nodoUsuario * inicLista()
{
    return NULL;
}

nodoUsuario * recorreListaUsuarios(nodoUsuario * LDL)
{
    printf("fff");
    if(LDL)
    {
        printf("fff");
        muestraNodoUsuario(LDL);
        printf("fff");
        recorreListaUsuarios(LDL->sig);
    }
}

void muestraNodoUsuario(nodoUsuario * usuario)
{
    char tipoUser[10], estado[10];
    printf("--------------------------------------\n");
    printf("ID: %d\n", usuario->usr.idUsuario);
    printf("Nombre: %s\n", usuario->usr.nombreUsuario);
    printf("Genero: %C\n", usuario->usr.genero);
    printf("Pais: %s\n", usuario->usr.pais);
    printf("A%co: %d\n",164, usuario->usr.anioNacimiento);
    if(usuario->usr.admin==0)
        strcpy(tipoUser, "Usuario");
    else
        strcpy(tipoUser, "Admin");
    printf("Tipo de usuario: %s\n", tipoUser);
    if(usuario->usr.eliminado==1)
        strcpy(estado,"Inactivo");
    else
        strcpy(estado, "Activo");
    printf("Estado: %s\n", estado);
    printf("--------------------------------------\n");
}

nodoUsuario * pasarDeArchivoUsuariosToLDL(char archivo[], nodoUsuario * LDL)///PASA USUARIOS DEL ARCHIVO A LA LISTA
{
    FILE *usuarios;
    stUsuario pasaUsuario;
    nodoUsuario * usuarioAgregar;
    usuarios=fopen(archivo, "rb");
    if((usuarios=fopen(archivo, "rb"))!=NULL)
    {
        while(!feof(usuarios))
        {
            fread(&pasaUsuario, sizeof(stUsuario), 1, usuarios);
            if(!feof(usuarios))
            {
                usuarioAgregar=creaNodoUsuario(pasaUsuario);
                agregarAlFinalUsuario(usuarioAgregar, LDL);
            }
        }
    }

    fclose(usuarios);
    return LDL;
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
    usuarioNuevo=crearUsuario(LDL);
    nuevoNodo=creaNodoUsuario(usuarioNuevo);
    LDL=agregarAlFinalUsuario(nuevoNodo, LDL);
    return LDL;
}

nodoUsuario * buscarUltimoNodoUsuario(nodoUsuario * LDL)///RETORNA EL ÚLTIMO ID DE USUARIO DE LA LISTA
{
    nodoUsuario * aux=LDL;
    if(aux)
        while(aux->sig)
        {
            aux=aux->sig;
        }
    return aux;
}

int devuelveUltimoIDUsuario(nodoUsuario * LDL)///RETORNA EL ÚLTIMO USUARIO DE LA LISTA.
{
    int ultimoID=1;
    nodoUsuario * aux=LDL;
    if(aux)
    {
        while(aux)
        {
            aux=aux->sig;
        }
        ultimoID=aux->usr.idUsuario;
    }
    return ultimoID;
}

///////////////////////////////////////////////////////////////////////////
/////////////////ESTRUCTURA DE USUARIOS////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

stUsuario crearUsuario(nodoUsuario * LDL)///CREA UN USUARIO
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
