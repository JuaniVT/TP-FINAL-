#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "registro.h"
#include "menus.h"
#include "pila.h"
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
        fseek (arch, 0, SEEK_END);
        fwrite (&persona, sizeof (usuario), 1, arch);
    }
    fclose (arch);
}
// ACA SE CREA EL LA CUENTA ================================
usuario crear_Cuenta (FILE *arch)
{
    usuario personaAux;
    personaAux = pedir_Datos_Registro (arch, personaAux);
    nombre_Usuario (arch, &personaAux);
    contrasena (arch, &personaAux);

    return personaAux;
}
// ===================================================
// registro al sistema de usuario
void nombre_Usuario (FILE* arch, usuario *persona)
{
    int variableUser = 1;
    while (variableUser != 0)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("CREE SU NOMBRE DE USUARIO\n");
        printf ("------------------------------------------------------------------\n");
        printf ("Requisitos:\n");
        printf ("Debe tener minimo 8 caracteres\n");
        printf ("NO debe contener una Mayuscula\n");
        printf ("NO debe contener espacios\n");
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE AQUI: ");
        fflush (stdin);
        gets ((*persona).user);
        printf ("------------------------------------------------------------------\n");
        variableUser = comprobar_Usuario (arch, (*persona).user);
        if (variableUser != 0)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("REINGRESAR NOMBRE DE USUARIO\n");
            printf ("------------------------------------------------------------------\n");
        }
    }
}
// ======================================================
// CREA CONTRASEÑA
void contrasena (FILE* arch, usuario *persona)
{
    int variableContra = 1;
    //a cada funcion hay que agregarle su propia variable para recibir el valor =)
    while (variableContra != 0)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("CREE UNA CONTRASEÑA\n");
        printf ("------------------------------------------------------------------\n");
        printf ("Requisitos:\n");
        printf ("Debe contener una Mayuscula\n");
        printf ("Debe tener minimo 8 caracteres\n");
        printf ("Debe contener un numero\n");
        printf ("NO debe contener espacios\n");
        printf ("------------------------------------------------------------------\n");
        printf ("INGRESE AQUI: ");
        fflush (stdin);
        gets ((*persona).contra);
        printf ("------------------------------------------------------------------\n");
        variableContra = comprobar_Contra (arch, (*persona).contra);
        if (variableContra == 0)
            {
             variableContra = verificar_Contrasena ((*persona).contra);
            }
        if (variableContra != 0)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("REESCRIBA LA CONTRASENA\n");
            printf ("------------------------------------------------------------------\n");
        }
    }
}
// ============================================================
//funcion que comprueba el nombre de usuario
int comprobar_Usuario (FILE *arch, char palabra [])
{
    int minUser = 8;
    int flag = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;
    int flag6 = 0;
    int flag7 = 0;
    flag = verificar_Caracteres (palabra, minUser);
    flag7 = verificar_Existencia (arch, palabra);
    flag3 = verificar_Space (palabra);
    flag2 = comprobar_Mayusculas_User (palabra);
    flag4 = verificar_minusculas (palabra);
    if (flag != 0 || flag2 != 0 || flag3 != 0 || flag4 != 0 || flag7 != 0 || flag6)
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
            printf ("-NO CONTIENE MINUSCULA-\n");
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
int comprobar_Numeros_Dni (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag = 0;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] > 57 || palabra[i] < 48)
        {
            flag = 1;
        }
    }
    if (flag == 1)
        {
            printf ("-CARACTERES INVALIDOS-\n");
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
        printf ("-EL NOMBRE INGRESADO YA EXISTE-\n");
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
           printf ("-CONTIENE ESPACIOS-\n");
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
    printf ("------------------------------------------------------------------\n");
    printf ("VERIFICAR CONTRASENA\n");
    printf ("------------------------------------------------------------------\n");
    printf ("Repetir contrasena: ");
    gets (aux);
    if (stricmp (palabra, aux) == 0)
    {
        flag = 0;
    }
    if (flag == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("LA CONTRASENA NO COINSIDE\n");
            printf ("------------------------------------------------------------------\n");
        }
    else
        {
          printf ("------------------------------------------------------------------\n");
          printf ("VERIFICADO\n");
          printf ("------------------------------------------------------------------\n");
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
        printf ("-DNI INEXISTENTE-\n");
    }
    return flag;
}
int verificar_Telefono (char tele [])
{
    int flag = 1;
    int cantidad = strlen (tele);
    if (cantidad > 8)
        {
            flag = 0;
        }
    if (flag == 1)
    {
        printf ("-TELEFONO INEXISTENTE-\n");
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
        printf ("-EL MAIL NO ES VALIDO-\n");
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
            printf ("-CARACTERES NO VALIDOS EN EL NOMBRE Y APELLIDO-\n");
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
            printf ("-NO SE COMPLETO EL NOMBRE Y APELLIDO-\n");
        }
    return flag;
}
int verificar_Anio (int anio)
{
    int flag = 0;
    int limite = 2006;
    int i = 0;
    int aux = anio;
    while (anio > 0)
    {
        anio = anio / 10;
        i++;
    }
    if (aux > limite || i != 4)
    {
        flag = 1;
    }
    return flag;
}
int verificar_Mes (int mes)
{
    int flag = 0;
    if (mes >= 12 || mes <= 1)
        {
            flag = 1;
        }
    return flag;
}
int verificar_Dia (int dia, int mes)
{
    int flag = 0;
    int meses_31_dias [] = {1, 3, 5, 7, 8, 10, 12};
    int meses_30_dias [] = {4, 6, 9, 11};
    int febrero = 2;
    for (int i = 0 ; i < 7 ; i ++)
        {
            if (mes == meses_30_dias[i])
                {
                    if (dia > 30)
                    {
                        flag = 1;
                        break;
                    }
                }
        }
     for (int i = 0 ; i < 7 ; i ++)
     {
        if (mes == meses_31_dias[i])
                {
                    if (dia > 31)
                    {
                        flag = 1;
                        break;
                    }
                }
     }
    if (mes == febrero)
    {
        if (dia > 29)
        {
            flag = 1;
        }
    }

return flag;
}
int comprobar_Edad (int dia, int mes, int anio)
{
    int flag = 0;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    flag1 = verificar_Anio (anio);
    flag2 = verificar_Mes (mes);
    flag3 = verificar_Dia (dia, mes);
    if (flag1 != 0 || flag2 != 0 || flag3 != 0)
        {
            flag = 1;
            printf ("-EDAD INVALIDA-\n");
        }
    return flag;
}
int verificar_Rol (char aux)
{
    int flag = 0;
    if (aux != '0' && aux != '1')
        {
            flag = 1;
            printf ("-ROL INVALIDO-\n");
        }
    return flag;
}
int verificar_Caracteres_Edad (char dia [], char mes [], char anio [])
{
    int flag = 0;
    int flag1 = 1;
    int flag2 = 1;
    int flag3 = 1;
    flag1 = comprobar_Numeros_Edad (dia);
    flag2 = comprobar_Numeros_Edad (mes);
    flag3 = comprobar_Numeros_Edad (anio);
    if (flag1 == 1 || flag2 == 1 || flag3 == 1)
    {
        printf ("CARACTERES INVALIDOS\n");
        flag = 1;
    }
    return flag;
}
int comprobar_Numeros_Edad (char palabra[])
{
    int caracteres = strlen (palabra);
    int flag = 0;
    for (int i = 0; i < caracteres; i++)
    {
        if (palabra[i] > 57 || palabra[i] < 48)
        {
            flag = 1;
        }
    }
    return flag;
}
// ===============================================================
// FUNCION QUE PIDE DATOS PERSONALES PARA EL REGISTRO ============
usuario pedir_Datos_Registro (FILE *arch, usuario persona)
{
    int flag = 1;
    int flag2 = 1;
    int flag3 = 1;
    int flag4 = 1;
    while (flag == 1)
    {
        flag2 = 1;
        flag3 = 1;
        flag4 = 1;
        while (flag4 == 1 || flag3 == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("NOMBRE Y APELLIDO: ");
            fflush (stdin);
            gets (persona.nombre_Apellido);
            flag4 = comprobar_Caracteres_Usuario (persona.nombre_Apellido);
            flag3 = verificar_dos_o_mas_palabras (persona.nombre_Apellido);
        }
        flag3 = 1;
        while (flag2 == 1 || flag3 == 1 || flag4 == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("DNI: ");
            fflush (stdin);
            gets (persona.dni);
            flag3 = verificar_Dni (persona.dni);
            flag4 = comprobar_Numeros_Dni (persona.dni);
            flag2 = verificar_Space (persona.dni);
        }
        flag = verificar_Existencia_Persona (arch, persona.dni);
    }
    fseek (arch, 0, SEEK_END);
    flag2 = 1;
    flag4 = 1;
    flag3 = 1;
    while (flag2 == 1 || flag4 == 1 || flag3 == 1)
        {
            printf ("------------------------------------------------------------------\n");
            printf ("TELEFONO: ");
            fflush (stdin);
            gets (persona.tele);
            flag3 = verificar_Telefono (persona.tele);
            flag4 = comprobar_Numeros_Dni (persona.tele);
            flag2 = verificar_Space (persona.tele);
        }
    flag = 1;
    flag2 = 1;
    while (flag == 1 || flag2 == 1)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("DIRECCION DE CORREO: ");
        fflush (stdin);
        gets (persona.email);
        flag = verificar_Mail (persona.email);
        flag2 = verificar_Space (persona.email);
    }
    flag = 1;
    while (flag == 1)
    {
        flag2 = 1;
        printf ("------------------------------------------------------------------\n");
        printf ("FECHA DE NACIMIENTO\n");
        printf ("------------------------------------------------------------------\n");
        while (flag2 == 1)
        {
            printf("Ingrese el dia de nacimiento: ");
            fflush (stdin);
            gets (persona.nacimiento.dia);
            printf("Ingrese el mes de nacimiento: ");
            fflush (stdin);
            gets (persona.nacimiento.mes);
            printf("Ingrese el año de nacimiento: ");
            fflush (stdin);
            gets (persona.nacimiento.anio);
            flag2 = verificar_Caracteres_Edad (persona.nacimiento.dia, persona.nacimiento.mes, persona.nacimiento.anio);
        }
        int diaE = atoi (persona.nacimiento.dia);
        int mesE = atoi (persona.nacimiento.mes);
        int anioE = atoi (persona.nacimiento.anio);
        flag = comprobar_Edad (diaE, mesE, anioE);
    }
    flag = 1;
    flag2 = 1;
    while (flag == 1)
    {
        char aux = '0' ;
        printf ("------------------------------------------------------------------\n");
        printf ("ROL (1 = vendedor ; 0 = Comprador)");
        printf ("INGRESE AQUI = ");
        fflush (stdin);
        scanf ("%c", &aux);
        flag = verificar_Rol (aux);
        if (flag == 0)
            {
                if (aux == '0')
                    {
                        strcpy (persona.rol, "COMPRADOR");
                    }
                    else
                        {
                            strcpy (persona.rol, "VENDEDOR");
                        }
            }

    }
    return persona;
}
