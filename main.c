#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
//====================================================================================
// TRABAJO FINAL PROGRAMACION I
// Integrantes: Manuel Segovia, Juan Ignacio Valle Torres, Ignacio Agustin Villarreal
// SISTEMA PARA CONCESIONARIA DE AUTOS
//====================================================================================
void registro_En_El_sistema (char []);
usuario crear_Cuenta (FILE*);
usuario nombre_Usuario (FILE*, usuario*);
usuario contrasena (FILE*, usuario*);
int main()
{
    // VARIABLES DEL MAIN =====================
    int ops = 1; // SWITCH
    char seguirMain;
    // ========================================
    // CREACION DE ARCHIVOS ===================
    char autosArch [] = "autos.bin";
    char usuarios [] = "usuarios.bin";
    char ventas [] = "ventas.bin";
    // ========================================

    while (ops != 0)
    {
        printf ("------------------------------------------\n");
        printf ("BIENVENIDO\n");
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
            registro_En_El_sistema (usuarios);
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
// ACA SE CREA EL LA CUENTA ================================
usuario crear_Cuenta (FILE *arch)
{
    usuario personaAux;
    nombre_Usuario (arch, &personaAux);
    contrasena (arch, &personaAux);

    return personaAux;
}
// ===================================================
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
// ======================================================
// CREA CONTRASEÑA
usuario contrasena (FILE* arch, usuario *persona)
{
    int variableContra = 1;
    //a cada funcion hay que agregarle su propia variable para recibir el valor =)
    while (variableContra != 0)
    {
        printf ("Ingrese una contrasena: ");
        fflush (stdin);
        gets ((*persona).contra);
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
    return (*persona);
}
// ===============================================================
// FUNCION QUE PIDE DATOS PERSONALES PARA EL REGISTRO ============

