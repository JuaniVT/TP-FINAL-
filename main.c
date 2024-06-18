#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "login.h"
#include "menus.h"
#include "pila.h"
//====================================================================================
// TRABAJO FINAL PROGRAMACION I
// Integrantes: Manuel Segovia, Juan Ignacio Valle Torres, Ignacio Agustin Villarreal
// SISTEMA PARA CONCESIONARIA DE AUTOS
//====================================================================================
char ventasArch [] = "ventas.bin";
char autosArch [] = "autosArch.bin";
char usuarios [] = "usuarios.bin";
int main()
{
    // VARIABLES DEL MAIN =====================
    int ops = 1; // SWITCH
    char seguirMain;
    // ========================================
    while (ops != 0)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("BIENVENIDO\n");
        printf ("------------------------------------------------------------------\n");
        printf ("1- LOGIN\n");
        printf ("2- REGISTRARSE\n");
        printf ("0- PARA CERRAR EL SISTEMA\n");
        printf ("INGRESE AQUI: ");
        fflush (stdin);
        scanf ("%d", &ops);
        printf ("\n");
        switch (ops)
        {
        case 1:
            login_Persona (usuarios);
            break;
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
void menu_Vendedor (usuario persona)
{
    int op = 1;
    while (op != 0)
    {
        printf ("------------------------------------------------------------------\n");
        printf ("BIENVENIDO %s\n", persona.nombre_Apellido);
        printf ("MENU PRINCIPAL\n");
        printf ("------------------------------------------------------------------\n");
        printf ("0- CERRAR SECCION\n");
        printf ("1- MOSTRAR LISTADO DE USUARIOS\n");
        printf ("2- MODIFICAR USUARIO\n");
        printf ("3- AGRAGAR UN USUARIO\n");
        printf ("4- MOSTRAR UN USUARIO(toda la info)\n");
        printf ("5- CARGAR AUTO AL SISTEMA\n");
        printf ("6- MOSTRAR LISTADO DE AUTOS\n");
        printf ("7- MODIFICAR UN AUTO\n");
        printf ("8- MOSTRAR UN AUTO(toda la info)\n");
        printf ("9- REGISTRAR UNA VENTA\n");
        printf ("10- VER VENTAS (fecha y patente)\n");
        printf ("11- VER VENTAS (completo)\n");
        printf ("INGRESE AQUI: ");
        scanf ("%d", &op);
        switch (op)
        {
        case 0:
            printf ("------------------------------------------------------------------\n");
            printf ("SECCION CERRADA\n");
            printf ("------------------------------------------------------------------\n");
            break;
        case 1:
            mostrar_Archivo (usuarios);
            break;
        case 2:
            modificar_usuario (usuarios);
            break;
        case 3:
            registro_En_El_sistema (usuarios);
            break;
        case 4:
            mostrar_Datos_Usuario (usuarios);
            break;
        case 5:
            registro_auto_Sistema (autosArch);
            break;
        case 6:
            recorrer_Array_Autos (autosArch);
            break;
        case 7:
            modificar_Auto (autosArch);
            break;
        case 8:
            mostrar_Datos_Auto (autosArch);
            break;
        case 9:
            registrar_Venta_Arch (ventasArch, autosArch, usuarios);
            break;
        case 10:
            mostrar_Ventas (ventasArch);
            break;
        case 11:
            mostrar_Ventas_Arch_Completo (ventasArch);
            break;
        case 12:
            break;
        }
    }
}
