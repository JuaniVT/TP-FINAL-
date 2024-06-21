#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "login.h"
#include "menus.h"
#include "pila.h"
// =================================================================================================
// =================================================================================================
void login_Persona (char archivo [])
{
    FILE *arch = fopen (archivo, "rb"); // Abrir el archivo de usuarios

    // Verificar si se pudo abrir correctamente el archivo
    if (arch == NULL)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("NO HAY NADIE REGISTRADO\n");
        printf ("------------------------------------------------------------------\n");
    }
    else
    {
        usuario aux; // Variable para almacenar los datos de cada usuario
        int i = 1; // Variable de control para el bucle de login
        int flag = 0; // Variable para almacenar el rol del usuario logueado
        char contra_Login [20]; // Arreglo de caracteres para almacenar la contraseña ingresada
        char user_O_Mail [40]; // Arreglo de caracteres para almacenar el nombre de usuario o mail ingresado
        char seguir = 's'; // Variable para controlar si el usuario desea seguir en el login

        // Bucle para el proceso de login
        while (i == 1 && seguir != 'b')
        {
            // Mostrar encabezados y solicitar nombre de usuario o mail
            printf ("------------------------------------------------------------------\n");
            printf ("LOGIN\n");
            printf ("------------------------------------------------------------------\n");
            printf ("NOMBRE DE USUARIO o MAIL\n");
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE AQUI: ");
            fflush (stdin);
            gets (user_O_Mail); // Leer nombre de usuario o mail ingresado

            // Solicitar y leer la contraseña
            printf ("------------------------------------------------------------------\n");
            printf ("NOMBRE DE CONTRASEÑA\n");
            printf ("------------------------------------------------------------------\n");
            printf ("INGRESE AQUI: ");
            fflush (stdin);
            gets (contra_Login); // Leer contraseña ingresada

            // Llamar a la función comprobar_Login para verificar la autenticación
            i = comprobar_Login (arch, user_O_Mail, contra_Login, &aux);

            // Si la autenticación falla, pedir al usuario que ingrese 'b' para volver al menú
            if (i == 1)
            {
                printf ("------------------------------------------------------------------\n");
                printf ("El usuario o contrasena no coinciden\n");
                printf ("Si desea volver al menu ingrese 'b'\n");
                printf ("------------------------------------------------------------------\n");
                printf ("INGRESE AQUI: ");
                fflush (stdin);
                scanf ("%c", &seguir); // Leer la opción para continuar o volver al menú
            }

            // Si la autenticación es exitosa, verificar el rol del usuario
            if (i == 0)
            {
                flag = comprueba_Rol (aux); // Obtener el rol del usuario logueado

                // Si el rol es 1 (vendedor), llamar a la función menu_Vendedor
                if (flag == 1)
                {
                    menu_Vendedor (aux); // Llamar al menú para vendedores pasando los datos del usuario
                }
                else
                {
                    menu_Comprador (aux);// Llamar al menú para compradores pasando los datos del usuario
                }
            }
        }
    }

    // Cerrar el archivo después de la operación
    fclose (arch);
}
// =================================================================================================
// =================================================================================================
int comprobar_Login(FILE *arch, char nomb[], char contra[], usuario *aux)
{
    int i = 1; // Variable de control inicializada en 1 (no encontrado)
    fseek(arch, 0, SEEK_SET); // Colocar el puntero al inicio del archivo

    // Leer registros del archivo de usuarios hasta el final
    while (fread(aux, sizeof(usuario), 1, arch) > 0)
    {
        // Verificar si el nombre de usuario o email y la contraseña coinciden con algún registro
        if ((strcmp((*aux).user, nomb) == 0 || strcmp((*aux).email, nomb) == 0) && strcmp((*aux).contra, contra) == 0)
        {
            i = 0; // Cambiar la variable de control a 0 (encontrado)
            break; // Salir del bucle una vez encontrado el usuario
        }
    }

    return i; // Retornar el valor de la variable de control
}
// =================================================================================================
// =================================================================================================
int comprueba_Rol(usuario persona)
{
    int flag = 0; // Variable de control inicializada en 0 (no vendedor)

    // Verificar si el rol de la persona es "VENDEDOR" (case insensitive)
    if (strcmpi(persona.rol, "VENDEDOR") == 0)
    {
        flag = 1; // Cambiar la variable de control a 1 (vendedor)
    }

    return flag; // Retornar el valor de la variable de control
}
