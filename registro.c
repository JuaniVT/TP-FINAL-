#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registro.h"

int comprobar_Mayusculas (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag = 1;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] <= 90 && palabra[i] >= 65)
        {
            flag = 0;
        }
    }
    return flag;
}
int verificar_minusculas (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag = 1;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] <= 122 && palabra[i] >= 97)
        {
            flag = 0;
        }
    }
    return flag;
}
int comprobar_Numeros (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag = 1;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] <= 57 && palabra[i] >= 48)
        {
            flag = 0;
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
// COMPROBAR QUE EL USUARIO NO TENGA ESPACIOS
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
// ============================================================
//funcion que comprueba el nombre de usuario
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
//funcion que comprueba la contraseña
int comprobar_Contra (FILE *arch, char palabra [])
{
    int minContra = 8;
    int flag = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;
    int flag5 = 0;
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
    flag2 = comprobar_Mayusculas (palabra);
    if (flag2 == 1)
        {
            printf ("-LA CONTRASENA NO CONTIENE MAYUSCULA-\n");
        }
    flag4 = verificar_minusculas (palabra);
    if (flag4 == 1)
        {
            printf ("-LA CONTRASENA NO CONTIENE MINUSCULAS-\n");
        }
    flag5 = comprobar_Numeros (palabra);
    if (flag5 == 1)
        {
            printf ("-LA CONTRASENA NO CONTIENE NUMEROS-\n");
        }
    if (flag != 0 || flag2 != 0 || flag3 != 0 || flag4 != 0)
        {
            flag = 1;
        }

    return flag;
}
int verificar_Contrasena (char palabra[])
{
    char aux [20];
    int flag = 1;
    printf ("------------------------------------\n");
    printf ("VERIFICAR CONTRASENA\n");
    printf ("------------------------------------\n");
    printf ("Repetir contrasena: ");
    gets (aux);
    if (stricmp (palabra, aux) == 0)
    {
        flag = 0;
    }
    if (flag == 1)
        {
            printf ("------------------------------------\n");
            printf ("LA CONTRASENA NO COINSIDE\n");
            printf ("------------------------------------\n");
        }
    else
        {
          printf ("------------------------------------\n");
          printf ("VERIFICADO\n");
          printf ("------------------------------------\n");
        }
    return flag;
}
