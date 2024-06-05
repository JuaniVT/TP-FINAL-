#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//====================================================================================
// TRABAJO FINAL PROGRAMACION I
// Integrantes: Manuel Segovia, Juan Ignacio Valle Torres, Ignacio Agustin Villarreal
// SISTEMA PARA CONCESIONARIA DE AUTOS
//====================================================================================

typedef struct   // CREACION DE OTRA ESTRUCTURA PARA REGISTRARSE Y PODER LOGEARSE EN EL SISTEMA
{
    char contra [20];
    char user [15];
} usuario;

void registro_En_El_sistema (char []);
usuario crear_Cuenta (FILE*);
usuario nombre_Usuario (FILE*, usuario*);
usuario contrasena (FILE*, usuario*);
int comprobar_Nombre (FILE*, char []);
int comprobar_Contra (FILE *, char []);
int verificar_Caracteres (char [], int);
int verificar_Existencia (FILE*, char []);
int verificar_Space (char[]);
int main()
{
    // VARIABLES DEL MAIN =====================
    int ops = 1; // SWITCH
    char seguirMain;
    // ========================================
    // CREACION DE ARCHIVOS ===================
    char autosArch [] = "autos.bin";
    char personas [] = "personas.bin";
    char ventas [] = "ventas.bin";
    // ========================================

    while (ops != 0)
    {
        printf ("------------------------------------------\n");
        printf ("BIENVENIDO A VOLSWAGEN\n");
        printf ("------------------------------------------\n");
        printf ("1- LOGIN\n");
        printf ("2- REGISTRARSE\n");
        printf ("0- PARA CERRAR EL SISTEMA\n");
        printf ("INGRESE AQUI: ");
        fflush (stdin);
        scanf ("%d", &ops);
        printf ("\n");
        switch (ops)
        {
        case 2:
            registro_En_El_sistema (personas);
            break;
        case 0:
            printf ("GRACIAS POR CONFIAR EN NOSOTROS\n");
            break;
        default:
            printf ("------------------------------------------------------------------\n");
            printf ("DISCULPE PERO EL VALOR INGRESADO NO CORRESPONDE A NINGUN EJERCICIO\n");
            printf ("Ingrese cualquier elemento p/continuar\n");
            printf ("AQUI: ");
            fflush (stdin);
            scanf ("%c", &seguirMain);
            break;
        }
    }
    return 0;
}
// registro
void registro_En_El_sistema (char archivo [])
{
    printf ("------------------------------------------------------------------\n");
    printf ("CREACION DE USUARIO\n");
    printf ("------------------------------------------------------------------\n");
    FILE *arch = fopen (archivo, "a+b");
    usuario persona;
    if (arch != NULL)
    {
        persona = crear_Cuenta (arch);
        fwrite (&persona, sizeof (usuario), 1, arch);
    }
    fclose (arch);
}
usuario crear_Cuenta (FILE *arch)
{
    usuario personaAux;
    nombre_Usuario (arch, &personaAux);
    contrasena (arch, &personaAux);

    return personaAux;
}
// registro al sistema de usuario
usuario nombre_Usuario (FILE* arch, usuario *persona)
{
    int variableUser = 1;
    while (variableUser != 0)
    {
        printf ("Ingrese su nombre de usuario: ");
        fflush (stdin);
        gets ((*persona).user);
        variableUser = comprobar_Nombre (arch, (*persona).user);
        if (variableUser != 0)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("REINGRESAR NOMBRE DE USUARIO\n");
            printf ("------------------------------------------------------------------\n");
        }
    }
    return (*persona);
}
// verificar contraseña
usuario contrasena (FILE* arch, usuario *persona)
{
    int variableContra = 1;
    while (variableContra != 0)
    {
        printf ("Ingrese una contrasena: ");
        fflush (stdin);
        gets ((*persona).contra);
        variableContra = comprobar_Nombre (arch, (*persona).contra);
        if (variableContra != 0)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("REINGRESAR NOMBRE DE USUARIO\n");
            printf ("------------------------------------------------------------------\n");
        }
    }
    return (*persona);
}
//funcion que comprueba el nombre de usuario ===============
int comprobar_Nombre (FILE *arch, char palabra [])
{
    int minNombre = 8;
    int flag = 0;
    int flag2 = 0;
    int flag3 = 0;
    flag = verificar_Caracteres (palabra, minNombre);
    if (flag == 1)
    {
        printf ("-CANTIDAD INSUFICIENTE DE CARACTERES-\n");
    }
    flag2 = verificar_Existencia (arch, palabra);
    if (flag2 == 2)
    {
        printf ("-EL NOMBRE INGRESADO YA EXISTE-\n");
    }
    flag3 = verificar_Space (palabra);
    if (flag3 == 1)
        {
           printf ("-EL NOMBRE INGRESADO CONTIENE ESPACIOS-\n");
        }
    if (flag != 0 || flag2 != 0 || (flag3 != 0))
        {
            flag = 1;
        }
    return flag;
}
//funcion que comprueba el nombre de usuario ===============
int comprobar_Contra (FILE *arch, char palabra [])
{
    int minContra = 10;
    int flag = 0;
    int flag3 = 0;
    flag = verificar_Caracteres (palabra, minContra);
    if (flag == 1)
    {
        printf ("-CANTIDAD INSUFICIENTE DE CARACTERES-\n");
    }
    flag3 = verificar_Space (palabra);
    if (flag3 == 1)
        {
           printf ("-LA CONTRASENA INGRESADA CONTIENE ESPACIOS-\n");
        }
    if (flag != 0 || flag3 != 0)
        {
            flag = 1;
        }
    return flag;
}
int comprobar_Mayusculas (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag = 0;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] <= 90 && palabra[i] >= 65)
        {
            flag = 1;
        }
    }
    return flag;
}
int comprobar_Minusculas (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag = 0;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] <= 122 && palabra[i] >= 97)
        {
            flag = 1;
        }
    }
    return flag;
}
int comprobar_Numeros (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag = 0;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] <= 57 && palabra[i] >= 48)
        {
            flag = 1;
        }
    }
    return flag;
}
// comprobacion de strlean
int verificar_Caracteres (char palabra [], int min)
{
    int caracteres = strlen (palabra);
    int flag = 1;
    if (caracteres >= min)
    {
        flag = 0;
    }

    return flag;
}
// funcion para comprobar que el nombre ya exista ========
int verificar_Existencia (FILE *arch, char palabra [])
{
    int flag = 0;
    usuario aux;
    fseek (arch, 0, SEEK_SET);
    while (fread (&aux, sizeof (usuario), 1, arch) > 0)
    {
        if (strcmp (aux.user, palabra) == 0)
        {
            flag = 2;
        }
    }
    return flag;
}
// COMPROBAR QUE EL USUARIO NO TENGA SPACE
int verificar_Space (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag3 = 0;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] == 32)
        {
            flag3 = 1;
        }
    }
    return flag3;
}
