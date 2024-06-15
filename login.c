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
        char seguir = 's';
        while (i == 1 && seguir != 'b')
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
                printf ("Si desea volver al menu ingrese 'b'\n");
                printf ("-----------------------------------\n");
                printf ("INGRESE AQUI: ");
                fflush (stdin);
                scanf ("%c", &seguir);
            }
            if (i == 0)
            {
                printf ("------------------------------\n");
                printf ("BIENVENIDO\n");
                printf ("------------------------------\n");
            }
        }
    }
    fclose (arch);
}
int comprobar_Login (FILE * arch, char nomb [], char contra [])
{
    usuario aux;
    int i = 1;
   while (fread (&aux, sizeof (usuario), 1, arch) > 0)
    {
        if ((strcmp (aux.user, nomb) == 0 || strcmp (aux.email, nomb) == 0) && strcmp (aux.contra, contra) == 0)
            {
               i = 0;
            }
    }

    return i;
}
