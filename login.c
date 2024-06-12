#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "login.h"
void login_Persona (char archivo [])
{
    FILE *arch = fopen (archivo, "rb");

    if (arch != NULL)
    {
        int i = 1;
        char contra_Login [20];
        char user_O_Mail [30];
        while (i == 1)
        {
            printf ("-----------------------------------\n");
            printf ("LOGIN\n");
            printf ("-----------------------------------\n");
            printf ("NOMBRE DE USUARIO o MAIL\n");
            printf ("-----------------------------------\n");
            printf ("INGRESE AQUI: ");
            fflush (stdin);
            gets (user_O_Mail);
            printf ("-----------------------------------\n");
            printf ("NOMBRE DE CONTRASEÑA\n");
            printf ("-----------------------------------\n");
            printf ("INGRESE AQUI: ");
            fflush (stdin);
            gets (contra_Login);
            i = comprobar_Login (arch, user_O_Mail, contra_Login);
            if (i == 1)
            {
                printf ("-----------------------------------\n");
                printf ("El usuario o contrasena no coinciden\n");
                printf ("-----------------------------------\n");
            }
            if (i == 0)
            {
                printf ("------------------------------\n");
                printf ("BIENVENIDO\n");
                printf ("------------------------------\n");
            }
        }
    }
}
int comprobar_Login (FILE * arch, char nomb [], char contra [])
{
    usuario aux;
    int i = 1;
   while (fread (&aux, sizeof (usuario), 1, arch) > 0)
    {
        if ((strcmpi (aux.user, nomb) == 0 || strcmpi (aux.email, nomb) == 0) && strcmpi (aux.contra, contra) == 0)
            {
               i = 0;
            }
    }

    return i;
}
