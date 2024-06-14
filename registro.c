#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registro.h"
// ============================================================
//funcion que comprueba el nombre de usuario
int comprobar_Usuario (FILE *arch, char palabra [])
{
    int minUser = 8;
    int flag = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;
    int flag5 = 0;
    int flag6 = 0;
    int flag7 = 0;
    flag = verificar_Caracteres (palabra, minUser);
    flag7 = verificar_Existencia (arch, palabra);
    flag3 = verificar_Space (palabra);
    flag2 = comprobar_Mayusculas_User (palabra);
    flag4 = verificar_minusculas (palabra);
    flag5 = comprobar_Numeros (palabra);
    if (flag != 0 || flag2 != 0 || flag3 != 0 || flag4 != 0 || flag5 != 0 || flag7 != 0 || flag6)
        {
            flag = 1;
        }
    return flag;
}
int comprobar_Contra (FILE *arch, char palabra [])
{
    int minContra = 8;
    int flag = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;
    int flag5 = 0;
    flag = verificar_Caracteres (palabra, minContra);
    flag3 = verificar_Space (palabra);
    flag2 = comprobar_Mayusculas (palabra);
    flag4 = verificar_minusculas (palabra);
    flag5 = comprobar_Numeros (palabra);
    if (flag != 0 || flag2 != 0 || flag3 != 0 || flag4 != 0 || flag5 != 0)
        {
            flag = 1;
        }

    return flag;
}
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
    if (flag == 1)
        {
            printf ("-NO CONTIENE MAYUSCULA-\n");
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
    if (flag == 1)
        {
            printf ("-NO CONTIENE MINUSCULAS-\n");
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
    if (flag == 1)
        {
            printf ("-NO CONTIENE NUMEROS-\n");
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
    if (flag == 1)
    {
        printf ("-CANTIDAD INSUFICIENTE DE CARACTERES-\n");
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
    if (flag == 2)
    {
        printf ("-EL DATO INGRESADO YA EXISTE-\n");
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
    if (flag3 == 1)
        {
           printf ("-EL DATO INGRESADO CONTIENE ESPACIOS-\n");
        }
    return flag3;
}
//funcion que comprueba la contraseña
int comprobar_Mayusculas_User (char palabra[])
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
    if (flag == 1)
        {
            printf ("-CONTIENE MAYUSCULA-\n");
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
int verificar_Dni (char dni [])
{
    int flag = 1;
    int cantidad = strlen (dni);
    if (cantidad == 8)
        {
            flag = 0;
        }
    if (flag == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("EL DNI NO ES VALIDO\n");
        printf ("------------------------------------------------------------------\n");
    }
    return flag;
}
int verificar_Mail (char mail [])
{
    int flag = 1;
    int caracteres = strlen (mail);
    for (int i = 0; i < caracteres; i++)
    {
        if (mail[i] == 64)
        {
            flag = 0;
        }
    }
     if (flag == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("EL MAIL NO ES VALIDO\n");
        printf ("------------------------------------------------------------------\n");
    }
    return flag;
}
int verificar_Existencia_Persona (FILE *arch, char palabra [])
{
    int flag = 0;
    usuario aux;
    fseek (arch, 0, SEEK_SET);
    while (fread (&aux, sizeof (usuario), 1, arch) > 0)
    {
        if (strcmp (aux.dni, palabra) == 0)
        {
            flag = 1;
        }
    }
    if (flag == 1)
    {
        printf ("-LA PERSONA INGRESADA YA POSEE UNA CUENTA-\n");
    }
    return flag;
}
// NO FUNCIONA ============================================================
// EL IF
int comprobar_Caracteres_Usuario (char palabra [])
{
    int flag = 1;
    int caracteres = strlen (palabra);
    for (int i = 0 ; i < caracteres ; i++)
    {
        if ((palabra [i] >= 65 && palabra [i] <= 90) || (palabra [i] >= 97 && palabra [i] <= 122) || palabra[i] == 32)
        {
            flag = 0;
        }
        else
        {
            flag = 1;
            printf ("EL NOMBRE Y APELLIDO NO ES VALIDO\n");
            break;
        }
    }
    return flag;
}
int verificar_dos_o_mas_palabras (char palabra [])
{
    int caracteres = strlen (palabra);
    int minimo = 3;
    int flag = 1;
    for (int i = 0 ; i < caracteres ; i++)
        {
           if (i >= minimo && palabra [i] == 32)
            {
                for (int u = i ; u < caracteres ; u++)
                    {
                        if (u == i + 3)
                            {
                                flag = 0;
                                break;
                            }
                    }
            }
        }
    if (flag == 1)
        {
            printf ("INVALIDO\n");
        }
    return flag;
}

